unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"Vector3",
	function ()
		local vec_i = kf.Vector3(1,0,0)
		local vec_j = kf.Vector3(0,1,0)
		local vec_k = kf.Vector3(0,0,1)
		local vec = vec_i % vec_j
		test_assert("Cross-1", vec == kf.Vector3(0,0,1))

		local vec = vec_j % vec_k
		test_assert("Cross-2", vec == kf.Vector3(1,0,0))
		
		local vec = kf.Vector3(1,2,3) * kf.Vector3(1,1,1)
		test_assert("Dot-1", vec == 6)
		
		local vec = kf.Vector3(1,2,3) * 2
		test_assert("Scalar-1", vec == kf.Vector3(2,4,6))

		local vec = kf.Vector3(1,2,3)
		test_assert("grab x - 1", vec.x == 1)
		test_assert("grab y - 1", vec.y == 2)
		test_assert("grab z - 1", vec.z == 3)

		test_assert("grab x - 2", vec[1] == 1)
		test_assert("grab y - 2", vec[2] == 2)
		test_assert("grab z - 2", vec[3] == 3)

		local vec = kf.Vector3(1,2,3)
		test_assert("addition", vec+1 == kf.Vector3(2,3,4))
		test_assert("negation", -vec == kf.Vector3(-1,-2,-3))
		
		local vec = kf.Vector3()

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

		local vec = kf.Vector3(1,2,3)
		vec = vec:compProd(kf.Vector3(2,2,2))
		test_assert("compProd", vec == kf.Vector3(2,4,6))

		local vec = kf.Vector3(1,2,1)
		local mag = vec:magnitude()
		test_assert("magnitude", mag == 6)
		
		local mag = vec:magnitude_real()
		test_assert("mag real", vec.magnitude_real ~= nil)
end)
