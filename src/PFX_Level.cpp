#include <fstream>
#include "PFX_Level.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <core\PFX_Context.h>

using json = nlohmann::json;

PFX_Level::PFX_Level() {
    //ctor
}
PFX_Level::~PFX_Level() {
    //dtor
}
uint8_t PFX_Level::LoadTexture( std::string path ) {
    uint8_t key = this->_textures_count;
    this->_textures.push_back( PFX_Texture( path ) );
    this->_textures_count++;
    return key;
}
void PFX_Level::SetSizes( int x , int y , int z ) {
    this->_size_x = x;
    this->_size_y = y;
    this->_size_z = z;
    const int cell_size = x * z;
    //this->_cells.resize( cell_size );
    this->_CreateCellsData();
}
void PFX_Level::_CreateCell( std::array<float, 3> position ) {
    PFX_Level_Cell cell( position );
    this->_cells.push_back( std::move( cell ) );
    //return this->_cells.back();
}
void PFX_Level::_CreateCellsData() {
    for( uint8_t z = 0; z < this->_size_z; z++ ) {
        for( uint8_t x = 0; x < this->_size_x; x++ ) {
            this->_CreateCell( { static_cast<float>( x ) , 0.0f , static_cast<float>( z ) } );
            this->_cells.back().AddPlane();
           // PFX_Level_Cell* cell = &this->_cells.back();
        }
    }
}
void PFX_Level::LoadData( uint8_t level_num ) {
    std::ifstream f("levels/level-1.json");
    json data = json::parse(f);
    std::cout << data["x"] << "ponos" << "\n";
}
void PFX_Level::Update() {
    PFX_Context& context = PFX_Context::GetInstance();
    PFX_Render& render = context.Render();
    for ( auto &element : this->_cells ) {
        element.Update();
        render.Geometry( element.GetPlane() );
    }
}
