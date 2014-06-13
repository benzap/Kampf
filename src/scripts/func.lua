--[[

	This is a module that contains a lot of utility functions that
	resemble undersore.js.

	The functions are typically used on tables

]] 

local func = {}

func.range = function(s, e, inc)
	local t = {}
	local index = 1;
	inc = inc or 1
	for i = s,e,inc do
		table.insert(t, index, i)
		index = index + 1
	end
	return t
end

func.map = function(t, f) 
	local resultTable = {}
	for i,v in ipairs(t) do
		resultTable[i] = f(v)
	end
	return resultTable
end

func.filter = function(t, f)
	local resultTable = {}
	for i,v in ipairs(t) do
		if f(v) then 
			table.insert(resultTable, v)
		end
	end
	return resultTable
end

func.reduce = function(t, f)
	local result = t[i]
	for i,v in ipairs(func.rest(t)) do
		result = f(result, t[i])
	end
	return result
end

func.find = function(t, f)
	for i,v in ipairs(t) do
		if f(v) then
			return v
		end
	end
	return nil
end

func.findall = function(t, f)
	local resultTable = {}
	for i,v in ipairs(t) do
		if f(v) then
			table.insert(resultTable, v)
		end
	end
	return resultTable
end

func.contains = function(t, val)
	for i,v in ipairs(t) do
		if v == val then
			return true
		end
	end
	return false
end

func.any = function(t, f)
	for i,v in ipairs(t) do
		if f(v) then return true end
	end
	return false
end

func.all = function(t, f)
	for i,v in ipairs(t) do
		if not f(v) then return false end
	end
	return true
end

func.first = function(t)
	return t[1]
end

func.rest = function(t)
	local resultTable = {}
	for i=2,#t do
		table.insert(resultTable, t[i])
	end
	return resultTable
end

func.last = function(t)
	return t[#t]
end

func.keys = function(t)
	local resultTable = {}
	for i,v in pairs(t) do
		table.insert(resultTable, i)
	end
	return resultTable
end

func.values = function(t)
	local resultTable = {}
	for i,v in pairs(t) do
		table.insert(resultTable, v)
	end
	return resultTable
end

func.has = function(t, val)
	for i,v in pairs(t) do
		if v == val then return true end
	end
	return false
end

return func
