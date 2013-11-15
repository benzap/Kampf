local ruleMachine = kf.getRuleMachine()
print(ruleMachine)

function ruleCond(msg)
	print("lua: rule condition")
	return false
end

function ruleFunc(msg)
	print("lua: rule function")
end

ruleMachine.addRule(ruleCond, ruleFunc)
print("hello")

kf.runMainLoop(5)
