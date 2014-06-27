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

local redCircle = sprite:new{
	name = "red-circle",
	physics = {
		position = {200, 200, 0},
		velocity = {0, 0, 0},
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

kf.runMainLoop()
