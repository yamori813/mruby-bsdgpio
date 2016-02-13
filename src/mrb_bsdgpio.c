/*
** mrb_bsdgpio.c - BsdGpio class
**
** Copyright (c) Hiroki Mori 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mrb_bsdgpio.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_bsdgpio_data;

static const struct mrb_data_type mrb_bsdgpio_data_type = {
  "mrb_bsdgpio_data", mrb_free,
};

static mrb_value mrb_bsdgpio_init(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data;
  char *str;
  int len;

  data = (mrb_bsdgpio_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_bsdgpio_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_bsdgpio_data *)mrb_malloc(mrb, sizeof(mrb_bsdgpio_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value mrb_bsdgpio_hello(mrb_state *mrb, mrb_value self)
{
  mrb_bsdgpio_data *data = DATA_PTR(self);

  return mrb_str_new(mrb, data->str, data->len);
}

static mrb_value mrb_bsdgpio_hi(mrb_state *mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, "hi!!");
}

void mrb_mruby_bsdgpio_gem_init(mrb_state *mrb)
{
    struct RClass *bsdgpio;
    bsdgpio = mrb_define_class(mrb, "BsdGpio", mrb->object_class);
    mrb_define_method(mrb, bsdgpio, "initialize", mrb_bsdgpio_init, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, bsdgpio, "hello", mrb_bsdgpio_hello, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, bsdgpio, "hi", mrb_bsdgpio_hi, MRB_ARGS_NONE());
    DONE;
}

void mrb_mruby_bsdgpio_gem_final(mrb_state *mrb)
{
}

