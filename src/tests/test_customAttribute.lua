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

		customAttr_num:setInteger(13)
		test_assert("setInteger - test", customAttr_num:get() == 13)

		local customAttr_num2 = kf.CustomAttribute(3.14)
		print(customAttr_num2)
		test_assert("getFloat", customAttr_num2:getFloat() == 3.14);
		test_assert("get (float)", customAttr_num2:get() == 3.14);

		customAttr_num2:setFloat(2.73)
		test_assert("setFloat -test", customAttr_num2:get() == 2.73)

		local customAttr_string = kf.CustomAttribute("Hello")
		print(customAttr_string)
		test_assert("getString",customAttr_string:getString() == "Hello")
		test_assert("get (string)", customAttr_string:get() == "Hello")

		customAttr_string:setString("World!")
		test_assert("setString - test", customAttr_string:get() == "World!")

		local customAttr_array = kf.CustomAttribute{2,2,4,4}
		print(customAttr_array)
		local array = customAttr_array:getArray()
		test_assert("getArray",table.eq(array, {2,2,4,4}))
		local array = customAttr_array:get()
		test_assert("get (array)", table.eq(array, {2,2,4,4}))

		customAttr_array:setArray{4,2,4,2}
		local array = customAttr_array:get()
		test_assert("setArray - test", table.eq(array, {4,2,4,2}))

		local customAttr_char = kf.CustomAttribute()
		customAttr_char:setChar("a")
		print(customAttr_char)
		test_assert("getChar", customAttr_char:getChar() == "a")
		test_assert("get (char)", customAttr_char:get() == "a")

		local customAttr_bool = kf.CustomAttribute()
		customAttr_bool:setBool(true)
		print(customAttr_bool)
		test_assert("getBool", customAttr_bool:getBool() == true)
		test_assert("get (bool)", customAttr_bool:get() == true)

		local customAttr_vector = kf.CustomAttribute()
		customAttr_vector:setVector(kf.Vector3(1,2,3))
		print(customAttr_vector)
		test_assert("getVector", customAttr_vector:getVector() == kf.Vector3(1,2,3))
		test_assert("get (vector)", customAttr_vector:get() == kf.Vector3(1,2,3))

end)
