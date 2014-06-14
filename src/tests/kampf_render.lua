require "utils"
local func = require "func"
local events = require "events"
local timers = require "timers"
local sprite = require "sprite"

-- ASSETS
local assetManager = kf.SDLAssetManager()
local asset_pacDrawable = assetManager:addImage("pacman", "./assets/pacman.png")
local asset_redCircle = assetManager:addImage("red-circle", "./assets/red_circle.png")
local asset_blueCircle = assetManager:addImage("blue-circle", "./assets/blue_circle.png")

-- FONTS
local fontManager = kf.SDLFontManager()
local font = fontManager:addFont("Inconsolata-normal-12",
								 "../fonts/Inconsolata-Regular.ttf",
								 12)

--print(font:getRenderType())
font:setRenderType("BLENDED")
font:setFontColor(255, 0, 0, 255)
font:setStyle({
				  bold = true,
				  italic = false,
				  underline = false,
				  strikethrough = false,
})

-- RENDER WINDOW
local renderWindow = kf.getRenderWindow()
renderWindow:setWindowTitle("Kampf Render Testing Grounds")
renderWindow:setWindowIcon("./assets/platformer/png/grass.png")
renderWindow:setWindowSize(800, 600)
renderWindow:setResolution(800, 600)
renderWindow:setViewport{
	x = 0,
	y = 0,
	w = 800,
	h = 600,
}
renderWindow:setClearColor(17,17,17)

local pacman = sprite:new{
	name = "pacman",
	physics = {
		position = {0,0,0},
	},
	graphics = {
		key = "pacman",
		index = 50,
	},
	collision = {
		type = "CIRCLE",
		origin = {50, 50, 0},
		radius = 50,
	}
}

local redCircle = sprite:new{
	name = "red-circle",
	physics = {
		velocity = {500, 300, 0},
		acceleration = {0, 300, 0},
		damping = 0.9,
	},
	graphics = {
		key = "red-circle",
	},
	collision = {
		type = "CIRCLE",
		origin = {50, 50, 0},
		radius = 50,
	},
}

local toggleCircle = sprite:new{
	name = "toggleCircle",
	physics = {
		position = {400, 400, 0},
	},
	graphics = {
		key = "red-circle",
	},
	collision = {
		type = "CIRCLE",
		origin = {50, 50, 0},
		radius = 50,
	},
}

local blueCircle = sprite:new {
	name = "blue-circle",
	physics = {
		position = {100, 100, 0},
	},
	graphics = {
		key = "blue-circle",
	},
	collision = {
		type = "CIRCLE",
		origin = {50, 50, 0},
		radius = 50,
	},
}

local increment = 0
function createText(text, x, y)
	local drawableKey = "text-" .. increment
	increment = increment + 1
	local sdlAssetManager = kf.SDLAssetManager()
	local textDrawable = sdlAssetManager:addText(drawableKey)
	textDrawable:appendText(text, "Inconsolata-normal-12")
	textDrawable:clearText()
	textDrawable:appendText("test", "Inconsolata-normal-12")

	local entity = kf.Entity("text")
	
	local physicsComponent = kf.PhysicsComponent("physical")
	entity:addComponent(physicsComponent)
	physicsComponent:setPosition(kf.Vector3(x, y, 0))

	local graphicsComponent = kf.GraphicsComponent("graphical")
	entity:addComponent(graphicsComponent)
	graphicsComponent:setPhysicsRelation(physicsComponent)
	graphicsComponent:setDrawableKey(drawableKey)
	graphicsComponent:setType("SDL_TEXT")
	return entity
end

--current text system needs to be fixed
local text1 = createText("Hello World!", 100, 100)
kf.EntityManager():addEntity(text1)

events.createMouseMoveListener(
	function(x,y)
		pacman:setPosition(x-50, y-50)
end)

events.createKeyListener(
	function(key, bKeyDown)
		local acceleration = toggleCircle:getAcceleration()

		local accelValue = 1000

		if bKeyDown then
			if key == "left" then
				acceleration[1] = -accelValue
			elseif key == "right" then
				acceleration[1] = accelValue
			elseif key == "up" then
				acceleration[2] = -accelValue
			elseif key == "down" then
				acceleration[2] = accelValue
			end
		else
			if key == "left" then
				acceleration[1] = acceleration[1] + accelValue
			elseif key == "right" then
				acceleration[1] = acceleration[1] - accelValue
			elseif key == "up" then
				acceleration[2] = acceleration[2] + accelValue
			elseif key == "down" then
				acceleration[2] = acceleration[2] - accelValue
			end
		end
				 
		toggleCircle:setDamping(0.5)
		toggleCircle:setAcceleration(acceleration)

		if bKeyDown and key == "space" then
			toggleCircle:setPosition(400,400)
		end


end)

--collision listener for pacman sprite
events.createCollisionListener(
	pacman:getName(),
	function(pacman, second, args)
		print(pacman:getName() .. " collided with " .. second:getName())
	end,
	function(pacman, second, args)
		print(pacman:getName() .. " stopped colliding with " .. second:getName())
end)

--collision listener for red-circle entities
events.createCollisionListener(
	"red-circle",
	function(circle, _, _)
		--creating a sprite from our entity
		local circleSprite = sprite:get(circle)
		circleSprite:setDrawableKey("blue-circle")
	end,
	function(circle, _, _)
		local circleSprite = sprite:get(circle)
		circleSprite:setDrawableKey("red-circle")
end)

--collision listener for blue-circle entities
events.createCollisionListener(
	"blue-circle",
	function(circle, _, _)
		local circleSprite = sprite:get(circle)
		circleSprite:setDrawableKey("red-circle")
	end,
	function(circle, _, _)
		local circleSprite = sprite:get(circle)
		circleSprite:setDrawableKey("blue-circle")
end)

--test out the time manager
local bToggleColor = false
local toggleDelay = 1000
timers.createEventInterval(
	toggleDelay,
	function()
		if bToggleColor then
			toggleCircle:setDrawableKey("red-circle")
		else
			toggleCircle:setDrawableKey("blue-circle")
		end
		bToggleColor = not bToggleColor
end)

local redPhysics = redCircle.physics

--lets add a secondary collision system so that the ball stays within
--the bounds
kf.addSystem(
	"CollisionBounds",
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
end)

-- performing test with text instances
kf.runMainLoop(-1)
