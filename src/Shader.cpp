#include "Shader.h"

#include <iostream>

Shader::Shader() {}

Shader& Shader::Use() {
  glUseProgram(this->id);
  return *this;
}

void Shader::Compile(const char* vertexShaderSrc, const char* fragmentShaderSrc, const char* geometryShaderSrc) {
  unsigned int vertexShader, fragmentShader, geometryShader;
  // vertex shader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
  glCompileShader(vertexShader);
  CheckCompileErrors(vertexShader, "VERTEX");
  // fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
  glCompileShader(fragmentShader);
  CheckCompileErrors(fragmentShader, "FRAGMENT");
  // geometry shader
  if (geometryShaderSrc != nullptr) {
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometryShaderSrc, NULL);
    glCompileShader(geometryShader);
    CheckCompileErrors(geometryShader, "GEOMETRY");
  }
  // shader program
  this->id = glCreateProgram();
  glAttachShader(this->id, vertexShader);
  glAttachShader(this->id, fragmentShader);
  if (geometryShaderSrc != nullptr) {
    glAttachShader(this->id, geometryShader);
  }
  glLinkProgram(this->id);
  CheckCompileErrors(this->id, "PROGRAM");
  // delete shaders as no longer necessary
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  if (geometryShaderSrc != nullptr) {
    glDeleteShader(geometryShader);
  }
}

void Shader::SetFloat(const char* name, float val, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform1f(glGetUniformLocation(this->id, name), val);
}

void Shader::SetInteger(const char* name, int val, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform1i(glGetUniformLocation(this->id, name), val);
}

void Shader::SetVector2f(const char* name, float x, float y, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform2f(glGetUniformLocation(this->id, name), x, y);
}

void Shader::SetVector2f(const char* name, glm::vec2& vec, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform2f(glGetUniformLocation(this->id, name), vec.x, vec.y);
}

void Shader::SetVector3f(const char* name, float x, float y, float z, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform3f(glGetUniformLocation(this->id, name), x, y, z);
}

void Shader::SetVector3f(const char* name, glm::vec3& vec, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform3f(glGetUniformLocation(this->id, name), vec.x, vec.y, vec.z);
}

void Shader::SetVector4f(const char* name, float x, float y, float z, float w, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform4f(glGetUniformLocation(this->id, name), x, y, z, w);
}

void Shader::SetVector4f(const char* name, glm::vec4& vec, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniform4f(glGetUniformLocation(this->id, name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetMatrix4(const char* name, glm::mat4& mat, bool bUseShader) {
  if (bUseShader) {
    this->Use();
  }
  glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(mat));
}

void Shader::CheckCompileErrors(unsigned int obj, std::string type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(obj, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER: Compile-time error:\nType: " << type << " Info:" << infoLog << std::endl;
    }
  } else {
    glGetProgramiv(obj, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(obj, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER: Link-time error:\n Type: " << type << " Info:" << infoLog << std::endl;
    }
  }
}
