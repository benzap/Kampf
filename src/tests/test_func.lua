require "utils"
local func = require "func"
local unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"func",
	function()
		
		local t1 = {"Hello", "World!"}
		
		t1_lower = func.map(t1, string.lower)
		test_assert("map", table.eq(t1_lower, {"hello", "world!"}))

		local t2 = func.range(1,6)

		test_assert("range", table.eq(t2, {1,2,3,4,5,6}))

		t2_even = func.filter(t2, 
							  function(a) 
								  return (a % 2) == 0 and true or false 
		end)

		test_assert("filter", table.eq(t2_even, {2,4,6}))

		local t3 = func.range(2,6,2)
		
		test_assert("first", func.first(t3) == 2)
		test_assert("last", func.last(t3) == 6)
		test_assert("rest", table.eq(func.rest(t3), {4,6}))
		
		--Just assuming these work
		--table.print(func.keys(t3))
		--table.print(func.values(t3))

		function person(first, last) 	
			return {
				first = first,
				middle = "test",
				last = last,
			}
		end

		local t4 = {
			person("Ben", "Zaporzan"),
			person("Amanda", "Zaporzan"),
			person("Jon", "Kivinen"),
		}
		
		test_assert("any", func.any(t4, function(a) return a.first == "Ben" end))
		test_assert("any (false)", not func.any(t4, function(a) return a.first == "Toot!" end))
		test_assert("all", func.all(t4, function(a) return a.middle == "test" end))
		test_assert("all (false)", not func.all(t4, function(a) return a.first == "Ben" end))
		
		local ben = func.find(t4, function(a) return a.first == "Ben" end)
		local bert = func.find(t4, function(a) return a.first == "Bert" end)
		test_assert("find", ben.first == "Ben" and ben.last == "Zaporzan") 
		test_assert("find (false)", bert == nil)

		local zaporzans = func.findall(t4, function(a) return a.last == "Zaporzan" end)
		test_assert("findall", #zaporzans == 2)

		
		
end)
