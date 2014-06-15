--[[

	This is a module that contains physics related wrappers, and a
	suggestion of common force generators that can be applied to physical objects

	One limitation to force generators, is it applies to 'collision
	components' and not physics components. This was a difficult
	design choice to make the force generator more powerful with more
	complex scenarios.

]]

local physicsRegistry = kf.PhysicsRegistry()

local physics = {}

--[[

	Represents an added force generator, that operates on the full
	list of 'collidables'. Note that collidables typically hold a
	reference to a physics component as a reference in
	c:getPhysicsRelation()

	func = function(collidables, time_ms)

]]

physics.addForceGenerator = function(name, func)
	physicsRegistry:addForceGenerator(name, func)
end

physics.registerComponent = function(name, component)
	--
end



return physics
