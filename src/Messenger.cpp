#include "Messenger.hpp"

Messenger::Messenger() {

}

Messenger::~Messenger() {

}

Message& Messenger::appendMessage() {
  auto msg = Message(this->messageIncrement++);
  this->messages.push_back(msg);
  return this->messages.back();
}

const messageContainer& Messenger::retrieveMessages() {
  return this->messages;
}

void Messenger::clearMessages() {
  this->messages.clear();
  this->messageIncrement = 0;
}

