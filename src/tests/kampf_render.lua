require "utils"

function createPacman()
	local entity = kf.Entity("pacman")
	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)

	graphicsComponent:setDrawableKey("pacman")
	physicsComponent:setPosition(kf.Vector3(0, 0, 0))

	return entity
end

local pacman = createPacman()
local assetManager = kf.SDLAssetManager()
assetManager:addBMP("pacman", "./assets/pacman.bmp")

local entityManager = kf.EntityManager()
entityManager:addEntity(pacman)

local renderWindow = kf.getRenderWindow()
renderWindow:setWindowSize(1000, 800)
renderWindow:setResolution(200, 200)
renderWindow:setViewport{
	x = 0,
	y = 0,
	w = 200,
	h = 200,
}

local ruleMachine = kf.getRuleMachine()
print(ruleMachine)

function ruleCond(msg)
	if msg:getType() == "MOUSE_MOVE" then
		return true
	end
	return false
end

function ruleFunc(msg)
	local xPosition = msg:get("x"):get()
	local yPosition = msg:get("y"):get()
	
	local phys = pacman:getComponentsByFamily("PHYSICS")[1]
	phys:setPosition(kf.Vector3(xPosition-50, yPosition-50, 0))
end

--ruleMachine.addRule(ruleCond, ruleFunc)


kf.runMainLoop(20000)

