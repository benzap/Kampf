#include "Message.hpp"

Message::Message(incrementType id) : id(id) {
  
}

Message::~Message() {
  
}

incrementType Message::getID() {
  return this->id;
}

enumMessageType Message::getType() {
  return this->type;
}

void Message::setType(enumMessageType type) {
  this->type = type;
}
