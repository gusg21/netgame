//
// Created by angus.goucher on 4/18/2024.
//

#ifndef NETGAME_TEXTURE_H
#define NETGAME_TEXTURE_H

#include <raylib.h>

namespace net {
class Texture {
public:
    Texture(const char* path);

    void* GetTextureHandle() { return &m_Texture; };

private:
    Texture2D m_Texture;
};
}

#endif