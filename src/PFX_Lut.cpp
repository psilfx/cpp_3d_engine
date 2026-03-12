#include "PFX_Lut.h"
#include "PFX_Context.h"
#include <cmath>

const float radian = 1 / 1000;
const float LUT_PI = 3.14159265359f;
const float LUT_PI_DOUBLE = LUT_PI * 2.0f;
float LUT_TIME_DELTA = 1.0f;
float LUT_SIN[ 10000 ] = {0};
float LUT_COS[ 10000 ] = {0};
float LUT_DIST_INV[ 10000 ] = {0};
float LUT_FOV = 0;
float LUT_FOV_H = 0;
float LUT_V_FOV = 0;
float LUT_V_FOV_H = 0;
//Для проекции
const float LUT_PROJECTION_DISTANCE_NEAR = 0.01f;
const float LUT_PROJECTION_DISTANCE_FAR = 10.0f;
float LUT_PROJECTION_DIST_INV[ 100000 ] = {0};
//Для рендера
uint_fast32_t LUT_RENDER_BUFF_Y[ 10000 ] = {0};
uint_fast16_t LUT_RENDER_TEXTURE_Y[ 10000 ] = {0};
uint_fast16_t LUT_RENDER_TEXTURE_X[ 10000 ] = {0};
uint_fast32_t LUT_RENDER_BUFF_X[ 10000 ] = {0};
uint_fast32_t LUT_RENDER_BUFF_MAX_INDEX = 0;
uint_fast32_t LUT_RENDER_TEXTURE_MAX_INDEX = 0;
uint_fast16_t LUT_RENDER_SCREEN_WIDTH = 0;
uint_fast16_t LUT_RENDER_SCREEN_WIDTH_HALF = 0;
uint_fast16_t LUT_RENDER_SCREEN_HEIGHT = 0;
uint_fast16_t LUT_RENDER_SCREEN_HEIGHT_HALF = 0;
uint_fast16_t LUT_RENDER_SCREEN_SCALE = 0;
float LUT_RENDER_SCREEN_WIDTH_F = 0.0f;
float LUT_RENDER_SCREEN_WIDTH_HALF_F = 0.0f;
float LUT_RENDER_SCREEN_HEIGHT_F = 0.0f;
float LUT_RENDER_SCREEN_HEIGHT_HALF_F = 0.0f;
float LUT_RENDER_SCREEN_SCALE_F = 0.0f;
//Для текстуры
uint_fast8_t LUT_RENDER_TEXTURE_SIZE = 0;
float LUT_RENDER_TEXTURE_SIZE_F = 0.0f;
float LUT_RENDER_TEXTURE_Z_INV[ 10000 ] = {0};
uint_fast8_t LUT_RENDER_TEXTURE_DIVISION[ 10000 ] = {0};
//Геометрия
const int LUT_POINT_SIZE = 6;
const int LUT_POINT_SIZE_2 = LUT_POINT_SIZE * 2;
const int LUT_POINT_SIZE_3 = LUT_POINT_SIZE * 3;
const int LUT_POINT_SIZE_4 = LUT_POINT_SIZE * 4;
const int LUT_POINT_SIZE_5 = LUT_POINT_SIZE * 5;

void InitLUT() {
    for ( int i = 0; i < 10000; i++ ) {
        LUT_SIN[ i ] = std::sin( static_cast<float>( i ) * radian );
        LUT_COS[ i ] = std::cos( static_cast<float>( i ) * radian );
        LUT_DIST_INV[ i ] = 1.0f / std::max( LUT_PROJECTION_DISTANCE_NEAR , static_cast<float>( i ) );
    }
    for ( int i = 0; i < 100000; i++ ) {
        LUT_PROJECTION_DIST_INV[ i ] = 1.0f / std::max( LUT_PROJECTION_DISTANCE_NEAR , static_cast<float>( i ) / 1000.0f );
    }
}

void InitRenderLut( ) {
    PFX_Context& context = PFX_Context::GetInstance();
    PFX_Config& config = context.Config();
    LUT_RENDER_BUFF_MAX_INDEX = config.width * config.height * 4;
    //Углы обзора
    LUT_FOV = config.fov;
    LUT_FOV_H = config.fov_half;
    LUT_V_FOV = config.fov_vertical;
    LUT_V_FOV_H = config.fov_vertical_half;
    //Размеры экрана
    LUT_RENDER_SCREEN_WIDTH = config.width;
    LUT_RENDER_SCREEN_WIDTH_HALF = config.width_half;
    LUT_RENDER_SCREEN_HEIGHT = config.height;
    LUT_RENDER_SCREEN_HEIGHT_HALF = config.height_half;
    LUT_RENDER_SCREEN_SCALE = config.screen_scale;
    LUT_RENDER_SCREEN_WIDTH_F = (float)LUT_RENDER_SCREEN_WIDTH;
    LUT_RENDER_SCREEN_WIDTH_HALF_F = (float)LUT_RENDER_SCREEN_WIDTH_HALF;
    LUT_RENDER_SCREEN_HEIGHT_F = (float)LUT_RENDER_SCREEN_HEIGHT;
    LUT_RENDER_SCREEN_HEIGHT_HALF_F = (float)LUT_RENDER_SCREEN_HEIGHT_HALF;
    LUT_RENDER_SCREEN_SCALE_F = (float)LUT_RENDER_SCREEN_SCALE;
    //Текстура
    LUT_RENDER_TEXTURE_SIZE = config.texture_size;
    LUT_RENDER_TEXTURE_SIZE_F = (float)LUT_RENDER_TEXTURE_SIZE;
    LUT_RENDER_TEXTURE_MAX_INDEX = LUT_RENDER_TEXTURE_SIZE * LUT_RENDER_TEXTURE_SIZE * 4;
    for ( int i = 0; i < 10000; i++ ) {
        const int max_i_y = std::min( i , LUT_RENDER_SCREEN_HEIGHT - 1 );
        const int max_i_x = std::min( i , LUT_RENDER_SCREEN_WIDTH - 1 );
        LUT_RENDER_BUFF_Y[ i ] = max_i_y * ( config.width * 4 );
        LUT_RENDER_BUFF_X[ i ] = max_i_x * 4;
    }
    for ( int i = 0; i < 10000; i++ ) {
        LUT_RENDER_TEXTURE_Z_INV[ i ] = LUT_RENDER_TEXTURE_SIZE_F / std::max( LUT_PROJECTION_DISTANCE_NEAR , static_cast<float>( i ) / 1000.0f ); //Инвертированное расстояние
    }
    for( int i = 0; i < 10000; i++ ) {
        const int max_i_y = std::min( i , LUT_RENDER_TEXTURE_SIZE - 1 );
        const int max_i_x = std::min( i , LUT_RENDER_TEXTURE_SIZE - 1 );
        LUT_RENDER_TEXTURE_Y[ i ] = max_i_y * ( LUT_RENDER_TEXTURE_SIZE * 4 );
        LUT_RENDER_TEXTURE_X[ i ] = max_i_x * 4;
        LUT_RENDER_TEXTURE_DIVISION[ i ] = std::floor( i % LUT_RENDER_TEXTURE_SIZE ); //Остаток от деления
    }
}


