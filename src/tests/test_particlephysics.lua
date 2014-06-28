require "utils"
local func = require "func"
local events = require "events"
local timers = require "timers"
local sprite = require "sprite"
local text = require "text"
local physics = require "physics"

-- ASSETS

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

--having issues with this function in linux
if KF_OS ~= "LINUX" then
	renderWindow:setClearColor(17,17,17)
end

local __text_increment = 0
function createText(x,y)
	local text = text:new{
		name = "textlabel_" .. __text_increment,
		font = "Inconsolata-normal-12",
		physics = {
			position = {x, y}
		},
		graphics = {
			index = 50,
		},
	}
	__text_increment = __text_increment + 1
	return text
end

local padding = 5
local font_size = 12
local label_penetration = createText(padding, padding)
label_penetration:setText("Penetration: ")
local label_normal = createText(padding, padding + font_size)
label_normal:setText("Contact Normal: ")
local label_time = createText(padding, padding + font_size * 2)
label_time:setText("Time: ")
local label_time_collision = createText(padding, padding + font_size * 3)
label_time_collision:setText("Time Collision: ")

local redCircle = sprite:new{
	name = "red-circle",
	physics = {
		position = {200, 200, 0},
		velocity = {0, 0, 0},
		acceleration = {0, 0, 0},
		damping = 0.95,
		mass = 1,
		elasticity = 1.0,
		type = "PARTICLE",
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
		position = {400, 200, 0},
		damping = 0.95,
		mass = 1,
		elasticity = 1.0,
		type = "PARTICLE",
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

events.createKeyListener(
	function(key, bKeyDown)
		accelerationValue = 100
		if bKeyDown then
			if key == "left" then
				redCircle:setAcceleration(-accelerationValue, 0)
			elseif key == "right" then
				redCircle:setAcceleration(accelerationValue, 0)
			elseif key == "space" then
				redCircle:setPosition(200, 200)
			end
		else
			redCircle:setAcceleration(0, 0)
		end		
end)

events.createCollisionListener(
	"red.circle",
	function(circle, _, args)
		label_penetration:setText("Penetration: " .. args.penetration)
		label_normal:setText("Contact Normal: " .. tostring(args.contactNormal))
		label_time_collision:setText("Time Collision: " .. kf.getTick())
	end,
	function(circle, _, args)
		
end)

timers.createEventInterval(
	100,
	function()
		--label_time_collision:setText("Time: ", kf.getTick())
end)

kf.addSystem(
	"Time Label Update",
	function() end,
	function()
		--label_time:setText("Time: ", kf.getTick())
end)

kf.runMainLoop()
