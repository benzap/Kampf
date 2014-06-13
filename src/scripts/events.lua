--[[
	
	This ia a module containing wrappers around good portions of the
	kf.RuleMachine, to make it easier to setup event callbacks within
	the game engine.
	
	This makes developing a game within kampf more intuitive, and
	provides a much simpler level of abstraction.
	
]]
local func = require "func"

local events = {}

--Check if we're running in the kampf lua script engine
if not kf then error("This script must be run using the kampf engine lua instantiation") end

local ruleMachine = kf.getRuleMachine()
local timeManager = kf.TimeManager()

--[[
	We attach an event listener to a provided entity, for the provided
	eventName the eventCallback is what is called when the event is
	triggered for the given entity

	eventCallback = function(kf.Message msg)

	passing in an entityName of '*all*' will return for all events by
	the given name

	returns a rule id, which can be passed to removeEventListener to
	remove the given rule

]]

events.createEventListener = function(eventName, entityName, eventCallback)
	return ruleMachine.addRule(
		function(msg)
			--first, check if it's the event we're looking for
			if msg:getType():upper() == eventName:upper() then
				--check if we want all events
				if entityName:lower() == "*all*" then
					return true
				else
					local theEntity = msg:getFirstEntity()
					if entityName == theEntity:getName() then
						return true
					end
				end
			end
		end,
		eventCallback)
end

-- Removes the event from the rule machine with the given id
events.removeEventListener = function(eventId)
	ruleMachine:removeRule(eventId)
end

--[[
	Used to listen to the mouse movements
	
	mouseCallback = function(int x, int y)
]]
events.createMouseMoveListener = function(mouseCallback)
	-- we're wrapping our mouseCallback into the rule machine
	function mouseCallbackWrapper(msg)
		local scaleFactor = kf.getRenderWindow():getScaleFactor();
		local xPosition = msg:get("x"):get() / scaleFactor[1]
		local yPosition = msg:get("y"):get() / scaleFactor[2]

		mouseCallback(xPosition, yPosition)
	end

	return events.createEventListener("MOUSE_MOVE", "*all*", mouseCallbackWrapper)
end

--[[
	Used to listen to collisions on a specific entity, given by the entity name.

	beginCollisionCallback(thisEntity, thisCollisionComponent, args)

	args contains several extra arguments:
	- args.secondEntity : the entity it collided within
	- args.secondCollisionComponent : the collision component collided with
]]

events.createCollisionListener = function(entityName, beginCollisionCallback, endCollisionCallback)
	function collisionCallbackWrapper(msg)
		local bRegistered = msg:get("bRegistered"):get()
		local thisEntity = msg:getFirstEntity()
		local secondEntity = msg:getSecondEntity()
		local args = {
			firstCollisionComponent = msg:getFirstComponent(),
			secondCollisionComponent = msg:getSecondComponent(),
		}

		if bRegistered == 1 then
			beginCollisionCallback(thisEntity, secondEntity, args)
		else
			endCollisionCallback(thisEntity, secondEntity, args)
		end
	end

	return events.createEventListener("COLLISION", entityName, collisionCallbackWrapper)
end


return events
