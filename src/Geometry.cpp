/* INCLUDES */
#include "Geometry.hpp"

/* START */

Geometry::Geometry(): Graphics() {
  this->type = GEOMETRY;
    
  this->sGeometryName = NULL;
  this->sGeometryGroupName = NULL;
  
  this->vVectors = NULL;
  this->vNormals = NULL;
  
  this->sVectorFilePath = NULL;
  this->e_vType = VECTOR_NONE;

  this->sMaterialName = NULL;
  this->sMaterialFilePath = NULL;
  this->e_mType = MATERIAL_NONE;

  this->structMaterialProperties = NULL;

  this->vTextures = NULL;
  this->vColors = NULL;

  this->sTextureFilePath = NULL;
  this->e_tType = TEXTURE_NONE;

  this->vOrdering = NULL;
}

Geometry::Geometry(stringType* geometryName): Graphics() {
  this->type = GEOMETRY;

  this->sGeometryName = geometryName;
  this->sGeometryGroupName = NULL;
  
  this->vVectors = NULL;
  this->vNormals = NULL;
  
  this->sVectorFilePath = NULL;
  this->e_vType = VECTOR_NONE;

  this->sMaterialName = NULL;
  this->sMaterialFilePath = NULL;
  this->e_mType = MATERIAL_NONE;

  this->structMaterialProperties = NULL;

  this->vTextures = NULL;
  this->vColors = NULL;

  this->sTextureFilePath = NULL;
  this->e_tType = TEXTURE_NONE;

  this->vOrdering = NULL;
}

Geometry::Geometry(stringType* geometryName, stringType* geometryGroup): Graphics() {
  this->type = GEOMETRY;

  this->sGeometryName = geometryName;
  this->sGeometryGroupName = geometryGroup;
  
  this->vVectors = NULL;
  this->vNormals = NULL;
  
  this->sVectorFilePath = NULL;
  this->e_vType = VECTOR_NONE;

  this->sMaterialName = NULL;
  this->sMaterialFilePath = NULL;
  this->e_mType = MATERIAL_NONE;

  this->structMaterialProperties = NULL;

  this->vTextures = NULL;
  this->vColors = NULL;

  this->sTextureFilePath = NULL;
  this->e_tType = TEXTURE_NONE;

  this->vOrdering = NULL;
}

Geometry::~Geometry() {
  //Not likely going to be deleting but dereferencing
}

void Geometry::printStatus() {
  std::cout << "< Geometry[" << (void*)this << "]";
  std::cout << " type='GEOMETRY'";
  std::cout << " name='" << this->getName() << "'";
  std::cout << " number_of_children='" << this->readNumberOfChildren() << "'";
  std::cout << " has_parent='" << this->getParent() << "'";
  std::cout << " >" << std::endl;
}

CALLBACK Geometry::execute() {

}

//general
CALLBACK Geometry::setGeometryName(stringType* theName) {
  this->sGeometryName = theName;
}

const stringType* Geometry::getGeometryName() {
  return this->sGeometryName;
}


CALLBACK Geometry::setGeometryGroupName(stringType* theName) {
  this->sGeometryGroupName = theName;
}

const stringType* Geometry::getGeometryGroupName() {
  return this->sGeometryGroupName;
}


//Actual Geometry
CALLBACK Geometry::setVectorArray(v_vectorArray* theArray) {
  this->vVectors = theArray;
}

const v_vectorArray* Geometry::getVectorArray() {
  return this->vVectors;
}


CALLBACK Geometry::setNormalArray(v_normalArray* theArray) {
  this->vNormals = theArray;
}

const v_normalArray* Geometry::getNormalArray() {
  return this->vNormals;
}


CALLBACK Geometry::setVectorFilePath(stringType* thePath) {
  this->sVectorFilePath = thePath;
}

const stringType* Geometry::getVectorFilePath() {
  return this->sVectorFilePath;
}


CALLBACK Geometry::setVectorFileType(vectorFileTypes theType) {
  this->e_vType = theType;
}

const vectorFileTypes Geometry::getVectorFileType() {
  return this->e_vType;
}


//Material Properties
CALLBACK Geometry::setMaterialName(stringType* theName) {
  this->sMaterialName = theName;
}

const stringType* Geometry::getMaterialName() {
  return this->sMaterialName;
}


CALLBACK Geometry::setMaterialFilePath(stringType* thePath) {
  this->sMaterialFilePath = thePath;
}

const stringType* Geometry::getMaterialFilePath() {
  return this->sMaterialFilePath;
}


CALLBACK Geometry::setMaterialFileType(materialFileTypes theType) {
  this->e_mType = theType;
}

const materialFileTypes Geometry::getMaterialFileType() {
  return this->e_mType;
}

CALLBACK Geometry::setMaterialProperties(struct_MaterialProperties* theProperties) {
  this->structMaterialProperties = theProperties;
}

const struct_MaterialProperties* Geometry::getMaterialProperties() {
  return this->structMaterialProperties;
}

//Texture Properties
CALLBACK Geometry::setTextureArray(v_textureArray* theArray) {
  this->vTextures = theArray;
}

const v_textureArray* Geometry::getTextureArray() {
  return this->vTextures;
}


CALLBACK Geometry::setColorArray(v_colorArray* theArray) {
  this->vColors = theArray;
}

const v_colorArray* Geometry::getColorArray() {
  return this->vColors;
}


CALLBACK Geometry::setTextureFilePath(stringType* thePath) {
  this->sTextureFilePath = thePath;
}

const stringType* Geometry::getTextureFilePath() {
  return this->sTextureFilePath;
}

CALLBACK Geometry::setTextureFileType(textureFileTypes theType) {
  this->e_tType = theType;
}

const textureFileTypes Geometry::getTextureFileType() {
  return this->e_tType;
}

//synthesis
CALLBACK Geometry::setOrdering(v_orderArray* theArray) {
  this->vOrdering = theArray;
}

const v_orderArray* Geometry::getOrdering() {
  return this->vOrdering;
}
