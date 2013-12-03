require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"CustomAttribute",
	function ()
		local customAttr_num = kf.CustomAttribute(10)
		print(customAttr_num)
		test_assert("getInteger", customAttr_num:getInteger() == 10);
		test_assert("get (int)", customAttr_num:get() == 10);

		local customAttr_num2 = kf.CustomAttribute(3.14)
		print(customAttr_num2)
		test_assert("getFloat", customAttr_num2:getFloat() == 3.14);
		test_assert("get (float)", customAttr_num2:get() == 3.14);

		local customAttr_string = kf.CustomAttribute("Hello")
		print(customAttr_string)
		test_assert("getString", customAttr_string:getString() == "Hello")
		test_assert("get (string)", customAttr_string:get() == "Hello")

		local customAttr_array = kf.CustomAttribute{2,2,4,4}
		print(customAttr_array)

		local array = customAttr_array:getArray()
		test_assert("getArray",table.eq(array, {2,2,4,4}))
		local array = customAttr_array:get()
		test_assert("get (array)", table.eq(array, {2,2,4,4}))

		local customAttr_char = kf.CustomAttribute()
		customAttr_char:setChar("a")
		print(customAttr_char)

		print(customAttr_char:getChar())
		test_assert("getChar", customAttr_char:getChar() == "a")
		test_assert("get (char)", customAttr_char:get() == "a")



end)
