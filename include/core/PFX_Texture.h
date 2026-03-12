#pragma once

#include <string>
#include <cstdint>

class PFX_Texture
{
    private:
        std::string _path;
        int _width = 0;
        int _height = 0;
        int _channels = 0;
        unsigned char* _pixels;
    public:
        PFX_Texture();
        PFX_Texture( std::string path );
        ~PFX_Texture();
        void Load( std::string path );
        unsigned char* Pixels();
        int Width();
        int Height();
        std::string Path();
        int Channels();
};
