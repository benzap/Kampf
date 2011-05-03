----Libraries
require('msgpack')
json = require('json')

----Initial variables

--Extensions
local outputExtension_vectors = ".kv"
local outputExtension_faces = ".kf"
local outputExtension_normals = ".kn"
local outputExtension_textures = ".kt"
local outputExtension_materials = ".km"

--Output Directories
local outputDirectory = "./"

----Functions

--Just shows a help message
function error_showHelp()
   print("importOBJ [importFile (OBJ)]\n")
end

--function makes sure the file exists and can be read from
-- returns boolean
function fileExists(filename)
   if not filename then return false end
   check, eMessage = io.open(filename, 'r')
   if check then 
      io.close(check)
      return true
   else
      print(eMessage)
      return false
   end
end

--string manipulation: strips the given string from the beginning and
--ending of the file, if nothing is given, it strips spaces from the
--given string. 
-- returns the modifed string
function string.strip(_s, _n)
   local n = _n or " "
   local s = _s
   if s == nil then return nil end

   while string.find(s,"^" .. n) do
      s = string.sub(s,2,-1)
   end
   while string.find(s,n .. "$") do
      local sLen = string.len(s)
      s = string.sub(s,1,sLen-1)
   end
   return s
end

--string manipulation: splits the given string up into an array of
--strings based on the given delimiter, currently only works with spaces
-- returns array
function string.split(_s, _n)
   local n = _n or " "
   local s = _s
   if s == nil then return nil end
   local array = {}
   local index
   local tempString
   while true do
      s = string.strip(s,n)
      index = string.find(s,n,1,true)
      
      if not index then
	 array[#array+1] = s
	 return array
      end

      tempString = string.sub(s,1,index-1)
      array[#array+1] = tempString
      s = string.sub(s,index,-1)
   end
end

----START


local arg = {unpack(arg)}

--make sure there are enough args
if #arg < 1 then
   print("Not enough arguments\n")
   error_showHelp()
   os.exit(1)
end

local inputFile = unpack(arg)
local path
do
   i = string.find(inputFile,"/%w+.%w+$")
   path = string.sub(inputFile,1,i)
end

--make sure input file exists and has the right extension .obj
if fileExists(inputFile) then
   do
      local testString = string.lower(inputFile)
      local index = string.find(testString,".obj$")
      if not index then
	 print("WARNING: input file '" .. inputFile .. "' doesn't have the correct extension (OBJ)\n")
      end
   end
else
   os.exit(1)
end

--setup files to be read
inputFileHandle = io.open(inputFile, 'r')

io.input(inputFileHandle)

--begin

local objectName = ''
local groupName = ''

local materialProperties = {} -- table for storing material properties

local outputFileVectorHandle -- vectors
local outputFileFacesHandle -- faces
local outputFileNormalsHandle -- normals
local outputFileTexturesHandle -- textures
local outputFileMaterialHandle -- materials


local materialName -- temp variable for material properties
local temp, tempMat -- a temporary variable
for line in inputFileHandle:lines() do
   if string.find(line,"^#") then
      print(line)

   elseif string.find(line,"^mtllib%s") then
      --Process material properties and store in the materialProperties table
      temp = string.split(line)
      table.remove(temp,1)
      
      for i,v in ipairs(temp) do
	 if string.find(v,"%w+%.mtl$") then
	    materialName = string.match(v,"%w+%.mtl$")
	    materialFileHandle = io.open(path .. materialName,'r')
	    if materialFileHandle ~= nil then
	       for lineMat in materialFileHandle:lines() do
		  if string.find(lineMat,"^newmtl%s") then
		     materialName = string.split(lineMat)
		     materialName = string.strip(materialName[2])
		     materialProperties[materialName] = {}

		  elseif string.find(lineMat,"^Ka%s") then --ambient colour
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].ambientColor = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].ambientColor[i] = tonumber(tempMat[i])
		     end

		  elseif string.find(lineMat,"^Kd%s") then --diffuse colour
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].diffuseColor = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].diffuseColor[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^Ks%s") then --specular colour
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].specularColor = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].specularColor[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^Ns%s") then --specular coefficient
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].specularCoefficient = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].specularCoefficient[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^Ni%s") then --optical density
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].opticalDensity = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].opticalDensity[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^d%s") or string.find(lineMat,"^Tr%s")  then --transparency
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].transparency = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].transparency[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^illum%s") then --Illumination
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].illumination = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].illumination[i] = tonumber(tempMat[i])
		     end
		  elseif string.find(lineMat,"^map_Ka%s") then --ambient texture map
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].ambientTextureMap = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].ambientTextureMap[i] = tempMat[i]
		     end
		  elseif string.find(lineMat,"^map_Kd%s") then --diffuse texture map
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].diffuseTextureMap = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].diffuseTextureMap[i] = tempMat[i]
		     end
		  elseif string.find(lineMat,"^map_Ks%s") then --specular texture map
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].specularTextureMap = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].specularTextureMap[i] = tempMat[i]
		     end
		  elseif string.find(lineMat,"^map_d%s") then --alpha texture map
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].alphaTextureMap = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].alphaTextureMap[i] = tempMat[i]
		     end
		  elseif string.find(lineMat,"^map_bump%s") or string.find(lineMat,"^bump%s") then --bump map
		     tempMat = string.split(lineMat)
		     table.remove(tempMat,1)
		     
		     materialProperties[materialName].bumpTextureMap = {}
		     for i in pairs(tempMat) do
			materialProperties[materialName].bumpTextureMap[i] = tempMat[i]
		     end --END if i in pairs(tempMat) do
		  end --END if string.find(lineMat,"^map_bump%s") or ... 
	       end --END for lineMat in materialFileHandle:lineMats do
	    else
	       error("couldn't find material file")
	    end --END if materialFileHandle then
	 end --END if string.find(v,"%w+%.mtl$") then
      end --END for i,v in ipairs(temp) do
      
   elseif string.find(line,"^g%s") then
      --set group name
      temp = string.split(line)
      table.remove(temp,1)
      for i in pairs(temp) do
	 if i == 1 then
	    groupName = groupName .. temp[i]
	 elseif i > 1 then
	    groupName = groupName .. "_" .. temp[i]
	 end
      end
      
      if groupName == '' then
	 print("ERROR: no group name provided in '" .. inputFile .. "'\n")
	 os.exit(1)
      end

   elseif string.find(line,"^o%s") then
      --set object name
      temp = string.split(line)
      table.remove(temp,1)
      for i in pairs(temp) do
	 if i == 1 then
	    objectName = objectName .. temp[i]
	 elseif i > 1 then
	    objectName = objectName .. "_" .. temp[i]
	 end
      end
      
      if objectName == '' then
	 print("ERROR: no object name provided in '" .. inputFile .. "'\n")
	 os.exit(1)
      end
      
      local name
      if groupName == '' then 
	 name = objectName
      else
	 name = groupName .. "__" .. objectName
      end
      outputFileVectorHandle = io.open(path .. name .. outputExtension_vectors, 'wb')
      print(path .. name .. outputExtension_vectors .. " created")
      outputFileFacesHandle = io.open(path .. name .. outputExtension_faces, 'wb')
      print(path .. name .. outputExtension_faces .. " created")
      outputFileNormalsHandle = io.open(path .. name .. outputExtension_normals, 'wb')
      print(path .. name .. outputExtension_normals .. " created")
      outputFileTexturesHandle = io.open(path .. name .. outputExtension_textures, 'wb')
      print(path .. name .. outputExtension_textures .. " created")
      outputFileMaterialHandle = io.open(path .. name .. outputExtension_materials, 'w')
      print(path .. name .. outputExtension_materials .. " created")

   elseif string.find(line,"^v%s") then
      temp = string.split(line)
      table.remove(temp,1)

      local x = tonumber(temp[1])
      local y = tonumber(temp[2])
      local z = tonumber(temp[3])
      local w = temp[4] == nil and 1.0 or temp[4]
      
      outputFileVectorHandle:write(msgpack.pack(x,y,z,w))

   elseif string.find(line,"^vt%s") then
      --pass
   elseif string.find(line,"^vn%s") then
      --pass
   elseif string.find(line,"^usemtl") then
      temp = string.split(line)
      table.remove(temp,1)
      local theMaterial = materialProperties[temp[1]]
      if not theMaterial then error(temp[1] .. " doesn't exist") end
      outputFileMaterialHandle:write(json.encode(theMaterial))
      
   elseif string.find(line,"^s%s") then
      --pass
   elseif string.find(line,"^f%s") then
      -- currently will only support tri's and quad's
      temp = string.split(line)
      table.remove(temp,1)

      local vertex = {}
      local texture = {}
      local normal = {}
      for i,f in ipairs(temp) do
	 --vertex only
	 if string.find(f,"^%w+$") then
	    vertex[i] = tonumber(string.match(f,"%a*(%d+)"))
	    texture[i],normal[i] = 0.0,0.0
	 --vertex and texture coordinate
	 elseif string.find(f,"^%w+/%w+$") then
	    local v,t = string.match(f,"%a*(%d+)/%a*(%d+)")
	    vertex[i] = tonumber(v)
	    texture[i] = tonumber(t)
	    normal[i] = 0.0
	 --vertex, texture coordinate and normal
	 elseif string.find(f,"^%w+/%w+/%w+$") then
	    local v,t,n = string.match(f,"%a*(%d+)/%a*(%d+)/%a*(%d+)")
	    vertex[i] = tonumber(v)
	    texture[i] = tonumber(t)
	    normal[i] = tonumber(n)
	 --vertex and normal
	 elseif string.find(f,"^%w+//%w+$") then
	    local v,n = string.match(f,"%a*(%d+)//%a*(%d+)")
	    vertex[i] = tonumber(v)
	    texture[i] = 0.0
	    normal[i] = tonumber(n)
	 end
	 
	 if #vertex == 3 then
	    vertex[4],texture[4],normal[4] = 0.0,0.0,0.0
	 end
      end
      --write them to the file
      for i = 1,4 do
	 outputFileFacesHandle:write(msgpack.pack(vertex[i],texture[i],normal[i]))
      end
   end --END if string.find(line, ... OBJ
end --END for line in inputFileHandle:lines() do



os.exit(0)
