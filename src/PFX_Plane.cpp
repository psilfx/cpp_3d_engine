#include "PFX_Plane.h"
#include <core\PFX_Vector.h>

PFX_Plane::PFX_Plane() {
    this->position = {0};
    this->normal = {0};
}
float PFX_Plane::Distance() {
    float* n_d = this->normal.data();
    float* p_d = this->position.data();
    return Vector3F_Dot( n_d , p_d );
}
//Vec - float[5] точки x y z u v
bool PFX_Plane::PointInFront( const float* vec ) {
    float* n_d = this->normal.data();
    float* p_d = this->position.data();
    return Vector3F_Dot( n_d , vec ) - Vector3F_Dot( n_d , p_d ) > 0.0f;
}
PFX_Plane::~PFX_Plane() {

}
