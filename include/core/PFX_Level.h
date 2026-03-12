#pragma once
#include <cstdint>
#include <core/PFX_texture.h>

class PFX_Level
{
    private:
        //Размер уровня 0 - x , 1 - y
        uint8_t _size[ 2 ];
        PFX_Texture _textures[ 255 ];
        uint8_t _textures_count = 0;
    public:
        PFX_Level();
        ~PFX_Level();
        void LoadData( uint8_t level_num );
        void SetSizes( uint8_t x , uint8_t y );
        uint8_t LoadTexture( std::string path );
        void Update();
};
