#include <fstream>
#include "PFX_Level.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

PFX_Level::PFX_Level() {
    //ctor
}
PFX_Level::~PFX_Level() {
    //dtor
}
uint8_t PFX_Level::LoadTexture( std::string path ) {
    uint8_t key = this->_textures_count;
    this->_textures[ key ] = PFX_Texture( path );
    this->_textures_count++;
    return key;
}
void PFX_Level::SetSizes( uint8_t x , uint8_t y ) {
    this->_size[ 0 ] = x;
    this->_size[ 1 ] = y;
}
void PFX_Level::LoadData( uint8_t level_num ) {
    std::ifstream f("levels/level-1.json");
    json data = json::parse(f);
    std::cout << data["x"] << "ponos" << "\n";
}
void PFX_Level::Update() {

}
