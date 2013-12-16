require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"EntityManager",
	function ()
		local entityManager = kf.EntityManager()
		local entity1 = kf.Entity("one")
		local entity2 = kf.Entity("two")

		entityManager:addEntity(entity1)
		entityManager:addEntity(entity2)

		local entity_one = entityManager:getEntityByID(entity1:getID())
		test_assert("getEntityByID", entity1:getID() == entity_one:getID())

		local entities = entityManager:getEntities()
		test_assert("getEntities", #entities == 2)
		test_assert("getEntities (isEntity)", kf.isEntity(entities[1]))

end)
