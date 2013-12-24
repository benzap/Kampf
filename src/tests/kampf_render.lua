require "utils"

function createPacman()
	local entity = kf.Entity("pacman")
	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)

	graphicsComponent:setDrawableKey("pacman")
	physicsComponent:setPosition(kf.Vector3(100, 100, 0))

	return entity
end

local pacman = createPacman()
local assetManager = kf.SDLAssetManager()
assetManager:addBMP("pacman", "./assets/pacman.bmp")

local entityManager = kf.EntityManager()
entityManager:addEntity(pacman)

local renderWindow = kf.getRenderWindow()
--renderWindow:setWindowSize(800, 600)
renderWindow:setResolution(200, 200)
kf.runMainLoop(5000)
