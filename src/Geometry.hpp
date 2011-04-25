#ifndef GEOMETRY_HPP_
#define GEOMETRY_HPP_

/* INCLUDES */
#include <iostream>
#include <vector>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>

#include "Graphics.hpp"

/* CLASSES */

class Geometry;

/* ENUMERATIONS */
enum vectorFileTypes {
  VECTOR_NONE,
  VECTOR_OBJ,
};

enum materialFileTypes {
  MATERIAL_NONE,
  MATERIAL_MTL,
};

enum textureFileTypes {
  TEXTURE_NONE,
  TEXTURE_JPEG,
  TEXTURE_BMP,
  TEXTURE_GIF,
  TEXTURE_PNG,
  TEXTURE_TGA,
};

enum materialIllumination {
  COLOR = 0,
  COLOR_AMBIENCE = 1,
  HIGHLIGHT = 2,
  REFLECTION_RAYTRACE = 3,
  GLASS_RAYTRACE = 4,
  FRESNEL_RAYTRACE = 5,
  REFRACTION_RAYTRACE = 6,
  REFRACTION_FRESNEL_RAYTRACE = 7,
  REFLECTION = 8,
  GLASS = 9,
  CAST_SHADOWS = 10
};

/* DEFINITIONS */


/* TYPEDEFS */
typedef GLfloat vData; //vectors
typedef GLfloat nData; //normals
typedef GLfloat tData; //texture coords.
typedef GLfloat cData; //colours
typedef GLint   orderInt;

typedef std::string stringType;
typedef std::vector<vData> v_vectorArray;
typedef std::vector<nData> v_normalArray;
typedef std::vector<tData> v_textureArray;
typedef std::vector<cData> v_colorArray;
typedef std::vector<orderInt> v_orderArray;

typedef GLfloat matData; //materials

/* STRUCTURES */

typedef struct struct_MaterialProperties {
  stringType sMaterialName;
  stringType sMaterialPath;

  matData aAmbientColor[3];
  matData aDiffuseColor[3];
  matData aSpecularColor[3];
  matData specularCoeff;
  matData trasparencyCoeff;

  materialIllumination eIllumination;

  stringType sAmbienceTexturePath;
  textureFileTypes eAmbienceTextureType;

  stringType sDiffuseTexturePath;
  textureFileTypes eDiffuseTextureType;

  stringType sSpecularTexturePath;
  textureFileTypes eSpecularTextureType;

  stringType sAlphaTexturePath;
  textureFileTypes eAlphaTextureType;

  stringType sBumpTexturePath;
  textureFileTypes eBumpTextureType;

} struct_MaterialProperties;

/* START */

class Geometry: public Graphics {
private:
  //general
  stringType* sGeometryName;
  stringType* sGeometryGroupName;

  //Actual Geometry
  v_vectorArray* vVectors;
  v_normalArray* vNormals;

  stringType* sVectorFilePath;
  vectorFileTypes e_vType;


  //Material Properties
  stringType* sMaterialName;
  stringType* sMaterialFilePath;
  materialFileTypes e_mType;

  struct_MaterialProperties*  structMaterialProperties;

  //Textures Properties
  v_textureArray* vTextures;
  v_colorArray* vColors;

  stringType* sTextureFilePath;
  textureFileTypes e_tType;

  //synthesis
  v_orderArray* vOrdering;

public:
  Geometry();
  Geometry(stringType*);
  Geometry(stringType*, stringType*);

  virtual ~Geometry();
  
  void printStatus();

  CALLBACK execute();

  //general
  CALLBACK setGeometryName(stringType*);
  const stringType* getGeometryName();

  CALLBACK setGeometryGroupName(stringType*);
  const stringType* getGeometryGroupName();


  //Actual Geometry
  CALLBACK setVectorArray(v_vectorArray*);
  const v_vectorArray* getVectorArray();

  CALLBACK setNormalArray(v_normalArray*);
  const v_normalArray* getNormalArray();

  CALLBACK setVectorFilePath(stringType*); //might change this to filestream
  const stringType* getVectorFilePath();

  CALLBACK setVectorFileType(vectorFileTypes);
  const vectorFileTypes getVectorFileType();

  
  //Material Properties
  CALLBACK setMaterialName(stringType*);
  const stringType* getMaterialName();

  CALLBACK setMaterialFilePath(stringType*);
  const stringType* getMaterialFilePath();

  CALLBACK setMaterialFileType(materialFileTypes);
  const materialFileTypes getMaterialFileType();

  CALLBACK setMaterialProperties(struct_MaterialProperties*);
  const struct_MaterialProperties* getMaterialProperties();


  //Texture Properties
  CALLBACK setTextureArray(v_textureArray*);
  const v_textureArray* getTextureArray();

  CALLBACK setColorArray(v_colorArray*);
  const v_colorArray* getColorArray();

  CALLBACK setTextureFilePath(stringType*);
  const stringType* getTextureFilePath();

  CALLBACK setTextureFileType(textureFileTypes);
  const textureFileTypes getTextureFileType();


  //synthesis
  CALLBACK setOrdering(v_orderArray*);
  const v_orderArray* getOrdering();
};

#endif //GEOMETRY_HPP_
