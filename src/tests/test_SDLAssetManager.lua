require "utils"
unit = require "unit_test"

test_case = unit.test_case
test_assert = unit.test_assert

test_case(
	"SDLAssetManager",
	function ()
		local assetManager = kf.SDLAssetManager()
		test_assert("check existance", assetManager)
		
		local drawable = assetManager:addBMP("pacman",
											 "assets/pacman.bmp")

		test_assert("hasDrawable", assetManager:hasDrawable("pacman") == true)

end)
