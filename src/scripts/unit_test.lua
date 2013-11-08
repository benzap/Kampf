--[[

	Contains functions for performing unit tests
	
]]

local unit_test = {}

local _testnum = 1
unit_test.test_case = function(msg, func)
	local testMsg = "TEST_CASE #" .. _testnum .. ": " .. msg
	print(testMsg .. " - STARTED")

	status, err = pcall(func)
	if status then
		testMsg = testMsg .. " - PASSED"
	else
		testMsg = testMsg .. " - FAILED"
	end
	print(testMsg)
	if not status then
		print("ERROR: " .. err)
	end
	print("")
	_testnum = _testnum + 1
end

unit_test.test_assert = function(msg, cond)
	local testMsg = " - " .. msg .. " - "
	if cond then
		testMsg = testMsg .. "PASSED"
		print(testMsg)
	else
		testMsg = testMsg .. "FAILED"
		print(testMsg)
		
		local debugInfo = debug.getinfo(2)
		local errorMsg = "Assertion --> " .. msg .. " "
		errorMsg = errorMsg .. debugInfo.short_src
		errorMsg = errorMsg .. ":" .. debugInfo.currentline
		--errorMsg = errorMsg .. msg
		error(errorMsg)
	end
end

return unit_test
