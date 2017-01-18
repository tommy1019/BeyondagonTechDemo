#include "Texture.h"

Texture::Texture(std::string fileName)
{
    SDL_Surface* image;

    image = IMG_Load(fileName.c_str());

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SDL_FreeSurface(image);
}

void Texture::useTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}
