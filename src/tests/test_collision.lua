require "utils"
local sprite = require "sprite"
local events = require "events"
local func = require "func"


local renderWindow = kf.getRenderWindow()
renderWindow:setWindowTitle("Test Collision")
renderWindow:setWindowIcon("./assets/platformer/png/alien_plant.png")

function createBlock(name, position)
	local block = sprite:new{
		name = name,
		physics = {
			position = position,
		},
		graphics = {
			key = "block-dirt",
			index = 1,
		},
		collision = {
			type = "AABB",
			width = 70,
			height = 70,
		},
	}
	return block
end

-- create and add our assets
local assetManager = kf.SDLAssetManager()
asset_block_rock = assetManager:addImage("block-rock", "./assets/platformer/png/ground_rock.png")
asset_block_dirt = assetManager:addImage("block-dirt", "./assets/platformer/png/ground_dirt.png")

local blocks = {}
--local block0 = createBlock("block-0", {0, 0})
--local block1 = createBlock("block-1", {70.01, 0})
local pointer = createBlock("pointer", {200, 200})
print(kf.isPhysicsComponent(pointer.physics))

local inc = 0
for i = 0,800,70 do
	for j = 0,600,70 do
		table.insert(blocks, createBlock("block-" .. inc, {i,j}))
		inc = inc + 1
	end
end


events.createKeyListener(
	function(key, bKeyDown)
		
		if key == "left" then
			
			
		end
end)

events.createMouseMoveListener(
	function(x,y)
		pointer:setPosition(x,y)
end)

--Testing collision system
--Pointer response to colliding with blocks
events.createCollisionListener(
	"pointer",
	function(first, second, _)
		local pointer = sprite:get(first)
		local block = sprite:get(second)

		print(pointer:getName() .. " collided with " .. block:getName())
	end,
	function(first, second, _)
		local pointer = sprite:get(first)
		local block = sprite:get(second)

		print(pointer:getName() .. " stopped colliding with " .. block:getName())
end)

--block response to colliding
events.createCollisionListener(
	"block",
	function(first, second, args)
		local block = sprite:get(first)
		local second = sprite:get(second)
		if second:getName() == "pointer" then
			block:setDrawableKey("block-rock")
		end
	end,
	function(first, second, args)
		local block = sprite:get(first)
		local second = sprite:get(second)
		if second:getName() == "pointer" then
			block:setDrawableKey("block-dirt")
		end
end)

kf.runMainLoop();
