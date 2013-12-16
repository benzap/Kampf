#include <iostream>
#include <cassert>

#include "KF_test.hpp"

Entity* create_pacman() {
    auto entity = new Entity("pacman");
    
    //pacman needs a position, which can be defined with a physics
    //component. The graphics system also tries to find a physics
    //component in order to draw the graphics component correctly
    auto physicsComponent = createPhysicsComponent("physics");
    entity->addComponent(physicsComponent);
    
    physicsComponent->setPosition({100,100,0});

    auto graphicsComponent = createGraphicsComponent("graphics");
    entity->addComponent(graphicsComponent);

    //the keyname of the drawable that this component refers to
    graphicsComponent->setDrawableKey("pacman");

    return entity;
}

int main(int argc, char *argv[]) {
  TEST_NAME("test_SDLAssetManager.cpp");
  auto kampf = Kampf(enumInitType::Basic); 
  // auto lua = kampf.getLua();
  // lua->loadScript(KF_INIT_FILE);
    
  auto assetManager = SDLAssetManager::getInstance();
  assetManager->addBMP("pacman", "assets/pacman.bmp");

  TEST_BOOL(assetManager->hasDrawable("pacman"), "hasDrawable true");
  TEST_BOOL(!assetManager->hasDrawable("batmat"), "hasDrawable false");

  //removing drawable
  assetManager->removeDrawable("pacman");
  TEST_BOOL(!assetManager->hasDrawable("pacman"), "removeDrawable");

  //reading the drawable
  SDL_Rect pacmanSize = {0, 0, 100, 100};
  assetManager->addBMP("pacman", "assets/pacman.bmp", &pacmanSize);
  
  //creating an entity that holds pacman image/sprite
  auto pacman = create_pacman();

  auto entityManager = EntityManager::getInstance();
  entityManager->addEntity(pacman);

  auto window = kampf.getWindowContext();
  window->setViewport(100, 100, 800, 600);

  kampf.runMainLoop(5000);
  return 0;
}

