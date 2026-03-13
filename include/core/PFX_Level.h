#pragma once
#include <cstdint>
#include <vector>
#include <core/PFX_Texture.h>
#include <core/PFX_Geometry.h>
#include <core/PFX_Level_Cell.h>

class PFX_Level
{
    private:
        //Размер уровня 0 - x , 1 - y
        uint8_t _size_x;
        uint8_t _size_y;
        uint8_t _size_z;
        std::vector<PFX_Texture> _textures;
        std::vector<PFX_Geometry> _geometry;
        std::vector<PFX_Level_Cell> _cells;
        uint8_t _textures_count = 0;
        void _CreateCell( std::array<float, 3> position );
        void _CreateCellsData();
    public:
        PFX_Level();
        ~PFX_Level();
        void LoadData( uint8_t level_num );
        void SetSizes( int x , int y , int z );
        uint8_t LoadTexture( std::string path );
        void Update();
};
