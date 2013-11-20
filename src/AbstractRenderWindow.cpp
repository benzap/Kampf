#include "AbstractRenderWindow.hpp"

AbstractRenderWindow::AbstractRenderWindow(int windowWidth, int windowHeight) : 
  windowWidth(windowWidth), windowHeight(windowHeight) {
  
}

AbstractRenderWindow::~AbstractRenderWindow() {
  
}

const Resolution* AbstractRenderWindow::getWindowSize() {
    
}

void AbstractRenderWindow::setWindowSize(Resolution resolution) {
    
}

const Resolution* AbstractRenderWindow::getResolution() {
    
}

void AbstractRenderWindow::setResolution(Resolution resolution) {
    
}

const Viewport* AbstractRenderWindow::getViewport() {
    return &this->viewport;
}

void AbstractRenderWindow::setViewport(Viewport viewport) {
    this->viewport = viewport;
}
