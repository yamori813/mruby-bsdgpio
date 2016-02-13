# mruby-bsdgpio   [![Build Status](https://travis-ci.org/yamori813/mruby-bsdgpio.svg?branch=master)](https://travis-ci.org/yamori813/mruby-bsdgpio)
BsdGpio class
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
t = BsdGpio.new "hello"
p t.hi
#=> "hi!!"
p t.lo
#=> "lo!!"
p t.bye
#=> "hello bye"
```

## License
under the BSD License:
- see LICENSE file
