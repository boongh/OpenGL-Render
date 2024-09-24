#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm.hpp>

class Shader{

private:
    // the program ID
    unsigned int m_program;


public:

    enum MatSizeShader
    {
        M2,
        M2X2,
        M2X3,
        M2X4,
        M3,
        M3X2,
        M3X3,
        M3X4,
        M4,
        M4X2,
        M4X3,
        M4X4,
    };

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);

    //Destructor for freeing memory
    ~Shader();

    void checkError(unsigned int shader, GLenum checkFor, const char* errorMessage);
    void CompileShader(unsigned int* target, const char* sourcePath, GLenum mode, const char* errorMes);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    // Overload for a single int (glUniform1i)
    void SetInt(const std::string& name, int value) const;
    // Overload for a single int (glUniform2i)
    void SetInt(const std::string& name, int value1, int value2) const;
    // Overload for a single int (glUniform3i)
    void SetInt(const std::string& name, int value1, int value2, int value3) const;
    // Overload for a single int (glUniform4i)
    void SetInt(const std::string& name, int value1, int value2, int value3, int value4) const;
    // Overload for a single float (glUniform1f)
    void SetFloat(const std::string& name, float value) const;
    // Overload for a single float (glUniform2f)
    void SetFloat(const std::string& name, float value1, float value2) const;
    // Overload for a single float (glUniform3f)
    void SetFloat(const std::string& name, float value1, float value2, float value3) const;
    // Overload for a single float (glUniform4f)
    void SetFloat(const std::string& name, float value1, float value2, float value3, float value4) const;

    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2x2 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2x3 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2x4 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3x2 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3x3 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3x4 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4x2 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4x3 mat);
    void SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4x4 mat);

};

#endif