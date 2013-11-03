#ifndef GRAPHICSSYSTEM__HPP
#define GRAPHICSSYSTEM__HPP
//DESCRIPTION
/*
  Graphics system handles the drawing and display of graphics
 */

//CLASSES

//INCLUDES
#include "AbstractSystem.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class GraphicsSystem : public AbstractSystem {
private:
  
public:
  GraphicsSystem();
  virtual ~GraphicsSystem();

  void createMessages();
  void process();
};


#endif //END GRAPHICSSYSTEM__HPP
