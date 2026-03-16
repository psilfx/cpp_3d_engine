#pragma once
#include <cstdint>
#include <vector>
#include <core\PFX_Texture.h>
#include <core\PFX_Geometry.h>
#include <core\PFX_Level_Cell.h>

class PFX_Level
{
    private:
        //Размер уровня 0 - x , 1 - y
        uint8_t _size_x = 0;
        uint8_t _size_y = 0;
        uint8_t _size_z = 0;
        std::array<float, 3> _sizes = {0};
        std::vector<PFX_Texture> _textures;
        std::vector<std::unique_ptr<PFX_Geometry>> _geometry;
        std::vector<PFX_Level_Cell> _cells;
        uint8_t _textures_count = 0;
        void _CreateCell( std::array<float, 3> position );
        void _CreateCellsData();
    public:
        PFX_Level();
        ~PFX_Level();
        void LoadData( uint8_t level_num );
        int GetCellIndex( const std::array<float, 3>& position );
        PFX_Level_Cell& GetCellByCoords( std::array<float, 3> position );
        PFX_Geometry& CreateGeometry();
        void BindGeometryToCells( PFX_Geometry& geometry );
        void SetSizes( int x , int y , int z );
        std::array<float, 3> GetSizes();
        uint8_t LoadTexture( std::string path );
        void Update();
};
