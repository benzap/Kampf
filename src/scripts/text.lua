--[[

	Text representation within lua. Still requires a lot of
	development, but it serves it's original intent just fine

	NOTE: To speed up development of this class, i'm inheriting from sprite

]]

local sprite = require "sprite"

local text = {

}

__increment_text = 0

local assetManager = kf.SDLAssetManager()

function text:new(args)
	--lazy inheritance
	local obj = sprite:new(args)
	obj.setText = text.setText
	obj.setDefaultFont = text.setDefaultFont
	obj.redraw = text.redraw

	--need to redefine how the graphics component works
	local graphicsArgs = args.graphics or {}
	local graphics = obj.graphics
	graphics:setType("SDL_TEXT")

	--text is a rare beast that requires a different area to store the
    --'text snippet'
	obj.textKey = "text-" .. __increment_text
	__increment_text = __increment_text + 1
	obj.textDrawable = assetManager:addText(obj.textKey)
	graphics:setDrawableKey(obj.textKey)

	obj.textString = args.text or " "
	obj.font = args.font or "default"

	obj.textDrawable:appendText(obj.textString, obj.font)

	local collision = obj.collision
	collision:setType("NONE")
	
	return obj
end

function text:setText(text, font)
	text = text or " "
	font = font or self.font

	self.textDrawable:clearText()
	self.textDrawable:appendText(text, font)

	self.textString = Text
end

function text:setDefaultFont(font)
	self.font = font
end

function text:redraw()
	self.textDrawable:redraw()
end

return text
