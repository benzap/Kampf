unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"CustomAttribute",
	function ()
		local customAttr_num = kf.CustomAttribute(10)
		print(customAttr_num)

		local customAttr_num2 = kf.CustomAttribute(3.14)
		print(customAttr_num2)

		local customAttr_string = kf.CustomAttribute("Hello")
		print(customAttr_string)



end)
