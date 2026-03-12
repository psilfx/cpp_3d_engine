#include "PFX_Texture.h"
#include <stb-image/stb_image.h>

PFX_Texture::PFX_Texture( std::string path )
{
    this->Load( path );
}
PFX_Texture::PFX_Texture() {

}
PFX_Texture::~PFX_Texture()
{
    delete[] this->_pixels;
}
void PFX_Texture::Load( std::string path ) {
    this->_path = path;
    this->_pixels = stbi_load( this->_path.c_str() , &this->_width, &this->_height, &this->_channels, 4 );
}
unsigned char* PFX_Texture::Pixels() {
    return this->_pixels;
}
int PFX_Texture::Width() {
    return this->_width;
}
int PFX_Texture::Height() {
    return this->_height;
}
std::string PFX_Texture::Path() {
    return this->_path;
}
int PFX_Texture::Channels() {
    return this->_channels;
}
