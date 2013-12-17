print("Initializing Kampf Test Engine")

for i,v in pairs(_G) do
	if i:match("^KF.") then
		print(i, " - ", v)
	end
end

for i,v in pairs(kf) do
	print(i,v)
end

print("--Initializing Rule Machine")
local ruleMachine = kf.getRuleMachine()

print("--Rule Condition")
function ruleCond(msg)
	return true
end

print("--Rule Function")
function ruleFunc(msg)
	local msgType = msg:getType()
	if msgType == "KEYBOARD" then
		print(msg:get("Key"):getString())
	end
	print(msg:getType())
end

print("--ruleMachine.addRule")
ruleMachine.addRule(ruleCond, ruleFunc)

print("--Running...")

print ("--Running tests--")
tests = require "tests"
