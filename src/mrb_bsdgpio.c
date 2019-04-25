/*
** mrb_bsdgpio.c - BsdGpio class
**
** Copyright (c) Hiroki Mori 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/array.h"
#include "mrb_bsdgpio.h"

#include <fcntl.h>
#include <libgpio.h>

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  gpio_handle_t handle;
} mrb_bsdgpio_data;

static const struct mrb_data_type mrb_bsdgpio_data_type = {
  "mrb_bsdgpio_data", mrb_free,
};

static mrb_value mrb_bsdgpio_init(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data;
  mrb_int num;

  data = (mrb_bsdgpio_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_bsdgpio_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "i", &num);
  data = (mrb_bsdgpio_data *)mrb_malloc(mrb, sizeof(mrb_bsdgpio_data));
  data->handle = gpio_open(num);
  
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_bsdgpio_set(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);
  mrb_int pin, val;

  mrb_get_args(mrb, "ii", &pin, &val);

  gpio_pin_set(data->handle, pin, val);

  return mrb_fixnum_value(0);
}

static mrb_value mrb_bsdgpio_get(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);
  mrb_int pin, val;

  mrb_get_args(mrb, "i", &pin);

  val = gpio_pin_get(data->handle, pin);

  return mrb_fixnum_value(val);
}

static mrb_value mrb_bsdgpio_setflags(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);
  mrb_int pin, flag;
  gpio_config_t conf;

  mrb_get_args(mrb, "ii", &pin, &flag);

  conf.g_pin = pin;
  conf.g_flags = flag;
  gpio_pin_set_flags(data->handle, &conf);

  return mrb_fixnum_value(0);
}

static mrb_value mrb_bsdgpio_access32(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);
  mrb_int first_pin, clear_pins, change_pins;
  struct gpio_access_32 gacc32;

  mrb_get_args(mrb, "iii", &first_pin, &clear_pins, &change_pins);

  gacc32.first_pin = first_pin;
  gacc32.clear_pins = clear_pins;
  gacc32.change_pins = change_pins;
  ioctl(data->handle, GPIOACCESS32, &gacc32);

  return mrb_fixnum_value(gacc32.orig_pins);
}

static mrb_value mrb_bsdgpio_config32(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);
  mrb_int first_pin, num_pins;
  mrb_value arr;
  struct gpio_config_32 gconf32;
  int i;

  mrb_get_args(mrb, "iiA", &first_pin, &num_pins, &arr);

  gconf32.first_pin = first_pin;
  gconf32.num_pins = num_pins;
  for (i = 0; i < num_pins; ++i) {
    gconf32.pin_flags[i] = mrb_fixnum( mrb_ary_ref( mrb, arr, i));
  }
  ioctl(data->handle, GPIOCONFIG32, &gconf32);

  return mrb_fixnum_value(0);
}

void mrb_mruby_bsdgpio_gem_init(mrb_state *mrb)
{
    struct RClass *bsdgpio;
    bsdgpio = mrb_define_class(mrb, "BsdGpio", mrb->object_class);
    mrb_define_const(mrb, bsdgpio, "INPUT",  mrb_fixnum_value(GPIO_PIN_INPUT));
    mrb_define_const(mrb, bsdgpio, "OUTPUT",  mrb_fixnum_value(GPIO_PIN_OUTPUT));
    mrb_define_method(mrb, bsdgpio, "initialize", mrb_bsdgpio_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, bsdgpio, "set", mrb_bsdgpio_set, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, bsdgpio, "get", mrb_bsdgpio_get, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, bsdgpio, "setflags", mrb_bsdgpio_setflags, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, bsdgpio, "access32", mrb_bsdgpio_access32, MRB_ARGS_REQ(3));
    mrb_define_method(mrb, bsdgpio, "config32", mrb_bsdgpio_config32, MRB_ARGS_REQ(3));
    DONE;
}

void mrb_mruby_bsdgpio_gem_final(mrb_state *mrb)
{
}

