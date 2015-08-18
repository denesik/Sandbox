#pragma once
#ifndef Shader_h__
#define Shader_h__


#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader;
typedef std::shared_ptr<Shader> PShader;

/// ������.
class Shader
{
public:
  Shader(const std::string &shaderName);
  ~Shader();

  /// ���������� ������.
  void Use();

  template<class T>
  void SetUniform(const T &val, const char *name = "")
  {
    SetUniform_(val, name);
  };

#define UNIFORM_QUOTE(name) #name
#define UNIFORM_MAKE_STR(macro) UNIFORM_QUOTE(macro)
#define SetUniform(val) SetUniform(val, UNIFORM_MAKE_STR(val))

private:

  unsigned int mProgram;

private:

  /// ��������� ������.
  unsigned int CreateShader(const std::string &data, int type);

  /// ������� ������
  void DeleteShader(unsigned int shader);

  /// ��������� ����.
  std::string ReadTxtFile(const std::string &fileName);

  int GetUniformLocation(const char *name);

private:

  void SetUniform_(const glm::mat4 &val, const char *name);

  void SetUniform_(int val, const char *name);

  void SetUniform_(const glm::vec4 &val, const char *name);

  void SetUniform_(const glm::vec3 &val, const char *name);

private:

  std::unordered_map<std::string, int> mUniforms;

};


#endif // Shader_h__
