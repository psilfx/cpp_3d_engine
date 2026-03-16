#include "PFX_Plane.h"
#include <core\PFX_Vector.h>

PFX_Plane::PFX_Plane() {
    this->position = {0};
    this->normal = {0};
}
//Vec - float[5] точки x y z u v
bool PFX_Plane::PointInFront( const float* vec ) {
    float* n_d = this->normal.data();
    float* p_d = this->position.data();
    return Vector3F_Dot( n_d , vec ) - this->distance > 0.0f;
}
void PFX_Plane::Update() {
    float* n_d = this->normal.data();
    float* p_d = this->position.data();
    this->distance = Vector3F_Dot( n_d , p_d );
}
PFX_Plane::~PFX_Plane() {

}
