#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

class Texture
{
    public:
        GLuint texture;

        Texture(std::string fileName);

        void useTexture();
};

#endif
