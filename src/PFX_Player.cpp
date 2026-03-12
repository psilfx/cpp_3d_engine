#include "PFX_Player.h"
#include <core/PFX_Vector.h>
#include <iostream>

PFX_Player::PFX_Player()
{
    this->_position[ 0 ] = 7.0f;
    this->_position[ 1 ] = 0.0f;
    this->_position[ 2 ] = 2.0f;
    this->_up[ 0 ] = 0.0f;
    this->_up[ 1 ] = 1.0f;
    this->_up[ 2 ] = 0.0f;
    this->_angle_h = 3.14;
}
void PFX_Player::UpdateCamera() {
    this->_camera->position = this->_position;
    this->_camera->normal = this->_normal_camera;
    this->_camera->player_normal = this->_normal;
    this->_camera->up = this->_up;
    this->_camera->angle_h = this->_angle_h;
    this->_camera->angle_v = this->_angle_v;
    this->_camera->angle_v_max = this->_angle_v_max;
    this->_camera->height = this->_height;
    this->_camera->height_half = this->_height_half;
    this->_camera->width = this->_width;
    this->_camera->width_half = this->_width_half;
}
void PFX_Player::UpdateMove() {
    std::array<float, 2> move_vector = Vector2F_Plus( this->_forward , this->_strafe );
    this->_position[ 0 ] += move_vector[ 0 ];
    this->_position[ 2 ] += move_vector[ 1 ];
    this->_position[ 0 ] = std::max( this->_position[ 0 ] , 0.0f );
    this->_position[ 2 ] = std::max( this->_position[ 2 ] , 0.0f );
}
std::array<float, 3>& PFX_Player::GetNormal(){
    return this->_normal;
}
void PFX_Player::Update() {
    //Нормаль
    this->_normal[ 0 ] = std::cos( this->_angle_h );
    this->_normal[ 1 ] = 0.0f;
    this->_normal[ 2 ] = std::sin( this->_angle_h );
    this->_normal_camera[ 0 ] = std::cos( this->_angle_h - 1.57f );
    this->_normal_camera[ 1 ] = 0.0f;
    this->_normal_camera[ 2 ] = std::sin( this->_angle_h - 1.57f );
    this->UpdateMove();
    this->UpdateCamera();
    this->_strafe[ 0 ] = 0.0f;
    this->_strafe[ 1 ] = 0.0f;
    this->_forward[ 0 ] = 0.0f;
    this->_forward[ 1 ] = 0.0f;
}
void PFX_Player::SetCamera( PFX_Camera& camera ) {
    this->_camera = &camera;
}
void PFX_Player::Control( int move_forward , int move_strafe , float ang_h , float ang_v ) {
    std::array<float, 3> position_strafe = Vector3F_Cross( this->_normal , this->_up );
    float move_speed = LUT_TIME_DELTA * this->_speed;
    float rot_speed = LUT_TIME_DELTA * this->_speed_rotation;

    this->_angle_h += ang_h * rot_speed;

    while ( this->_angle_h > LUT_PI )  this->_angle_h -= LUT_PI_DOUBLE;
    while ( this->_angle_h < -LUT_PI ) this->_angle_h += LUT_PI_DOUBLE;

    this->_strafe[ 0 ]  = ( move_speed * position_strafe[ 0 ] ) * static_cast<float>( -move_strafe );
    this->_strafe[ 1 ]  = ( move_speed * position_strafe[ 2 ] ) * static_cast<float>( -move_strafe );
    this->_forward[ 0 ] = ( move_speed * this->_normal[ 0 ] ) * static_cast<float>( move_forward );
    this->_forward[ 1 ] = ( move_speed * this->_normal[ 2 ] ) * static_cast<float>( move_forward );
}
PFX_Player::~PFX_Player()
{
    //dtor
}
