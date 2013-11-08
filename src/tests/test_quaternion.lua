unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

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
