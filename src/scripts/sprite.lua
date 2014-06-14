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
	local entity = kf.Entity(args.name or "sprite")
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
	local key = graphicsArgs.key or "default"
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

--[[

	generates a sprite from an existing entity

	this would be used to convert an entity being passed from say, a
	message, into a sprite object
	
	contenders for the sprite wrapper:

	- has one physics component
	- has one collision component
	- has one graphcis component

	that's about it
]]
function sprite:get(entity)
	obj = {}
	setmetatable(obj, self)
	self.__index = self

	obj.entity = entity
	
	--assign our physics component
	local physicsComponent = entity:getComponentsByFamily("PHYSICS")[1]
	obj.physics = physicsComponent
	
	--assign our graphics component
	local graphicsComponent = entity:getComponentsByFamily("GRAPHICS")[1]
	obj.graphics = graphicsComponent

	--assign our collision component
	local collisionComponent = entity:getComponentsByFamily("COLLISION")[1]
	obj.collision = collisionComponent

	return obj
end

function sprite:getName() 
	return self.entity:getName()
end

-- physics methods

function sprite:translate(x,y)
	x = x or 0
	y = y or 0
	local z = 0
	local vec = kf.Vector3(x,y,z)

	local physics = self.physics
	local position = physics:getPosition()
	position = position + vec
	physics:setPosition(position)
end

function sprite:getPosition()
	local physics = self.physics
	local position = physics:getPosition()
	return {
		position.x, position.y, 
	}
end

function sprite:setPosition(x, y)
	--other form is x --> table
	if type(x) == "table" and #x == 2 then
		y = x[2]
		x = x[1]
	end

	x = x or 0
	y = y or 0

	local physics = self.physics
	local vec = kf.Vector3(x, y, 0)

	physics:setPosition(vec)
end

function sprite:getVelocity()
	local physics = self.physics
	local velocity = physics:getVelocity()
	return {
		velocity.x, velocity.y
	}
end

function sprite:setVelocity(x, y)
	--other form is x --> table
	if type(x) == "table" and #x == 2 then
		y = x[2]
		x = x[1]
	end

	x = x or 0
	y = y or 0

	local physics = self.physics
	local vec = kf.Vector3(x, y, 0)

	physics:setVelocity(vec)
end

function sprite:getAcceleration()
	local physics = self.physics
	local acceleration = physics:getAcceleration()
	return {
		acceleration.x, acceleration.y
	}
end

function sprite:setAcceleration(x, y)
	--other form is x --> table
	if type(x) == "table" and #x == 2 then
		y = x[2]
		x = x[1]
	end

	x = x or 0
	y = y or 0

	local physics = self.physics
	local vec = kf.Vector3(x, y, 0)

	physics:setAcceleration(vec)
end

function sprite:getDamping()
	local physics = self.physics
	return physics:getDamping()
end

function sprite:setDamping(val)
	local physics = self.physics
	physics:setDamping(val)
end

-- graphics methods

function sprite:getDrawableKey()
	local graphics = self.graphics
	return graphics:getDrawableKey()
end

function sprite:setDrawableKey(drawableKey)
	local graphics = self.graphics
	graphics:setDrawableKey(drawableKey)
end

return sprite
