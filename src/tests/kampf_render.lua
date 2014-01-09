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

local pacman = createPacman()
local pacman2 = createPacman()

local assetManager = kf.SDLAssetManager()

local pacDrawable = assetManager:addBMP("pacman", "./assets/pacman.bmp")
pacDrawable:setColorKey(255, 255, 255)

local entityManager = kf.EntityManager()
entityManager:addEntity(pacman)
entityManager:addEntity(pacman2)

local renderWindow = kf.getRenderWindow()
renderWindow:setWindowSize(1000, 600)
renderWindow:setResolution(200, 200)
renderWindow:setViewport{
	x = 0,
	y = 0,
	w = 200,
	h = 200,
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


kf.runMainLoop(20000)

