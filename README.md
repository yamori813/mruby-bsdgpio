# mruby-bsdgpio   [![Build Status](https://travis-ci.org/yamori813/mruby-bsdgpio.svg?branch=master)](https://travis-ci.org/yamori813/mruby-bsdgpio)
BsdGpio class.
FreeBSD GPIO wapper for mruby. Build on 11-CURRENT. Because of use libgpio.
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'yamori813/mruby-bsdgpio'
end
```
## example
```ruby
t = BsdGpio.new(0)
#=> #<BsdGpio:0x40ee3fd8>
t.setflags(1, BsdGpio::OUTPUT)
#=> 0
t.set(1,1)
#=> 0
t.set(1,0)
#=> 0
```

## License
under the BSD License:
- see LICENSE file
