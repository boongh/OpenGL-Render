#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <gtc/type_ptr.hpp>

Shader* Shader::currentShader = nullptr;


Shader::Shader(const char* vertexPath, const char* fragmentPath) {

    // 2. compile shaders
    unsigned int vertex, fragment;

    // vertex Shader
    CompileShader(&vertex, vertexPath, GL_VERTEX_SHADER, "ERROR VERTEX");
    CompileShader(&fragment, fragmentPath, GL_FRAGMENT_SHADER, "ERROR FRAGMENT");

    // shader Program
    m_program = glCreateProgram();
    glAttachShader(m_program, vertex);
    glAttachShader(m_program, fragment);
    glLinkProgram(m_program);

    // print linking errors if any
    int success;
    char infoLog[512];
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::Shader() {

}
//Destructor for freeing memory
Shader::~Shader() {
    int success;
    char infoLog[512];
    glDeleteProgram(m_program);
    glGetProgramiv(m_program, GL_DELETE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::DELETION::FAILED\n" << infoLog << std::endl;
    };
}

void Shader::checkError(unsigned int shader, GLenum checkFor, const char* errorMessage) {
    int success;
    char infoLog[512];

    glGetShaderiv(shader, checkFor, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << errorMessage << "\n" << infoLog << std::endl;
    };
}

void Shader::CompileShader(unsigned int* target, const char* sourcePath, GLenum mode, const char* errorMes) {

    // 1. retrieve the vertex/fragment source code from filePath
    std::string code;
    std::ifstream ShaderFile;
    // ensure ifstream objects can throw exceptions:
    ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        ShaderFile.open(sourcePath);
        std::stringstream ShaderStream;
        // read file's buffer contents into streams
        ShaderStream << ShaderFile.rdbuf();
        // close file handlers
        ShaderFile.close();
        // convert stream into string
        code = ShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* ShaderCode = code.c_str();

    std::cout << ShaderCode << "\n";



    // 2. compile shaders
    unsigned int shader;
    int success;
    char infoLog[512];
    std::cout << mode;

    // vertex Shader
    shader = glCreateShader(mode);
    glShaderSource(shader, 1, &ShaderCode, NULL);
    glCompileShader(shader);
    // print compile errors if any
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << errorMes << infoLog << std::endl;
    };

    *target = shader;
}

void Shader::Use() {
    glUseProgram(m_program);
	currentShader = this;
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), value);
}
void Shader::SetInt(const std::string& name, int value1, int value2) const
{
    glUniform2i(glGetUniformLocation(m_program, name.c_str()), value1, value2);
}
void Shader::SetInt(const std::string& name, int value1, int value2, int value3) const
{
    glUniform3i(glGetUniformLocation(m_program, name.c_str()), value1, value2, value3);
}
void Shader::SetInt(const std::string& name, int value1, int value2, int value3, int value4) const
{
    glUniform4i(glGetUniformLocation(m_program, name.c_str()), value1, value2, value3, value4);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) {
		std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
    	throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
	}
    glUniform1f(loc, value);
}
void Shader::SetFloat(const std::string& name, float value1, float value2) const
{
    glUniform2f(glGetUniformLocation(m_program, name.c_str()), value1, value2);
}
void Shader::SetFloat(const std::string& name, float value1, float value2, float value3) const
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), value1, value2, value3);
}
void Shader::SetFloat(const std::string& name, float value1, float value2, float value3, float value4) const
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), value1, value2, value3, value4);
}

void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2 mat)  {
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2x3 mat) {
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat2x4 mat) {
    glUniformMatrix2fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3 mat)  {
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3x2 mat) {
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat3x4 mat) {
    glUniformMatrix3fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4 mat)  {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4x2 mat) {
    GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) {
		std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;

		throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
    }
    glUniformMatrix4fv(loc, count, transpose, glm::value_ptr(mat));
};
void Shader::SetMatrix(const std::string& name, int count, GLboolean transpose, glm::mat4x3 mat) {
    GLint loc = glGetUniformLocation(m_program, name.c_str());
    if (loc == -1) {
        std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
        throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
    }
    glUniformMatrix4fv(loc, count, transpose, glm::value_ptr(mat));
};

void Shader::SetVec(const std::string& name, int count, glm::vec1 vec) {
	GLint loc = glGetUniformLocation(m_program, name.c_str());
	if (loc == -1) {
		std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
		throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
	}
    glUniform1fv(loc, count, &vec[0]);
};
void Shader::SetVec(const std::string& name, int count, glm::vec2 vec) {
    GLint loc = glGetUniformLocation(m_program, name.c_str());
    if (loc == -1) {
        std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
        throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
    }
    glUniform2fv(loc, count, &vec[0]);
};
void Shader::SetVec(const std::string& name, int count, glm::vec3 vec) {
    GLint loc = glGetUniformLocation(m_program, name.c_str());

    if (loc == -1) {
        std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
        throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
    }
    glUniform3fv(loc, count, &vec[0]);
};
void Shader::SetVec(const std::string& name, int count, glm::vec4 vec) {
    GLint loc = glGetUniformLocation(m_program, name.c_str());
    if (loc == -1) {
        std::cout << "ERROR::SHADER::UNIFORM_NOT_FOUND\n" << name << std::endl;
        throw std::runtime_error("ERROR::SHADER::UNIFORM_NOT_FOUND\n" + name);
    }
    glUniform4fv(loc, count, &vec[0]);
};
