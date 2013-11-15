local ruleMachine = kf.getRuleMachine()
print(ruleMachine)

function ruleCond(msg)
	print("lua: rule condition")
	print(msg:getType())
	return false
end

function ruleFunc(msg)
	print("lua: rule function")
end

ruleMachine.addRule(ruleCond, ruleFunc)

kf.runMainLoop(5000)
