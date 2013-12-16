require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"AbstractComponent",
	function ()

		local entity = kf.Entity("ben");
		test_assert("getName", entity:getName() == "ben")

		--set the name to something different
		entity:setName("apeman")
		test_assert("setName", entity:getName() == "apeman")

		local entity2 = kf.Entity("monkey")

		test_assert("getID (type)", type(entity2:getID()) == "number")

		--check if IDs are unique
		test_assert("getID (unique)", entity:getID() ~= entity2:getID())

		local abstractComponent = kf.AbstractComponent("so abstract")
		entity:addComponent(abstractComponent)

		local collisionComponent = kf.CollisionComponent("collidable")
		entity:addComponent(collisionComponent)
		
		local physicsComponent = kf.PhysicsComponent("physical")
		entity:addComponent(physicsComponent)

		local graphicsComponent = kf.GraphicsComponent("graphics")
		entity:addComponent(graphicsComponent)

		local componentList = entity:getComponents()
		for _, component in ipairs(componentList) do
			print(component)
		end

		test_assert("getComponents", #componentList == 4)

		local compPhysics = entity:getComponentsByFamily("PHYSICS")
		test_assert("getComponentsByFamily", compPhysics[1]:getName() == "physical")
		
		local compAnAbstract = entity:getComponentsByName("so abstract")
		test_assert("getComponentsByName", compAnAbstract[1]:getName() == "so abstract")



end)
