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

physics.gravity = {0, 20, 0}

physics.addForceGenerator = function(name, func)
	local forceGenerator = kf.ForceGenerator(
		name,
		func)
	physicsRegistry:addForceGenerator(forceGenerator)
end

physics.registerComponent = function(generatorName, component)
	if physicsRegistry:hasForceGenerator(generatorName) then
		local forceGenerator = physicsRegistry:getForceGenerator(generatorName)
		if kf.isCollisionComponent(component) then
			forceGenerator:registerComponent(component)
		else
			error("second parameter must be a collision component", 2)
		end
	else
		error("first parameter does not name a generator in the physics registry", 2)
	end
end

physics.unregisterComponent = function(generatorName, component)
	local forceGenerator = physicsRegistry:getForceGenerator(generatorName)
	forceGenerator:unregisterComponent(component)
end



return physics
