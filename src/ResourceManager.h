#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <string>
#include <map>

#include <glad/glad.h>

#include "Shader.h"
#include "Texture.h"

class ResourceManager {
 public:
  // resource storage
  static std::map<std::string, Shader> Shaders;
  static std::map<std::string, Texture2D> Textures;
  // load a shader
  static Shader LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile,
                           std::string name);
  // retrieve a shader
  static Shader& GetShader(std::string name);
  // load a texture
  static Texture2D LoadTexture2D(const char* file, bool bAlpha, std::string name);
  // retrieve a texture
  static Texture2D& GetTexture2D(std::string name);
  // de-allocate resource
  static void Clear();

 private:
  // constructor
  ResourceManager();
  // load a shader from file
  static Shader LoadShaderFromFile(const char* vertexShaderFile, const char* fragmentShaderFile,
                                   const char* geometryShaderFile = nullptr);
  // load a texture from file
  static Texture2D LoadTexture2DFromFile(const char* file, bool bAlpha);
};

#endif