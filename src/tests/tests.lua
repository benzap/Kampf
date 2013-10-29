print "UNIT_TESTS"
local _testnum = 1
local function test_case(msg, func)
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

local function test_assert(msg, cond)
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

test_case(
	"Vector",
	function ()
		local vec_i = kf.Vector(1,0,0)
		local vec_j = kf.Vector(0,1,0)
		local vec_k = kf.Vector(0,0,1)
		local vec = vec_i % vec_j
		test_assert("Cross-1", vec == kf.Vector(0,0,1))

		local vec = vec_j % vec_k
		test_assert("Cross-2", vec == kf.Vector(1,0,0))
		
		local vec = kf.Vector(1,2,3) * kf.Vector(1,1,1)
		test_assert("Dot-1", vec == 6)
		
		local vec = kf.Vector(1,2,3) * 2
		test_assert("Scalar-1", vec == kf.Vector(2,4,6))

		local vec = kf.Vector(1,2,3)
		test_assert("grab x - 1", vec.x == 1)
		test_assert("grab y - 1", vec.y == 2)
		test_assert("grab z - 1", vec.z == 3)

		test_assert("grab x - 2", vec[1] == 1)
		test_assert("grab y - 2", vec[2] == 2)
		test_assert("grab z - 2", vec[3] == 3)

		local vec = kf.Vector(1,2,3)
		test_assert("addition", vec+1 == kf.Vector(2,3,4))
		test_assert("negation", -vec == kf.Vector(-1,-2,-3))
		
		local vec = kf.Vector()

		vec.x = 1
		test_assert("set x - 1", vec.x == 1)
		vec[1] = 2
		test_assert("set x - 2", vec[1] == 2)
		
		vec.y = 1
		test_assert("set y - 1", vec.y == 1)
		vec[2] = 2
		test_assert("set y - 2", vec[2] == 2)

		vec.z = 1
		test_assert("set z - 1", vec.z == 1)
		vec[3] = 2
		test_assert("set z - 2", vec[3] == 2)

		local vec = kf.Vector(1,2,3)
		vec = vec:compProd(kf.Vector(2,2,2))
		test_assert("compProd", vec == kf.Vector(2,4,6))

		local vec = kf.Vector(1,2,1)
		local mag = vec:magnitude()
		test_assert("magnitude", mag == 6)
		
		local mag = vec:magnitude_real()
		test_assert("mag real", vec.magnitude_real ~= nil)
end)

test_case(
	"Quaternion",
	function()
		local quat = kf.Quaternion(1,2,3,4)
		test_assert("Quaternion Init", (quat))

		quat = quat + kf.Quaternion(1,1,1,1)
		test_assert("Add", quat == kf.Quaternion(2,3,4,5))

		local quat = kf.Quaternion()
		quat.w = 1
		test_assert("grab w - 1", quat.w == 1)
		quat.x = 2
		test_assert("grab x - 1", quat.x == 2)
		quat.y = 3
		test_assert("grab y - 1", quat.y == 3)
		quat.z = 4
		test_assert("grab z - 1", quat.z == 4)

		quat[1] = 2
		test_assert("grab w - 2", quat[1] == 2)
		quat[2] = 3
		test_assert("grab x - 2", quat[2] == 3)
		quat[3] = 4
		test_assert("grab y - 2", quat[3] == 4)
		quat[4] = 5
		test_assert("grab z - 2", quat[4] == 5)

		local quat = kf.Quaternion(1,2,3,4)
		test_assert("negation", -quat == kf.Quaternion(-1,-2,-3,-4))
		
		test_assert("length", #quat == 4)
		local quat = kf.Quaternion(2,2,2,2)
		test_assert("unit", quat:unit() == kf.Quaternion(0.5,0.5,0.5,0.5))

		local quat = kf.Quaternion(1,1,1,1)
		test_assert("quat product", quat*kf.Quaternion(1,1,1,1) == 4)

		local quat = kf.Quaternion(1,1,1,1)
		test_assert("quat conj", quat:conj() == kf.Quaternion(1,-1,-1,-1))
		test_assert("quat inv", quat:inv() == kf.Quaternion(0.25,-0.25,-0.25,-0.25))

end)
