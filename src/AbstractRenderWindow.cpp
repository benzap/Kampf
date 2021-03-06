#include "AbstractRenderWindow.hpp"

AbstractRenderWindow::AbstractRenderWindow(int windowWidth, int windowHeight) : 
  windowWidth(windowWidth), windowHeight(windowHeight) {
  
}

AbstractRenderWindow::~AbstractRenderWindow() {
  
}

const std::vector<int> AbstractRenderWindow::getWindowSize() {
    //not implemented
    return {0, 0};
}

void AbstractRenderWindow::setWindowSize(floatType w, floatType h) {
    //not implemented
    std::cout << "Abstract: setWindowSize not implemented" << std::endl;
}

const Viewport* AbstractRenderWindow::getViewport() {
    return &(this->viewport);
}

void AbstractRenderWindow::setViewport(Viewport viewport) {
    this->viewport = viewport;
}

void AbstractRenderWindow::setViewport(integerType x,
				       integerType y,
				       integerType w,
				       integerType h) {
    this->viewport.x = x;
    this->viewport.y = y;
    this->viewport.w = w;
    this->viewport.h = h;
}

const Resolution* AbstractRenderWindow::getResolution() {
    return &this->resolution;
}

void AbstractRenderWindow::setResolution(floatType w, floatType h) {
    std::cout << "set resolution" << std::endl;
    this->resolution.w = w;
    this->resolution.h = h;
}

floatType AbstractRenderWindow::getScaledWidthFactor() {
    std::cout << "Not Implemented: AbstractRenderWindow::getScaledWidthFactor" << std::endl;
    return 0;
}

floatType AbstractRenderWindow::getScaledHeightFactor() {
    std::cout << "Not Implemented: AbstractRenderWindow::getScaledHeightFactor" << std::endl;
    return 0;
}

void AbstractRenderWindow::setRenderClearColor(unsigned char r,
					       unsigned char g,
					       unsigned char b,
					       unsigned char a) {
    RenderClearColor renderClearColor = {
	r,g,b,a
    };
    this->renderClearColor = renderClearColor;
}

const RenderClearColor& AbstractRenderWindow::getRenderClearColor() {
    return this->renderClearColor;
}
