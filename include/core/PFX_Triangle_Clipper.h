#pragma once
#include <core/PFX_Plane.h>
#include <cmath>
#include <cstdint>

class PFX_Triangle_Clipper
{
    public:
        PFX_Triangle_Clipper();
        ~PFX_Triangle_Clipper();
        static std::array<float, 6> IntersectEdgeWithPlane( PFX_Plane &plane , const float* edge_start , const float* edge_end );
        static uint8_t Clip( PFX_Plane &plane , const float* triangle , float* buffer );
        static uint8_t Clip( PFX_Plane &plane , const float* triangle , float* triangle_1_buffer , float* triangle_2_buffer ); //Buffer_offset - смещение в буфере для второго треугольника
};
