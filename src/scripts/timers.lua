--[[
	
	This is a module that contains timer functions that can be used to
	perform different kinds of timing operations.

	


]]

local events = require "events"

local timers = {}

local timeManager = kf.TimeManager()
local ruleMachine = kf.getRuleMachine()
--[[ 

	Creates an event timer, and performs the timerCallback upon the
	timer being completed

	timerCallback = function()

]]

__timers = {}

timers.createEventTimer = function(msDelay, timerCallback)
	--append a new timer to our time manager
	local timeGuid = timeManager:appendTime(msDelay)
	function conditionFunction(msg)
		if msg:getType() == "TIMER" and timeGuid == msg:get("timeGuid"):get() then
			return true
		end
		return false
	end
	function timerCallbackWrapper(msg)
		timerCallback()

		--remove the timer object from our time manager once we're done with it
		local timeGuid = msg:get("timeGuid"):get()
		kf.TimeManager():removeTime(timeGuid)
	end

	local ruleID = ruleMachine.addRule(conditionFunction,
									   timerCallbackWrapper)

	return ruleID
end

--[[
	
	Creates an interval timer. It calls the same function each time at
	a given interval

]]

timers.createEventInterval = function(msDelay, intervalCallback)
	intervalCallbackWrapper = function()
		intervalCallback()
		timers.createEventTimer(msDelay, intervalCallbackWrapper)
	end
	local ruleID = timers.createEventTimer(msDelay, intervalCallbackWrapper)
	return ruleID
end
	
return timers
