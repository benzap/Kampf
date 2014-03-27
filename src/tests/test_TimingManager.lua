require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"TimeManager",
	function()
		local timeManager = kf.TimeManager()
		local currentTime = kf.getTick()
		local timeInactive = timeManager:appendTime()
		local timeInactive2 = timeManager:appendTime()
		print(timeInactive2, timeManager:getTime(timeInactive2))		

		kf.delay(1000)

		local timeTuple = {
			guid = timeInactive,
			time = timeManager:getTime(timeInactive)
		}

		test_assert("getTime", timeTuple.time == currentTime)
		test_assert("hasTime", timeManager:hasTime(timeTuple.guid))

		timeManager:removeTime(timeTuple.guid)
		test_assert("removeTime", not timeManager:hasTime(timeTuple.guid))

		print(timeInactive, timeManager:getTime(timeInactive))
		print(timeInactive2, timeManager:getTime(timeInactive2))
		print("test: ", timeTuple.time, timeManager:getTime(timeInactive))


		local newTime = timeManager:getTime(timeInactive2)
		timeManager:extendTime(timeInactive2, 500)
	
		test_assert("extendTime", timeManager:getTime(timeInactive2) == newTime + 500)

		local ruleMachine = kf.getRuleMachine();
end)
