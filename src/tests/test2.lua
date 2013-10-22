math = require "math"


y = "world"
x = "hello" .. y

print(x)



function concat(i, j)
	return i .. j
end

print(concat("hello ", y.."!"))
