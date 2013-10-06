#ifndef MESENGER__HPP
#define MESENGER__HPP
//DESCRIPTION
/*
  The messaging class for taking messages.
 */

//INCLUDES
#include <vector>

#include "KF_globals.hpp"
#include "KF_utilities.hpp"
#include "Message.hpp"

//CLASSES
class Messenger;
//DEFINITIONS

//MACROS

//TYPEDEFS
typedef std::vector<Message> messageContainer;

//FUNCTIONS

//BEGIN
class Messenger {
private:
  incrementType messageIncrement = 0;
  messageContainer messages;
public:
  Messenger();
  virtual ~Messenger();
  
  Message& appendMessage();
  const messageContainer& retrieveMessages();
  void clearMessages();
};

#endif //END MESENGER__HPP
