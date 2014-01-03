require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"CollisionComponent",
	function()
		
		--create a collision component
		local component = kf.CollisionComponent("collidable")
		
		--get it's current name
		test_assert("getName", component:getName() == "collidable");
		
		--change it's name
		component:setName("ben")
		test_assert("setName", component:getName() == "ben");

		--get the string representation
		test_assert("toString",
					tostring(component) == "Component:COLLISION:ben");
		
		--get the family it belongs to
		test_assert("getFamily", component:getFamily() == "COLLISION")

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
		test_assert("children",
					component:children()[1]:getName() == "sibling")		


		-- collision bounds

		--setOffset / getOffset
		component:setOffset(kf.Vector3(1,2,3))
		test_assert("setOffset - getOffset",
					component:getOffset() == kf.Vector3(1,2,3))

		--setOrigin / getOrigin
		component:setOrigin(kf.Vector3(1,1.1,1.3))
		local origin = component:getOrigin()
		test_assert("setOrigin - getOrigin",
					origin == kf.Vector3(1,1.1,1.3))

		--setOrientation / getOrientation
		component:setOrientation(kf.Quaternion(1.1, 1.4, 1.2, 0))
		local orientation = component:getOrientation()
		test_assert("setOrientation - getOrientation",
					orientation == kf.Quaternion(1.1, 1.4, 1.2, 0))


		-- collision component specifics

		--testing defaults
		test_assert("getType", component:getType() == "NONE")
		
		--setType (CIRCLE)
		component:setType("CIRCLE")
		test_assert("setType", component:getType() == "CIRCLE")

		--setRadius / getRadius
		component:setRadius(10)
		test_assert("setRadius - getRadius", component:getRadius() == 10)
 
		--setWidth / getWidth
		component:setWidth(5)
		test_assert("setWidth - getWidth", component:getWidth() == 5)

		--setHeight / getHeight
		component:setHeight(3)
		test_assert("setHeight - getHeight", component:getHeight() == 3)

		local v3 = kf.Vector3
		component:setVectorList{
			v3(0,0,0),
			v3(0,1,0),
			v3(1,0,0),
			v3(1,1,0)
		}

		local vecList = {
			v3(0,0,0),
			v3(0,1,0),
			v3(1,0,0),
			v3(1,1,0)
		}

		local compList = component:getVectorList()
		
		for i = 1,#vecList do
			test_assert("comparison veclist - " .. i, vecList[i] == compList[i])
		end
		

end)
