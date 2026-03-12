#include "PFX_Projection.h"
#include <core/PFX_Vector.h>
#include <core/PFX_Lut.h>
#include <iostream>

PFX_Projection::PFX_Projection() {

    //std::cout << config.screen_scale << " " << this->_width_half << "\n";
}
PFX_Projection::~PFX_Projection()
{
    //dtor
}
std::array<float, 3> PFX_Projection::ProjectPoint( std::array<float, 3> point , PFX_Camera &camera  ) {

    std::array<float, 3> projected;

    const float px = camera.position[ 0 ];
    const float py = camera.position[ 1 ];
    const float pz = camera.position[ 2 ];
    const float nx = camera.normal[ 0 ];
    const float nz = camera.normal[ 2 ];

    const float pitch = camera.angle_v;
    const float pitch_cos = std::cos( pitch );
    const float pitch_sin = std::sin( pitch );
    const float lookAtY = std::tan( pitch ) * LUT_RENDER_SCREEN_SCALE_F;

    const float* pt = point.data();  // каждая точка: x,y,z,u,v
    float* out = projected.data();  // выход для точки

    // Координаты в пространстве камеры
    const float cx = pt[ 0 ] - px;
    const float cy = pt[ 1 ] - py;
    const float cz = pt[ 2 ] - pz;

    // Расчёт Z в пространстве камеры (ваш алгоритм)
    const float cam_z = -cx * nz + cz * nx;

    // Поворот (ваш алгоритм)
    const float rot_x = cx * nx + cz * nz;
    const float rot_y = ( pt[ 1 ] - camera.camera_y ) * pitch_cos - cam_z * pitch_sin;
    const float rot_z = rot_y * pitch_sin + cam_z * pitch_cos;

    // Расстояние и масштаб
    const float dist = std::max( LUT_PROJECTION_DISTANCE_NEAR , std::abs( rot_z ) );
    const unsigned short dist_idx = static_cast<unsigned short>( dist * 1000 );
    const float dist_inv = LUT_PROJECTION_DIST_INV[ dist_idx ];
    const float scale = LUT_RENDER_SCREEN_SCALE_F * dist_inv;

    // Проекция на экран
    out[ 0 ] = std::floor( LUT_RENDER_SCREEN_WIDTH_HALF_F - ( rot_x * dist_inv ) * LUT_RENDER_SCREEN_SCALE_F + 0.5f );
    out[ 1 ] = std::floor( LUT_RENDER_SCREEN_HEIGHT_HALF_F - rot_y * scale + lookAtY + 0.5f );
    out[ 2 ] = dist; // z для буфера

    return projected;
}
std::array<float, 18> PFX_Projection::ProjectTriangle( const float* points , PFX_Camera &camera ) {
    std::array<float, 18> projected;

    const float px = camera.position[ 0 ];
    const float py = camera.position[ 1 ];
    const float pz = camera.position[ 2 ];
    const float nx = camera.normal[ 0 ];
    const float nz = camera.normal[ 2 ];

    const float pitch = camera.angle_v;
    const float pitch_cos = std::cos( pitch );
    const float pitch_sin = std::sin( pitch );
    const float lookAtY = std::tan( pitch ) * LUT_RENDER_SCREEN_SCALE_F;

    // Обрабатываем три точки
    int p_ind = 0;
    #pragma GCC unroll 3
    for ( int i = 0; i < 3; i++ ) {
        const float* pt = points + p_ind;  // каждая точка: x,y,z,u,v
        float* out = projected.data() + p_ind;  // выход для точки

        // Координаты в пространстве камеры
        const float cx = pt[ 0 ] - px;
        const float cy = pt[ 1 ] - py;
        const float cz = pt[ 2 ] - pz;

        // Расчёт Z в пространстве камеры (ваш алгоритм)
        const float cam_z = -cx * nz + cz * nx;

        // Поворот (ваш алгоритм)
        const float rot_x = cx * nx + cz * nz;
        const float rot_y = ( pt[ 1 ] - camera.camera_y ) * pitch_cos - cam_z * pitch_sin;
        const float rot_z = rot_y * pitch_sin + cam_z * pitch_cos;

        // Расстояние и масштаб
        const float dist = std::max( LUT_PROJECTION_DISTANCE_NEAR , std::abs( rot_z ) );
        const unsigned short dist_idx = static_cast<unsigned short>( dist * 1000 );
        const float dist_inv = LUT_PROJECTION_DIST_INV[ dist_idx ];
        const float scale = LUT_RENDER_SCREEN_SCALE_F * dist_inv;

        // Проекция на экран
        out[ 0 ] = std::floor( LUT_RENDER_SCREEN_WIDTH_HALF_F - ( rot_x * dist_inv ) * LUT_RENDER_SCREEN_SCALE_F + 0.5f );
        out[ 1 ] = std::floor( LUT_RENDER_SCREEN_HEIGHT_HALF_F - rot_y * scale + lookAtY );
        out[ 2 ] = dist;           // z для буфера
        out[ 3 ] = pt[ 3 ];          // u
        out[ 4 ] = pt[ 4 ];          // v
        out[ 5 ] = pt[ 5 ];          // light

        p_ind += LUT_POINT_SIZE;
    }

    return projected;
}
