#include <textureload.h>
#include <stb_image.h>
#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>
#include <iostream>


Texture::~Texture() {
    glDeleteTextures(1, &textureID);
}

Texture::Texture(const char* texturePath, GLenum typeIn, int unit) {
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);

    Texture::unit = unit;
    Texture::type = typeIn;
    unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);


    if (data) {
        //generate texture
        glGenTextures(1, &textureID);
        TextureActive();// activate the texture unit first before binding texture
        TextureBind();

        std::cout << nrChannels << "\n" << std::endl;
        //generate minimap
        if (nrChannels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {

        std::cout << "FAILED TO LOAD TEXTURE " << unit;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    //free image to free space
    stbi_image_free(data);

};

void Texture::TextureBind() {
    TextureActive();
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::TextureActive() {
    glActiveTexture(GL_TEXTURE0 + unit);
}