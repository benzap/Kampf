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
    return &this->viewport;
}

void AbstractRenderWindow::setViewport(Viewport viewport) {
    this->viewport = viewport;
}
