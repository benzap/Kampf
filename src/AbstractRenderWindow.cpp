#include "AbstractRenderWindow.hpp"

AbstractRenderWindow::AbstractRenderWindow(int windowWidth, int windowHeight) : 
  windowWidth(windowWidth), windowHeight(windowHeight) {
  
}

AbstractRenderWindow::~AbstractRenderWindow() {
  
}

const std::vector<int> AbstractRenderWindow::getWindowSize() {
    
}

void AbstractRenderWindow::setWindowSize(floatType w, floatType h) {
    
}

const Viewport* AbstractRenderWindow::getViewport() {
    return &(this->viewport);
}

void AbstractRenderWindow::setViewport(Viewport viewport) {
    this->viewport = viewport;
}

const Resolution* AbstractRenderWindow::getResolution() {
    return &this->resolution;
}

void AbstractRenderWindow::setResolution(floatType w, floatType h) {
    this->resolution.w = w;
    this->resolution.h = h;
}
