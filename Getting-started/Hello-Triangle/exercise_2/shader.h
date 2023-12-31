#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
  public:
    unsigned int ID;

    // constructor generates the shader on the fly
    Shader(const char*, const char*);

    // activate the shader
    void use()
    { 
      glUseProgram(ID); 
    }

    // utility uniform functions
    void setBool(const std::string &name, bool value) const
    {         
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }

    void setInt(const std::string &name, int value) const
    { 
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }

    void setFloat(const std::string &name, float value) const
    { 
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }

  private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(unsigned int, std::string);
};

#endif