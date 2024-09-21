#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>

int shaderInit() {

    const char* vertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "uniform float u_time;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0f, 1.0);\n"
        "}\0";

    const char* fragShaderSource =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "uniform vec2 u_resolution;\n"
        "uniform float u_time;\n"
        "void main(){\n"
        "   FragColor = vec4((sin(u_time - 7) + 1) /2 , (sin(u_time - 5) + 1) /2 , (sin(u_time - 3) + 1) /2 , 1.0f);\n"
        "}\0";


    //set "vertexShader" to be a type of vertex shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //The source code of shader to be vertexShaderSource
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //Compile the sourcecode of the shader into runnable code?
    glCompileShader(vertexShader);


    //set "fragmentShader" to be a type of fragment shader 
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //The source code of shader to be fragShaderSource
    glShaderSource(fragmentShader, 1, &fragShaderSource, NULL);
    //Compile the sourcecode of the shader into runnable code?
    glCompileShader(fragmentShader);



    //Check if compilation of the shader is successful at run time
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    //create shader program (how shaders interact with each other)
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //after linking the program, the shader is not needed anymore
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKER::FAILED\n" << infoLog << std::endl;
    }

    return shaderProgram;
}