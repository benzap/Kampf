--[[

	This module is to simplify the creation of sprites, by creating an
	entity type that consists of only one graphics component, one
	collision component, and one physics component.
	
	creating a sprite involves loading a table with the necessary
	arguments describing your sprite

	args = {
	  physics = {
    	position = {0,0,0},
      },
	  graphics = {
        key = "default",
        index = 0,
	  },
	  collision = {
        type = "CIRCLE",
        radius = 50,
      }
	}

]]

local sprite = {

}

function sprite:new(args)
	obj = {}
	setmetatable(obj, self)
	self.__index = self

	--create a new entity to assign to our object
	local entity = kf.Entity(args.name or "")
	obj.entity = entity

	--create our physics component
	local physicsComponent = kf.PhysicsComponent("sprite-physical")
	obj.physics = physicsComponent
	entity:addComponent(physicsComponent)

	--set the physics arguments
	local physicsArgs = args.physics or {}

	--physics position
	local physicsPosition = physicsArgs.position or {0,0,0}
	local posVector = kf.Vector3(physicsPosition[1],
								 physicsPosition[2],
								 physicsPosition[3])
	physicsComponent:setPosition(posVector)

	--physics velocity
	local velocity = physicsArgs.velocity or {0,0,0}
	physicsComponent:setVelocity(kf.Vector3(
									 velocity[1],
									 velocity[2],
									 velocity[3]))

	--physics acceleration
	local acceleration = physicsArgs.acceleration or {0, 0, 0}
	physicsComponent:setAcceleration(kf.Vector3(
										 acceleration[1],
										 acceleration[2],
										 acceleration[3]))

	--physics damping
	physicsComponent:setDamping(physicsArgs.damping or 1)

	--graphics component
	local graphicsComponent = kf.GraphicsComponent("sprite-graphics")
	obj.graphics = graphicsComponent
	entity:addComponent(graphicsComponent)

	local graphicsArgs = args.graphics or {}
	
	--set our physics relation
	graphicsComponent:setPhysicsRelation(physicsComponent)
	
	--get our drawable key
	local key = graphicsArgs.key or ""
	graphicsComponent:setDrawableKey(key)
	local index = graphicsArgs.index or 0
	graphicsComponent:setIndex(index)

	--collision component
	local collisionComponent = kf.CollisionComponent("sprite-collision")
	obj.collision = collisionComponent
	entity:addComponent(collisionComponent)
	
	local collisionArgs = args.collision or {}
	
	--set our physics relation
	collisionComponent:setPhysicsRelation(physicsComponent)

	--set our type and parameters
	collisionComponent:setType(collisionArgs.type or "CIRCLE")
	collisionComponent:setRadius(collisionArgs.radius or 0)
	collisionComponent:setWidth(collisionArgs.width or 0)
	collisionComponent:setHeight(collisionArgs.height or 0)
	
	local coll_origin = collisionArgs.origin or {0,0,0}
	collisionComponent:setOrigin(kf.Vector3(
									 coll_origin[1],
									 coll_origin[2],
									 coll_origin[3]))

	kf.EntityManager():addEntity(entity)
	return obj
end

function sprite:getName() 
	return self.entity:getName()
end

return sprite
