require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"FontManager",
	function ()
		local fontManager = kf.SDLFontManager()
		local font = fontManager:addFont("Inconsolata-normal-12",
										 "../fonts/Inconsolata-Regular.ttf",
										 12)

		test_assert("hasFont", fontManager:hasFont("Inconsolata-normal-12"))
end)

test_case(
	"SDLFont",
	function()
		local fontManager = kf.SDLFontManager()
		local font = fontManager:getFont("Inconsolata-normal-12")
		

end)
