#include "Texture.h"

Texture::Texture(std::string fileName)
{
    SDL_Surface* image = nullptr;

    image = IMG_Load(fileName.c_str());

    if (image == nullptr)
    {
        std::cout << "Error loading image: " << fileName << std::endl;
    }
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glActiveTexture(GL_TEXTURE0);

    int mode = GL_RGB;

    if (image->format->BytesPerPixel == 4)
        mode = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, mode, image->w, image->h, 0, mode, GL_UNSIGNED_BYTE, image->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SDL_FreeSurface(image);
}

void Texture::useTexture()
{
    glBindTexture(GL_TEXTURE_2D, texture);
}
