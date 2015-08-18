#include "Shader.h"


#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <assert.h>
#include <fstream>

Shader::Shader(const std::string &shaderName)
{
  // Читаем и создаем шейдеры.
  // Если файл не существует, шейдер не создается.
  std::vector<int> shaders;

  try
  {
    shaders.push_back(CreateShader(ReadTxtFile(shaderName + ".vs"), GL_VERTEX_SHADER));
    shaders.push_back(CreateShader(ReadTxtFile(shaderName + ".fs"), GL_FRAGMENT_SHADER));
  }
  catch (char *)
  {
    // Удалим все созданные шейдеры.
    for (auto it = shaders.begin(); it != shaders.end(); ++it)
    {
      DeleteShader(*it);
    }
    throw;
  }

  // Очищаем стек ошибок ogl.
  while (!glGetError()) {};

  // Пытаемся собрать программу из всех прочитанных шейдеров.
  mProgram = glCreateProgram();
  for (auto it = shaders.begin(); it != shaders.end(); ++it)
  {
    if (*it)
    {
      glAttachShader(mProgram, *it);
    }
  }
  glLinkProgram(mProgram);

  // Удаляем шейдеры.
  for (auto it = shaders.begin(); it != shaders.end(); ++it)
  {
    DeleteShader(*it);
  }

  // Проверяем статус линковки
  GLint link = GL_FALSE;
  glGetProgramiv(mProgram, GL_LINK_STATUS, &link);
  if (link != GL_TRUE || glGetError())
  {
    GLint linkerLogSize = 0;
    glGetProgramiv(mProgram, GL_INFO_LOG_LENGTH, &linkerLogSize);
    if (linkerLogSize)
    {
      std::string linkerLog(linkerLogSize, '\0');
      glGetProgramInfoLog(mProgram, linkerLogSize, NULL, &linkerLog[0]);
    }

    glDeleteProgram(mProgram);
    throw "Shader not created.";
  }
}


Shader::~Shader()
{
  glDeleteProgram(mProgram);
}

void Shader::Use()
{
  glUseProgram(mProgram);
}

void Shader::SetUniform_(const glm::mat4 &val, const char *name)
{
  glUniformMatrix4fv(glGetUniformLocation(mProgram, name), 1, GL_FALSE, &val[0][0]);
}

void Shader::SetUniform_(int val, const char *name)
{
  glUniform1i(glGetUniformLocation(mProgram, name), val);
}

void Shader::SetUniform_(const glm::vec4 &val, const char *name)
{
  glUniform3fv(glGetUniformLocation(mProgram, name), 1, &val[0]);
}

void Shader::SetUniform_(const glm::vec3 &val, const char *name)
{
  glUniform3fv(glGetUniformLocation(mProgram, name), 1, &val[0]);
}

unsigned int Shader::CreateShader(const std::string &data, int type)
{
  if (data.empty())
  {
    return 0;
  }

  // Очищаем стек ошибок ogl.
  while (!glGetError()) {};

  GLuint shader = glCreateShader(type);

  if (glGetError())
  {
    throw "Shader not created.";
  }

  char const *sourcePointer = data.c_str();
  glShaderSource(shader, 1, &sourcePointer, NULL);
  glCompileShader(shader);

  GLint compiled = GL_FALSE;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

  if (compiled != GL_TRUE || glGetError())
  {
    int infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    if (infoLogLength)
    {
      std::vector<char> VertexShaderErrorMessage(infoLogLength);
      glGetShaderInfoLog(shader, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
    }

    glDeleteShader(shader);
    throw "Shader not created.";
  }

  return shader;
}

void Shader::DeleteShader(unsigned int shader)
{
  glDeleteShader(shader);
}

std::string Shader::ReadTxtFile(const std::string &fileName)
{
  std::string code;
  std::ifstream file(fileName, std::ios::in);
  if (file.is_open())
  {
    std::string line = "";
    while (getline(file, line))
      code += "\n" + line;
    file.close();
  }

  return code;
}
