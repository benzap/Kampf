#include "SDLDrawable.hpp"

SDLDrawable::SDLDrawable() :
    AbstractDrawable(SDL_DRAWABLE) {
    
}

SDLDrawable::SDLDrawable(SDL_Surface* surface,
			 SDLRenderWindow* windowContext) :
    AbstractDrawable(SDL_DRAWABLE),
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

    auto viewport = this->windowContext->getViewport();
    floatType widthFactor = this->windowContext->getScaledWidthFactor();
    floatType heightFactor = this->windowContext->getScaledHeightFactor();
    
    auto textureWidth = sourceRectangle->w;
    auto textureHeight = sourceRectangle->h;

    SDL_Rect outputRect;
    outputRect.x = (position.x - viewport->x) * widthFactor;
    outputRect.y = (position.y - viewport->y) * heightFactor;
    outputRect.w = textureWidth * widthFactor;
    outputRect.h = textureHeight * heightFactor;

    // std::cout << "outputrect:" << outputRect.x << " ";
    // std::cout << outputRect.y << " ";
    // std::cout << outputRect.w << " ";
    // std::cout << outputRect.h << std::endl;	

    SDL_RenderCopy(windowContext->getRenderer(),
		   texture, 
		   this->sourceRectangle,
		   &outputRect);
    
    return 0;
}

void SDLDrawable::setRect(SDL_Rect* rect) {
    *this->sourceRectangle = *rect;
}

void SDLDrawable::setRect(integerType x, integerType y, 
			  integerType w, integerType h) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    *this->sourceRectangle = rect;
}



const SDL_Rect* SDLDrawable::getRect() {
    return sourceRectangle;
}

void SDLDrawable::setColorKey(unsigned short r,
			      unsigned short g,
			      unsigned short b) {
    //the pixel format
    auto format = surface->format;
    //generating the color for the color key
    auto colorKey = SDL_MapRGB(format, r, g, b);

    //setting the key
    SDL_SetColorKey(surface, SDL_TRUE, colorKey);

    SDL_DestroyTexture(this->texture);
    this->texture = SDL_CreateTextureFromSurface(
	windowContext->getRenderer(),
	surface);   
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

SDLDrawable SDLDrawable::clone(boolType bDeepReference) {
    SDLDrawable drawable = SDLDrawable(this->surface, this->windowContext);
    return drawable;
}
