--[[
	Includes a series of useful utilities
]]

--checks if two tables are equal to eachother
function table.eq(firstTable, secondTable)
	for firstIndex, value in pairs(firstTable) do
		if secondTable[firstIndex] ~= value then
			return false
		end
	end
	return true
end
