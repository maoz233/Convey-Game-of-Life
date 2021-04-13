#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
 public:
  // state
  unsigned int id;

  // constructor
  Shader();
  // set current shader
  Shader& Use();
  // compile the shader
  void Compile(const char* vertexShaderSrc, const char* fragmentShaderSrc, const char* geometryShaderSrc = nullptr);
  // utility funtions
  void SetFloat(const char* name, float val, bool bUseShader = false);
  void SetInteger(const char* name, int val, bool bUseShader = false);
  void SetVector2f(const char* name, float x, float y, bool bUseShader = false);
  void SetVector2f(const char* name, glm::vec2& vec, bool bUseShader = false);
  void SetVector3f(const char* name, float x, float y, float z, bool bUseShader = false);
  void SetVector3f(const char* name, glm::vec3& vec, bool bUseShader = false);
  void SetVector4f(const char* name, float x, float y, float z, float w, bool bUseShader = false);
  void SetVector4f(const char* name, glm::vec4& vec, bool bUseShader = false);
  void SetMatrix4(const char* name, glm::mat4& mat, bool bUseShader = false);

 private:
  void CheckCompileErrors(unsigned int obj, std::string type);
};

#endif