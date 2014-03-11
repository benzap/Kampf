require "utils"

function createPacman()
	local entity = kf.Entity("pacman")

	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(kf.Vector3(0, 0, 0))

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setDrawableKey("pacman")

	local collisionComponent = kf.CollisionComponent("collidable")
	entity:addComponent(collisionComponent)
	collisionComponent:setPhysicsRelation(physicsComponent)
	collisionComponent:setType("CIRCLE")
	collisionComponent:setOrigin(kf.Vector3(50, 50, 0))
	collisionComponent:setRadius(50)
	
	return entity
end

function createRedCircle()
	local entity = kf.Entity("red-circle")

	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(kf.Vector3(0, 0, 0))

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setDrawableKey("red-circle")

	local collisionComponent = kf.CollisionComponent("collidable")
	entity:addComponent(collisionComponent)
	collisionComponent:setPhysicsRelation(physicsComponent)
	collisionComponent:setType("CIRCLE")
	collisionComponent:setOrigin(kf.Vector3(50, 50, 0))
	collisionComponent:setRadius(50)
	
	return entity
end

function createBlueCircle()
	local entity = kf.Entity("blue-circle")

	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(kf.Vector3(0, 0, 0))

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setDrawableKey("blue-circle")

	local collisionComponent = kf.CollisionComponent("collidable")
	entity:addComponent(collisionComponent)
	collisionComponent:setPhysicsRelation(physicsComponent)
	collisionComponent:setType("CIRCLE")
	collisionComponent:setOrigin(kf.Vector3(50, 50, 0))
	collisionComponent:setRadius(50)
	
	return entity
end




local pacman = createPacman()
local redCircle = createRedCircle()
local blueCircle = createBlueCircle()
blueCircle:getComponentsByFamily("PHYSICS")[1]:setPosition(kf.Vector3(100,100,0)) 

local assetManager = kf.SDLAssetManager()

local asset_pacDrawable = assetManager:addBMP("pacman", "./assets/pacman.bmp")
asset_pacDrawable:setColorKey(255, 255, 255)

local asset_redCircle = assetManager:addBMP("red-circle", "./assets/red_circle.bmp")
asset_redCircle:setColorKey(255, 255, 255)

local asset_blueCircle = assetManager:addBMP("blue-circle", "./assets/blue_circle.bmp")
asset_blueCircle:setColorKey(255, 255, 255)

local entityManager = kf.EntityManager()
entityManager:addEntity(pacman)
entityManager:addEntity(redCircle)
entityManager:addEntity(blueCircle)

local renderWindow = kf.getRenderWindow()
renderWindow:setWindowSize(1000, 600)
renderWindow:setResolution(800, 600)
renderWindow:setViewport{
	x = 0,
	y = 0,
	w = 800,
	h = 600,
}

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
	
	local phys = pacman:getComponentsByFamily("PHYSICS")[1]
	phys:setPosition(kf.Vector3(xPosition-50, yPosition-50, 0))
end

ruleMachine.addRule(ruleCond, ruleFunc)

--Testing collision system

ruleMachine.addRule(
	function (msg)
		print (msg:getType())
		if msg:getType() == "COLLISION" then
			print "Collision!"
			return true
		end
		return false
	end,
	function (msg)
		print "Collision inner"
end)




kf.runMainLoop(20000)
