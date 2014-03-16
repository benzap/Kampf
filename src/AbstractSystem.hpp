#ifndef ABSTRACTSYSTEM__HPP
#define ABSTRACTSYSTEM__HPP
//DESCRIPTION
/*!
  @file AbstractSystem.hpp
  @brief Abstract for all systems

  This is the abstract class for systems, that is inherited for each
  included system. 

  Systems have two functions. The first function is to create messages
  that are placed within the Messenger. 

  The second function is to process messages, that have been
  previously created. The processing of these messages will usually
  lead to the creation of more messages.
*/

//CLASSES
class AbstractSystem;

//INCLUDES
#include "KF_globals.hpp"
#include "KF_utilities.hpp"

//DEFINITIONS

//MACROS

//TYPEDEFS

//FUNCTIONS

//BEGIN
class AbstractSystem {
private:
    //! a string that describes the type of system
    stringType type;

public:
    //! Abstract system constructor
    /*!
      @param type A unique name to describe the system
     */
    AbstractSystem(stringType type);
    virtual ~AbstractSystem();

    //! Overloaded virtual function for creating messages
    virtual void createMessages() = 0;

    //! Overloaded virtual function for processing messages
    virtual void process() = 0;
};


#endif //END ABSTRACTSYSTEM__HPP
