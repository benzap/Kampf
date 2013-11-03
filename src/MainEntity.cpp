#include "MainEntity.hpp"

MainEntity::MainEntity(stringType name,
		       incrementType id) :
  AbstractEntity(name, id, ENTITY_MAIN_TYPE) {

}

MainEntity::~MainEntity() {}
