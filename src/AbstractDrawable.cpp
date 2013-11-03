#include "AbstractDrawable.hpp"

AbstractDrawable::AbstractDrawable(stringType type) : type(type) {

}

AbstractDrawable::~AbstractDrawable() {

}

const stringType& AbstractDrawable::getType() {
  return this->type;
}
