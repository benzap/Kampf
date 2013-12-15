#include "SDLDrawable.hpp"

SDLDrawable::SDLDrawable() :
    AbstractDrawable("SDL") {
    
}

SDLDrawable::SDLDrawable(SDL_Surface* surface,
			 SDLRenderWindow* windowContext) :
    AbstractDrawable("SDL"),
    windowContext(windowContext),
    surface(surface) {

    this->texture = SDL_CreateTextureFromSurface(
	windowContext->getRenderer(),
	surface);

    if (this->texture == NULL) {
	std::cerr << "Warning: unable to create texture from surface";
	std::cerr << std::endl;
	std::cerr << SDL_GetError() << std::endl;
    }

    auto textureSize = this->getSize();
    this->sourceRectangle = new SDL_Rect();
    this->sourceRectangle->x = 0;
    this->sourceRectangle->y = 0;
    this->sourceRectangle->w = textureSize[0];
    this->sourceRectangle->h = textureSize[1];
}

SDLDrawable::~SDLDrawable() { 
    //SDL_DestroyTexture(texture);
    //delete sourceRectangle;
}

int SDLDrawable::draw(Vector3 position, 
		      Quaternion orientation) {

    //need to fit our drawing to the preferred resolution
    auto viewport = this->windowContext->getViewport();
    auto resolution = this->windowContext->getResolution();
    
    int width, height;
    SDL_GetWindowSize(windowContext->getWindow(),
		      &width, &height);    

    SDL_Rect outputRect;
    outputRect.x = width / resolution->w * (position.x - viewport->x);
    outputRect.y = height / resolution->h * (position.y - viewport->y);
    outputRect.w = width / resolution->w * viewport->w;
    outputRect.h = height / resolution->h * viewport->h;

    // std::cout << "Drawing:" << std::endl;
    // std::cout << "outputrect:" << outputRect.x << " ";
    // std::cout << outputRect.y << " ";
    // std::cout << outputRect.w << " ";
    // std::cout << outputRect.h << std::endl;
	

    SDL_RenderCopy(windowContext->getRenderer(),
		   texture, 
		   this->sourceRectangle,
		   &outputRect);
}

void SDLDrawable::setRect(SDL_Rect* rect) {
    *this->sourceRectangle = *rect;
}

void SDLDrawable::setRect(integerType x, integerType y, 
			  integerType w, integerType h) {
    
}

const SDL_Rect* SDLDrawable::getRect() {
    return sourceRectangle;
}

void SDLDrawable::setWindowContext(SDLRenderWindow* windowContext) {
    this->windowContext = windowContext;
}

std::vector<int> SDLDrawable::getSize() {
    // int textureWidth;
    // int textureHeight;
    // int error = SDL_QueryTexture(texture, NULL, NULL, 
    // 				 &textureWidth, &textureHeight);

    // if (error) {
    // 	std::cerr << "Error - getTextureSize" << std::endl;
    // 	std::cerr << SDL_GetError() << std::endl;
    // }

    std::vector<int> textureSize = {
	surface->w, surface->h 
    };
    
    return textureSize;
}
