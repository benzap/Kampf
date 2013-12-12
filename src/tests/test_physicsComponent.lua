require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"PhysicsComponent",
	function()
		
		--create a physics component
		local component = kf.PhysicsComponent("physical")
		
		--get it's current name
		test_assert("getName", component:getName() == "physical");
		
		--change it's name
		component:setName("ben")
		test_assert("setName", component:getName() == "ben");

		--get the string representation
		test_assert("toString",
					tostring(component) == "Component:PHYSICS:ben");
		
		--get the family it belongs to
		test_assert("getFamily", component:getFamily() == "PHYSICS")

		--is it a parent?
		test_assert("isParent", component:isParent() == true)
		
		--is it active?
		test_assert("isActive - true", component:isActive())

		--is it not active?
		component:setInactive()
		test_assert("isActive - false (setInactive())",
					component:isActive() == false)
		
		--is it now active?
		component:setActive()
		test_assert("isActive - true (setActive())",
					component:isActive() == true)

		--set based on custom attributes (for now)
		component:set("bigNumber", kf.CustomAttribute(123412))

		--does it have that number?
		test_assert("has", component:has("bigNumber") == true)

		--does it not have that number?
		test_assert("has (false)", component:has("bigLetter") == false)

		--get the big number
		local bigNumberAttr = component:get("bigNumber")
		
		--did it actually return a custom attribute?
		test_assert("isCustomAttribute", kf.isCustomAttribute(bigNumberAttr))

		--did it return a float type?
		test_assert("is it a float?", bigNumberAttr:type() == "FLOAT")
		
		--did it actually return the right float?
		test_assert("get()", bigNumberAttr:get() == 123412)

		--does it have any children (no)
		test_assert("hasChildren", component:hasChildren() == false)

		--lets create a child
		local childComponent = component:createChild("sibling")
		
		--check if the new child component has right name
		test_assert("new child check name",
					childComponent:getName(),
					"sibling")

		--now does it have children?
		test_assert("hasChildren (true)", component:hasChildren() == true)

		local children = component:children()
		--lets get the child from our children list
		test_assert("children", component:children()[1]:getName() == "sibling")		


end)
