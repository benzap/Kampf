--[[

	Includes a set of functions for manipulating the file system

]]

local func = require "func"

local filesystem = {}

--change what our separator is based on the OS
if KF_OS == "WIN32" then
	filesystem.separator = "\\"
else
	filesystem.separator = "/"
end

-- joins the list of table elements into a path
-- ex. {"path", "to", "something"} --> "./path/to/something"
filesystem.join = function(pathTable, bAbsolute)
	local pathString = ""
	if bAbsolute then
		pathString = filesystem.separator
	else
		pathString = "." .. filesystem.separator
	end
	
	--the reduce function
	local reduceFunc = function(a,b)
		return a .. filesystem.separator .. b
	end
	
	pathString = pathString .. func.reduce(
		func.rest(pathTable), reduceFunc)

	return pathString
end
