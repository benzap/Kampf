require "utils"

local renderWindow = kf.getRenderWindow()
renderWindow:setWindowTitle("Test Collision")
renderWindow:setWindowIcon("./assets/platformer/png/alien_plant.png")

function createBlock(name, position)
	assert(type(name) == "string", "first argument should be a string")
	assert(kf.isVector3(position), "second argument should be a kf.Vector3")

	local entity = kf.Entity(name)
	
	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(position)

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setPhysicsRelation(physicsComponent)
	graphicsComponent:setDrawableKey("block-dirt")
	graphicsComponent:setIndex(50)

	local collisionComponent = kf.CollisionComponent("collidable")
	entity:addComponent(collisionComponent)
	collisionComponent:setPhysicsRelation(physicsComponent)
	collisionComponent:setType("AABB")
	collisionComponent:setWidth(70)
	collisionComponent:setHeight(70)
	
	return entity
end

-- create and add our assets
local assetManager = kf.SDLAssetManager()
asset_block_rock = assetManager:addImage("block-rock", "./assets/platformer/png/ground_rock.png")
asset_block_dirt = assetManager:addImage("block-dirt", "./assets/platformer/png/ground_dirt.png")

local entityManager = kf.EntityManager()
local block0_id = entityManager:addEntity(createBlock("block-0", kf.Vector3(0,0,0)))
local block1_id = entityManager:addEntity(createBlock("block-1", kf.Vector3(70.01,0,0)))
local pointer_id = entityManager:addEntity(createBlock("pointer", kf.Vector3(200,200,0)))

local ruleMachine = kf.getRuleMachine()

function ruleCond(msg)
	if msg:getType() == "MOUSE_MOVE" then
		return true
	end
	return false
end

function ruleFunc(msg)

	local scaleFactor = renderWindow:getScaleFactor();

	local xPosition = msg:get("x"):get() / scaleFactor[1]
	local yPosition = msg:get("y"):get() / scaleFactor[2]
	
	local pointer = entityManager:getEntityByID(pointer_id)

	local phys = pointer:getComponentsByFamily("PHYSICS")[1]
	phys:setPosition(kf.Vector3(xPosition-35, yPosition-35, 0))
end
ruleMachine.addRule(ruleCond, ruleFunc)

--Testing collision system
--Pointer response to colliding with blocks
ruleMachine.addRule(
	function (msg)
		if msg:getType() == "COLLISION" then
			--check if the pacman is the first entity
			local entity = msg:getFirstEntity()
			if entity:getName() == "pointer" then
				return true
			end
		end
		return false
	end,
	function (msg)
		--need to perform different actions for when it's registering
        --and unregistering
		local bRegistered = msg:get("bRegistered"):get()
		
		local pointer = msg:getFirstEntity()
		local block = msg:getSecondEntity()

		if bRegistered == 1 then
			print(pointer:getName() .. " collided with " .. block:getName())
		else
			print(pointer:getName() .. " stopped colliding with " .. block:getName())
		end
end)

--block response to colliding
ruleMachine.addRule(
	function (msg)
		if msg:getType() == "COLLISION" then
			--check if it's a block
			local entity = msg:getFirstEntity()
			if string.find(entity:getName(), "^block") then
				print("Block: ", entity:getName())
				return true
			end
		end

		return false
	end,
	function (msg)
		local bRegistered = msg:get("bRegistered"):get()
		
		local block = msg:getFirstEntity()
		print("Collision: ", block:getName())

		local graphicsComponent = block:getComponentsByFamily("GRAPHICS")[1]
		if bRegistered == 1 then
			graphicsComponent:setDrawableKey("block-rock")
		else
			graphicsComponent:setDrawableKey("block-dirt")
		end
end)


kf.runMainLoop();
