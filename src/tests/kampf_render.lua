require "utils"

function createPacman()
	local entity = kf.Entity("pacman")

	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(kf.Vector3(0, 0, 0))

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setPhysicsRelation(physicsComponent)
	graphicsComponent:setDrawableKey("pacman")
	graphicsComponent:setIndex(50)

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
	graphicsComponent:setPhysicsRelation(physicsComponent)
	graphicsComponent:setDrawableKey("red-circle")
	graphicsComponent:setIndex(10)

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
	graphicsComponent:setPhysicsRelation(physicsComponent)
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

local redPhysics = redCircle:getComponentsByFamily("PHYSICS")[1]
local blueCircle = createBlueCircle()
blueCircle:getComponentsByFamily("PHYSICS")[1]:setPosition(kf.Vector3(100,100,0)) 

local assetManager = kf.SDLAssetManager()

local asset_pacDrawable = assetManager:addImage("pacman", "./assets/pacman.png")
asset_pacDrawable:setColorKey(255, 255, 255)
local rect = asset_pacDrawable:getRect()

local asset_redCircle = assetManager:addImage("red-circle", "./assets/red_circle.png")
asset_redCircle:setColorKey(255, 255, 255)

local asset_blueCircle = assetManager:addImage("blue-circle", "./assets/blue_circle.png")
asset_blueCircle:setColorKey(255, 255, 255)

local entityManager = kf.EntityManager()
entityManager:addEntity(pacman)
entityManager:addEntity(redCircle)
entityManager:addEntity(blueCircle)

local renderWindow = kf.getRenderWindow()
renderWindow:setWindowSize(800, 600)
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
--Pacman response to colliding with circles
ruleMachine.addRule(
	function (msg)
		if msg:getType() == "COLLISION" then
			--check if the pacman is the first entity
			local entity = msg:getFirstEntity()
			if entity:getName() == "pacman" then
				return true
			end
		end
		return false
	end,
	function (msg)
		--need to perform different actions for when it's registering
        --and unregistering
		local bRegistered = msg:get("bRegistered"):get()
		
		local pacman = msg:getFirstEntity()
		local circle = msg:getSecondEntity()

		if bRegistered == 1 then
			print(pacman:getName() .. " collided with " .. circle:getName())
		else
			print(pacman:getName() .. " stopped colliding with " .. circle:getName())
		end
end)

--red circle response to colliding
ruleMachine.addRule(
	function (msg)
		if msg:getType() == "COLLISION" then
			--check if the pacman is the first entity
			local entity = msg:getFirstEntity()
			if entity:getName() == "red-circle" then
				return true
			end
		end
		return false
	end,
	function (msg)
		--need to perform different actions for when it's registering
        --and unregistering
		local bRegistered = msg:get("bRegistered"):get()
		
		local circle = msg:getFirstEntity()

		local graphicsComponent = circle:getComponentsByFamily("GRAPHICS")[1]
		if bRegistered == 1 then
			graphicsComponent:setDrawableKey("blue-circle")
		else
			graphicsComponent:setDrawableKey("red-circle")
		end
end)

--blue circle response to colliding
ruleMachine.addRule(
	function (msg)
		if msg:getType() == "COLLISION" then
			--check if the pacman is the first entity
			local entity = msg:getFirstEntity()
			if entity:getName() == "blue-circle" then
				return true
			end
		end
		return false
	end,
	function (msg)
		--need to perform different actions for when it's registering
        --and unregistering
		local bRegistered = msg:get("bRegistered"):get()
		
		local circle = msg:getFirstEntity()

		local graphicsComponent = circle:getComponentsByFamily("GRAPHICS")[1]
		if bRegistered == 1 then
			graphicsComponent:setDrawableKey("red-circle")
		else
			graphicsComponent:setDrawableKey("blue-circle")
		end
end)

local toggleCircle = createRedCircle()
toggleCircle:setName("toggleCircle")
toggleCircle:getComponentsByFamily("PHYSICS")[1]:setPosition(kf.Vector3(400,400,0))
entityManager:addEntity(toggleCircle)
local toggleDrawable = toggleCircle:getComponentsByFamily("GRAPHICS")[1]


--test out the time manager
local bToggleColor = false
local toggleDelay = 1000
local toggleTimer = kf.TimeManager():appendTime(toggleDelay)
ruleMachine.addRule(
	function(msg)
		if msg:getType() == "TIMER" then
			local timeGuid = msg:get("timeGuid"):get()
			if (timeGuid == toggleTimer) then
				return true
			end
		end
		return false
	end,
	function(msg)
		if bToggleColor then
			toggleDrawable:setDrawableKey("red-circle")
		else
			toggleDrawable:setDrawableKey("blue-circle")
		end
		bToggleColor = not bToggleColor
		
		--remove the old timer
		kf.TimeManager():removeTime(toggleTimer)

		--append a new timer
		toggleTimer = kf.TimeManager():appendTime(toggleDelay)
end)

--Testing Physics System
redPhysics:setVelocity(kf.Vector3(500.0, 300.0, 0.0))
redPhysics:setAcceleration(kf.Vector3(0, 300, 0))
redPhysics:setDamping(0.9)

--lets add a secondary collision system so that the ball stays within
--the bounds

kf.addSystem("CollisionBounds",
			 --[[
				 Create Messages, we aren't creating 
				 any messages so this is empty
			 ]]
			 function()	end,

			 --Process Messages, we're checking the bounds of our
			 --redPhysics ball.
			 function()
				 local ballPosition = redPhysics:getPosition()
				 local xPosition = ballPosition[1]
				 local yPosition = ballPosition[2]
				 
				 local windowSize = kf.getRenderWindow():getResolution()
				 local width = windowSize[1]
				 local height = windowSize[2]

				 
				 local velocity = redPhysics:getVelocity()
				 local acceleration = redPhysics:getAcceleration()
				 local redRadius = 50
				 if xPosition + redRadius*2 > width then
					 velocity.x = -velocity.x
					 redPhysics:setVelocity(velocity)
				 end

				 if xPosition < 0 then
					 velocity.x = -velocity.x
					 redPhysics:setVelocity(velocity)
				 end
					 
				 if yPosition + redRadius*2 > height then
					 velocity.y = -velocity.y
					 redPhysics:setVelocity(velocity)
				 end

				 if yPosition < 0 then
					 velocity.y = -velocity.y
					 redPhysics:setVelocity(velocity)
				 end
			 end
)


kf.runMainLoop(-1)
