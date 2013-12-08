require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"AbstractComponent",
	function ()
		
		--create an abstract component
		local component = kf.AbstractComponent("bacon")
		
		test_assert("getName", component:getName() == "bacon");
		
		component:setName("ben")
		test_assert("setName", component:getName() == "ben");

		


end)
