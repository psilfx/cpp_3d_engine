#include "PFX_Config.h"
#include <cmath>

inline const float PI = 3.14159265359f;
PFX_Config::PFX_Config() {
}
void PFX_Config::Init( int screen_width , int screen_height ) {
    this->_width = screen_width;
    this->_height = screen_height;
    this->_width_half = screen_width * 0.5;
    this->_height_half = screen_height * 0.5;
    this->_aspect_ratio = (float)screen_height / (float)screen_width;
    this->_fov = PI * 0.5;
    this->_fov_half = this->_fov * 0.5;
    this->_tan_fov_half = std::tan( this->_fov_half );
    this->_tan_fov_half_v = this->_tan_fov_half * this->_aspect_ratio;
    this->_fov_vertical_half = std::atan( this->_tan_fov_half_v );
    this->_fov_vertical = this->_fov_vertical_half * 2;
    this->_screen_scale = (float)this->_width_half / this->_tan_fov_half;
    this->_distance_far = 10;
    this->_distance_near = 0.01;
    this->_texture_size = 64;
    this->Copy();
}
void PFX_Config::Copy() {
    this->width = this->_width;
    this->height = this->_height;
    this->width_half = this->_width_half;
    this->height_half = this->_height_half;
    this->screen_scale = this->_screen_scale;
    this->aspect_ratio = this->_aspect_ratio;
    this->fov = this->_fov;
    this->fov_half = this->_fov_half;
    this->fov_vertical = this->_fov_vertical;
    this->fov_vertical_half = this->_fov_vertical_half;
    this->tan_fov_half = this->_tan_fov_half;
    this->tan_fov_half_v = this->_tan_fov_half_v;
    this->distance_near = this->_distance_near;
    this->distance_far = this->_distance_far;
    this->texture_size = this->_texture_size;

}
void PFX_Config::CopyToLUT() {
    InitLUT();
    //Загружаем LUT таблицы
    InitRenderLut();
}
PFX_Config::~PFX_Config()
{
    //dtor
}
