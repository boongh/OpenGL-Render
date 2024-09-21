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
    Texture(const char* texturepath, GLenum type, int unit);
    ~Texture();

    //bind the texture to OpenGL
    void TextureBind();
    void TextureActive();
};

#endif