#include <fstream>
#include "PFX_Level.h"
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <core\PFX_Context.h>
#include <core\PFX_Raycast_Light.h>

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
    this->_sizes = { static_cast<float>( x ) , static_cast<float>( y ) , static_cast<float>( z ) };
    this->_CreateCellsData();
}
std::array<float, 3> PFX_Level::GetSizes() {
    return this->_sizes;
}
void PFX_Level::_CreateCell( std::array<float, 3> position ) {
    this->_cells.emplace_back( position );
    //return this->_cells.back();
}
void PFX_Level::_CreateCellsData() {
    for( uint8_t y = 0; y < this->_size_y; y++ ) {
        for( uint8_t z = 0; z < this->_size_z; z++ ) {
            for( uint8_t x = 0; x < this->_size_x; x++ ) {
                this->_CreateCell( { static_cast<float>( x ) , static_cast<float>( y ) , static_cast<float>( z ) } );
                this->_cells.back().AddPlane();
            }
        }
    }
}
void PFX_Level::LoadData( uint8_t level_num ) {
    std::ifstream f("levels/level-1.json");
    json data = json::parse(f);

    int size_x = data[ "size_x" ].get<int>();
    int size_y = data[ "size_y" ].get<int>();
    int size_z = data[ "size_z" ].get<int>();

    this->SetSizes( size_x , size_y , size_z );

    PFX_Context& context = PFX_Context::GetInstance();
    PFX_Player& player = context.Player();
    player.SetPositionMax( this->_sizes );

    for ( auto& [ key , geo ] : data[ "geometry" ].items() ) {
        std::string type = geo[ "type" ].get<std::string>();
        std::string texture = geo[ "texture" ].get<std::string>();
        std::array<float, 3 > geometry_position = { geo[ "position" ][ "x" ].get<float>() , geo[ "position" ][ "y" ].get<float>() , geo[ "position" ][ "z" ].get<float>() };
        std::array<float, 3 > geometry_heights = { geo[ "heights" ][ "x" ].get<float>() , geo[ "heights" ][ "y" ].get<float>() , geo[ "heights" ][ "z" ].get<float>() };
        if( type == "cube" ) {
            std::cout << geometry_position[ 0 ] << " " << geometry_position[ 1 ] << " " << geometry_position[ 2 ] << "\n";
            std::cout << geometry_heights[ 0 ] << " " << geometry_heights[ 1 ] << " " << geometry_heights[ 2 ] << "\n";
            std::cout << texture << "\n";
            PFX_Geometry& geometry = this->CreateGeometry();
            Geometry_Create_Cube( geometry , geometry_position ,
                                 geometry_heights[ 0 ] , geometry_heights[ 1 ] , geometry_heights[ 2 ] ,
                                 texture );
            this->BindGeometryToCells( geometry );
        }
    }

}
PFX_Geometry& PFX_Level::CreateGeometry() {
   // PFX_Geometry geometry();
    this->_geometry.push_back( std::move( std::make_unique<PFX_Geometry>() ) );
//    this->_geometry.emplace_back();
    return *this->_geometry.back().get();
}
void PFX_Level::BindGeometryToCells( PFX_Geometry& geometry ) {
    Collision_Box box = geometry.collision_box;
    float* position = box.position.data();
    float* heights = box.heights.data();
    int x_start = static_cast<int>( position[ 0 ] );
    int y_start = static_cast<int>( position[ 1 ] );
    int z_start = static_cast<int>( position[ 2 ] );
    int x_end = x_start + static_cast<int>( heights[ 0 ] );
    int y_end = y_start + static_cast<int>( heights[ 1 ] );
    int z_end = z_start + static_cast<int>( heights[ 2 ] );
    for( int y = y_start; y <= y_end; y++ ) {
        for( int z = z_start; z <= z_end; z++ ) {
            for( int x = x_start; x <= x_end; x++ ) {
                PFX_Level_Cell& cell = this->GetCellByCoords( { static_cast<float>( x ) , static_cast<float>( y ) , static_cast<float>( z ) } );
                cell.AddGeometry( geometry );
            }
        }
    }
}
int PFX_Level::GetCellIndex( const std::array<float, 3>& position ) {
    int x = static_cast<int>( position[ 0 ] );
    int y = static_cast<int>( position[ 1 ] );
    int z = static_cast<int>( position[ 2 ] );
    return y * ( static_cast<int>( this->_size_x ) * static_cast<int>( this->_size_z ) ) + z * static_cast<int>( this->_size_x ) + x;
}
PFX_Level_Cell& PFX_Level::GetCellByCoords( std::array<float, 3> position ) {
    int index = this->GetCellIndex( position );
    return this->_cells.at( index );
}
void PFX_Level::Update() {
    PFX_Raycast_Light::Ray( *this , { 1.0f , -1.0f , 1.0f } , 0.5f );
    for ( auto &geo : this->_geometry ) {
        //std::cout << geo.updated << " " << geo.collision_box.position[ 0 ] << " " << geo.collision_box.position[ 1 ] << " " << geo.collision_box.position[ 2 ] << "\n";
        geo->updated = false;
    }
    for ( auto &element : this->_cells ) {
        element.Update();
    }
}
