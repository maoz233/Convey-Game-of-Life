#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// Instantiate static variables
std::map<std::string, Shader> ResourceManager::Shaders;
std::map<std::string, Texture2D> ResourceManager::Textures;

Shader ResourceManager::LoadShader(const char* vertexShaderFile, const char* fragmentShaderFile, const char* geometryShaderFile,
                                   std::string name) {
  Shaders[name] = LoadShaderFromFile(vertexShaderFile, fragmentShaderFile, geometryShaderFile);
  return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name) { return Shaders[name]; }

Texture2D ResourceManager::LoadTexture2D(const char* file, bool bAlpha, std::string name) {
  Textures[name] = LoadTexture2DFromFile(file, bAlpha);
  return Textures[name];
}

Texture2D& ResourceManager::GetTexture2D(std::string name) { return Textures[name]; }

void ResourceManager::Clear() {
  // delete all shaders
  for (auto item : Shaders) {
    glDeleteProgram(item.second.id);
  }
  // delete all textures
  for (auto item : Textures) {
    glDeleteTextures(1, &item.second.id);
  }
}

Shader ResourceManager::LoadShaderFromFile(const char* vertexFile, const char* fragmentFile, const char* geometryFile) {
  // shader source code
  std::string vertexShaderSrc, fragmentShaderSrc, geometryShaderSrc;
  try {
    // open files
    std::ifstream vertexShaderFile(vertexFile);
    std::ifstream fragmentShaderFile(fragmentFile);
    // read file buffer contents to stream
    std::stringstream vertexShaderStream, fragmentShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    // close files
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // convert stream to string
    vertexShaderSrc = vertexShaderStream.str();
    fragmentShaderSrc = fragmentShaderStream.str();
    // geometry shader
    if (nullptr != geometryFile) {
      std::ifstream geometryShaderFile(geometryFile);
      std::stringstream geometryShaderStream;
      geometryShaderStream << geometryShaderFile.rdbuf();
      geometryShaderFile.close();
      geometryShaderSrc = geometryShaderStream.str();
    }
  } catch (std::exception e) {
    std::cerr << "ERROR::SHADER: Failed to open shader files " << std::endl;
  }
  const char* vertexShaderCode = vertexShaderSrc.c_str();
  const char* fragmentShaderCode = fragmentShaderSrc.c_str();
  const char* geometryShaderCode = geometryFile != nullptr ? geometryShaderSrc.c_str() : nullptr;
  // create sahder object
  Shader shader;
  shader.Compile(vertexShaderCode, fragmentShaderCode, geometryShaderCode);
  return shader;
}

Texture2D ResourceManager::LoadTexture2DFromFile(const char* file, bool bAlpha) {
  // create texture object
  Texture2D texture;
  if (bAlpha) {
    texture.internal_format = GL_RGBA;
    texture.image_format = GL_RGBA;
  }
  // load image
  int width, height, nrChannels;
  unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
  // generate texture
  texture.Generate(width, height, data);
  // free image data
  stbi_image_free(data);
  return texture;
}
