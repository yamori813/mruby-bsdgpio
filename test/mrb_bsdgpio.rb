##
## BsdGpio Test
##

assert("BsdGpio#hello") do
  t = BsdGpio.new "hello"
  assert_equal("hello", t.hello)
end

assert("BsdGpio#bye") do
  t = BsdGpio.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("BsdGpio.hi") do
  assert_equal("hi!!", BsdGpio.hi)
end
