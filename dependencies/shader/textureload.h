#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

class Texture {
private:
    unsigned int textureID;
    int unit;
    GLenum type;

public:

    //load image texture into class
    //initialize with filter and wrapper
    Texture(const char* texturepath, GLenum type, GLint minfilter, GLint magfilter, GLint texturewrapS, GLint texturewrapT, int unit);
    ~Texture();

    //bind the texture to OpenGL
    //incase for re-setting the filter
    void TextureBind();

    void parameterize(GLint minfilter, GLint magfilter, GLint texturewrapS, GLint texturewrapT);

    //activate the texture
    void TextureActive();
};

#endif