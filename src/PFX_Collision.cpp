#include "PFX_Collision.h"

PFX_Collision::PFX_Collision() {
    //ctor
}
bool PFX_Collision::AABB( Collision_Box box_1 , Collision_Box box_2 ) {
    const float* p1 = box_1.position.data();
    const float* p2 = box_2.position.data();
    const float* h1 = box_1.heights.data();
    const float* h2 = box_2.heights.data();
    return ( p1[ 0 ] <= p2[ 0 ] + h2[ 0 ] && p1[ 0 ] + h1[ 0 ] >= p2[ 0 ] ) &&
           ( p1[ 1 ] <= p2[ 1 ] + h2[ 1 ] && p1[ 1 ] + h1[ 1 ] >= p2[ 1 ] ) &&
           ( p1[ 2 ] <= p2[ 2 ] + h2[ 2 ] && p1[ 2 ] + h1[ 2 ] >= p2[ 2 ] );
}
PFX_Collision::~PFX_Collision() {
    //dtor
}
