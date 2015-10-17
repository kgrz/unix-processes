# I initially thought this would return 10 outputs: 9 "bye"s and 1 "hi" but
# that's not the case.
fork && fork && fork && fork && puts("hi")
puts 'bye'
