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

    auto textureWidth = sourceRectangle->w;
    auto textureHeight = sourceRectangle->h;

    SDL_Rect outputRect;

    outputRect.x = (position.x - viewport->x) * (floatType) width / resolution->w * (floatType) viewport->w / width;
    outputRect.y = (position.y - viewport->y) * (floatType) height / resolution->h * (floatType) viewport->h / height;
    outputRect.w = textureWidth * (floatType) width / resolution->w * 
	viewport->w / width;
    outputRect.h = textureHeight * (floatType) height / resolution->h *
	viewport->h / height;

    std::cout << "Drawing:" << std::endl;
    std::cout << "outputrect:" << outputRect.x << " ";
    std::cout << outputRect.y << " ";
    std::cout << outputRect.w << " ";
    std::cout << outputRect.h << std::endl;
	

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
    std::vector<int> textureSize = {
	surface->w, surface->h 
    };
    
    return textureSize;
}
