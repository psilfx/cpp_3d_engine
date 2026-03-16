#include "PFX_Camera.h"
#include <core/PFX_Vector.h>
#include <core/PFX_Lut.h>

PFX_Camera::PFX_Camera() {
    this->position = {0};
    this->up = { 0.0f , 1.0f , 0.0f };
}
void PFX_Camera::UpdatePyramid() {
    const float yaw_sin = std::sin( this->angle_h );
    const float yaw_cos = std::cos( this->angle_h );
    const float pitch_sin = std::sin( this->angle_v );
    const float pitch_cos = std::cos( this->angle_v );

    this->plane_c.normal[ 0 ] = yaw_cos * pitch_cos;
    this->plane_c.normal[ 1 ] = pitch_sin;
    this->plane_c.normal[ 2 ] = yaw_sin * pitch_cos;

    this->plane_l.normal[ 0 ] = std::cos( this->angle_h + LUT_FOV_H ) * pitch_cos;
    this->plane_l.normal[ 1 ] = pitch_sin;
    this->plane_l.normal[ 2 ] = std::sin( this->angle_h + LUT_FOV_H ) * pitch_cos;

    this->plane_r.normal[ 0 ] = std::cos( this->angle_h - LUT_FOV_H ) * pitch_cos;
    this->plane_r.normal[ 1 ] = pitch_sin;
    this->plane_r.normal[ 2 ] = std::sin( this->angle_h - LUT_FOV_H ) * pitch_cos;


    this->plane_b.normal[ 0 ] = yaw_cos * std::cos( this->angle_v - LUT_V_FOV_H + 1.37 );
    this->plane_b.normal[ 1 ] = std::sin( this->angle_v - LUT_V_FOV_H + 1.37 );
    this->plane_b.normal[ 2 ] = yaw_sin * std::cos( this->angle_v - LUT_V_FOV_H + 1.37 );

    this->plane_t.normal[ 0 ] = yaw_cos * std::cos( this->angle_v + LUT_V_FOV_H - 1.27 );
    this->plane_t.normal[ 1 ] = std::sin( LUT_V_FOV_H + this->angle_v - 1.27 );
    this->plane_t.normal[ 2 ] = yaw_sin * std::cos( this->angle_v + LUT_V_FOV_H - 1.27 );

    this->plane_c.position[ 0 ] = this->position[ 0 ] + this->player_normal[ 0 ] * 0.1f;
    this->plane_c.position[ 1 ] = this->camera_y;
    this->plane_c.position[ 2 ] = this->position[ 2 ] + this->player_normal[ 2 ] * 0.1f;

    this->plane_l.position[ 0 ] = this->position[ 0 ] ;
    this->plane_l.position[ 1 ] = this->camera_y;
    this->plane_l.position[ 2 ] = this->position[ 2 ] ;

    this->plane_r.position[ 0 ] = this->position[ 0 ] ;
    this->plane_r.position[ 1 ] = this->camera_y;
    this->plane_r.position[ 2 ] = this->position[ 2 ] ;

    this->plane_b.position[ 0 ] = this->position[ 0 ] ;
    this->plane_b.position[ 1 ] = this->camera_y;
    this->plane_b.position[ 2 ] = this->position[ 2 ] ;

    this->plane_t.position[ 0 ] = this->position[ 0 ] ;
    this->plane_t.position[ 1 ] = this->camera_y;
    this->plane_t.position[ 2 ] = this->position[ 2 ] ;

    this->plane_c.Update();
    this->plane_r.Update();
    this->plane_l.Update();
    this->plane_t.Update();
    this->plane_b.Update();
}
void PFX_Camera::Update() {
    this->camera_y = this->position[ 1 ] + this->height;
    this->UpdatePyramid();
}
PFX_Camera::~PFX_Camera() {

}
