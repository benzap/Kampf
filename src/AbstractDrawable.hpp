#ifndef ABSTRACTDRAWABLE__HPP
#define ABSTRACTDRAWABLE__HPP
//DESCRIPTION
/*!
  @file AbstractDrawable.hpp
  @brief Abstract for all drawables

  the drawable, which is an object representing something to be drawn
  on the screen. This includes things like sprites, 3d models, or
  text.
*/

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "KF_math.hpp"

//CLASSES
class AbstractDrawable;

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class AbstractDrawable {
private:
    //! The string representing the type of the drawable
    stringType type;

public:
    //! drawable constructor
    /*!

      @param type the string representing the type of drawable
     */
    AbstractDrawable(stringType type);
    virtual ~AbstractDrawable();

    //! The function is used to draw the given drawable
    /*!
      
      @param position The vector position that the drawable will be
      drawn at
      @param orientation The orientation of the given drawable on the
      screen.
     */
    virtual int draw(Vector3 position = Vector3(), 
		     Quaternion orientation = Quaternion()) = 0;

    //! Returns a string representing the type of drawable
    const stringType& getType();
};

#endif //END ABSTRACTDRAWABLE__HPP
