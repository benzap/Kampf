#include "SDLRenderWindow.hpp"

SDLRenderWindow::SDLRenderWindow(int windowWidth, int windowHeight) :
    AbstractRenderWindow(windowWidth, windowHeight) {
  
}

SDLRenderWindow::~SDLRenderWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void SDLRenderWindow::draw(AbstractDrawable* drawable, 
			   Vector3 position,
			   Quaternion orientation) {
    if (drawable->getType() == "SDL") {
	SDLDrawable* sdl_drawable = static_cast<SDLDrawable*> (drawable);
	sdl_drawable->setWindowContext(this);
	sdl_drawable->draw(position,
			   orientation);
    }
}

boolType SDLRenderWindow::update() {
    SDL_RenderPresent(renderer);
    return true;
}

boolType SDLRenderWindow::clear() {
    RenderClearColor renderClearColor = this->getRenderClearColor();
    SDL_SetRenderDrawColor(renderer,
			   renderClearColor.r,
			   renderClearColor.g,
			   renderClearColor.b,
			   renderClearColor.a);
    SDL_RenderClear(renderer);
    return true;
}

bool SDLRenderWindow::initialize() {
    SDL_InitSubSystem(SDL_INIT_VIDEO);

    this->window = SDL_CreateWindow(this->windowTitle.c_str(),
				    this->xPosition,
				    this->yPosition,
				    this->windowWidth,
				    this->windowHeight,
				    this->windowFlags);
  
    this->renderer = SDL_CreateRenderer(this->window, -1,
					this->rendererFlags);
    return true;
}

bool SDLRenderWindow::reinitialize() {
    return true;
}

void SDLRenderWindow::setWindowFlags(Uint32 windowFlags) {
    this->windowFlags = windowFlags;
}

void SDLRenderWindow::setRendererFlags(Uint32 rendererFlags) {
    this->rendererFlags = rendererFlags;
}

void SDLRenderWindow::setPosition(int xPosition, int yPosition) {
    this->xPosition = xPosition;
    this->yPosition = yPosition;
}

void SDLRenderWindow::setTitle(stringType title) {
    SDL_SetWindowTitle(this->window,
		       title.c_str());
    this->windowTitle = title;
}

stringType SDLRenderWindow::getTitle() {
    stringType title = SDL_GetWindowTitle(this->window);
    return title;
}

SDL_Window* SDLRenderWindow::getWindow() {
    return this->window;
}

SDL_Renderer* SDLRenderWindow::getRenderer() {
    return this->renderer;
}

const std::vector<int> SDLRenderWindow::getWindowSize() {
    int width, height;
    SDL_GetWindowSize(this->window,
		      &width, &height);
    std::vector<int> windowSize = {width, height};
    return windowSize;
}

void SDLRenderWindow::setWindowSize(floatType w, floatType h) {
    std::cout << "set new window size" << std::endl;
    SDL_SetWindowSize(this->window, (int) w, (int) h);
}

floatType SDLRenderWindow::getScaledWidthFactor() {
    int width, height;
    SDL_GetWindowSize(window,
		      &width, &height); 

    //need to fit our drawing to the preferred resolution
    auto viewport = this->getViewport();
    auto resolution = this->getResolution();

    auto result = 1;
    result *= static_cast<floatType>(width);
    result *= static_cast<floatType>(viewport->w);
    result /= (resolution->w * resolution->w);
    
    return result;
}

floatType SDLRenderWindow::getScaledHeightFactor() {
    int width, height;
    SDL_GetWindowSize(this->window,
		      &width, &height); 

    //need to fit our drawing to the preferred resolution
    auto viewport = this->getViewport();
    auto resolution = this->getResolution();

    auto result = 1;
    result *= (floatType) height;
    result *= (floatType) viewport->h;
    result /= (resolution->h * resolution->h);

    return result;
}

void SDLRenderWindow::setWindowIcon(stringType filename) {
    SDL_Surface* sdlSurface = IMG_Load(filename.c_str());
    
    if (sdlSurface != NULL) {
	SDL_SetWindowIcon(this->window, sdlSurface);
	SDL_FreeSurface(sdlSurface);
    }
    else {
	std::cerr << "setWindowIcon - Error: in file - " << filename << std::endl;
	std::cerr << IMG_GetError() << std::endl;
    }
}
