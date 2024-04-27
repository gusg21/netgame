#include "texture.h"

net::Texture::Texture(const char* path)
{
    m_Texture = ::LoadTexture(path);
}