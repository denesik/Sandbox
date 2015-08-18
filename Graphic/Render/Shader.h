#pragma once
#ifndef Shader_h__
#define Shader_h__


#include <memory>
#include <string>
#include <glm/glm.hpp>

class Shader;
typedef std::shared_ptr<Shader> PShader;

#define QUOTE(name) #name
#define MAKE_STR(macro) QUOTE(macro)

#define SetUniform(val) SetUniform_(val, MAKE_STR(val))

/// ������.
class Shader
{
public:
  Shader(const std::string &shaderName);
  ~Shader();

  /// ���������� ������.
  void Use();

  void SetUniform_(const glm::mat4 &val, const char *name);

  void SetUniform_(int val, const char *name);

  void SetUniform_(const glm::vec4 &val, const char *name);

  void SetUniform_(const glm::vec3 &val, const char *name);

private:

  unsigned int mProgram;

private:

  /// ��������� ������.
  unsigned int CreateShader(const std::string &data, int type);

  /// ������� ������
  void DeleteShader(unsigned int shader);

  /// ��������� ����.
  std::string ReadTxtFile(const std::string &fileName);

};


#endif // Shader_h__
