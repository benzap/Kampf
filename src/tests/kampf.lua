print("Initializing Kampf Test Engine")

for i,v in pairs(_G) do
	if i:match("^KF.") then
		print(i, " - ", v)
	end
end

for i,v in pairs(kf) do
	print(i,v)
end

local ruleMachine = kf.getRuleMachine()

function ruleCond(msg)
	return true
end

function ruleFunc(msg)
	print(msg:getType())
end

ruleMachine.addRule(ruleCond, ruleFunc)
