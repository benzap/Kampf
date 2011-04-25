/* INCLUDES */
#include <iostream>

#include "kampf_general.hpp"
#include "Data.hpp"

/* START */



template <class T>
Data<T>::Data(): Object() {
  this->type = DATA;
  this->dataStorage = NULL;
  this->bIsArray = false;
  this->count = 1;
}

template <class T>
Data<T>::Data(T theData, unsigned int _count,  bool bArray): Object() {
  this->type = DATA;
  this->dataStorage = theData;
  this->bIsArray = bArray;
  this->count = _count;
}

template <class T>
Data<T>::~Data() {
  T theData = this->dataStorage;
  if (this->bIsArray) {
  delete [] theData;
  }
  else {
    delete theData;
  }
  theData = NULL;
}

template <class T>
void Data<T>::printStatus() {
  std::cout << "< Data[" << (void*)this << "]";
  std::cout << " type='DATA'";
  std::cout << " name='" << this->getName() << "'";
  std::cout << " number_of_children='" << this->readNumberOfChildren() << "'";
  std::cout << " has_parent='" << this->getParent() << "'";
  std::cout << " >" << std::endl;
}

template <class T>
CALLBACK Data<T>::execute() {
#if DEBUG
  std::cout << "Executing DATA Object" << std::endl;
#endif
  return SUCCESS;
}

template <class T>
CALLBACK Data<T>::setData(T theData) {
  this->dataStorage = theData;
  return SUCCESS;
}

template <class T>
const T Data<T>::getData() {
  return this->dataStorage;
}

template <class T>
CALLBACK Data<T>::deleteData() {
  delete [] this->dataStorage;
}

template <class T>
bool Data<T>::isArray() {
  return this->bIsArray;
}

template <class T>
unsigned int Data<T>::getCount() {
  return this->count;
}

template <class T>
CALLBACK Data<T>::setCount(unsigned int count) {
  this->count = count;
  return SUCCESS;
}


template class Data<int*>;
template class Data<float*>;
template class Data<char*>;
