#include "PFX_Raycast_Light.h"

PFX_Raycast_Light::PFX_Raycast_Light() {
    //ctor
}

void PFX_Raycast_Light::Ray( PFX_Level& level , std::array<float, 3> dir , float accuracy ) {
    float* sizes = level.GetSizes().data();
    float* directrion = dir.data();
}

PFX_Raycast_Light::~PFX_Raycast_Light() {
    //dtor
}
