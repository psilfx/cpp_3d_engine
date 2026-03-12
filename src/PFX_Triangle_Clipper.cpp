#include "PFX_Triangle_Clipper.h"
#include <core/PFX_Lut.h>
#include <core/PFX_Vector.h>
#include <iostream>
#include <algorithm>


inline void CopyTrianglePoint( float* buffer , const float* point ) {
    std::copy_n( point , 5 , buffer );
}

PFX_Triangle_Clipper::PFX_Triangle_Clipper()
{
    //ctor
}
std::array<float, 6> PFX_Triangle_Clipper::IntersectEdgeWithPlane( PFX_Plane &plane , const float* edge_start , const float* edge_end ) {
    const float* normal = plane.normal.data();
    const float ad = Vector3F_Dot( edge_start , normal );
    const float bd = Vector3F_Dot( edge_end , normal );
    const float denominator = bd - ad;
    // Защита от деления на ноль
    // Параллельно плоскости - возвращаем начальную точку
    if ( std::abs( denominator ) < 1e-6f ) return { edge_start[ 0 ] , edge_start[ 1 ] , edge_start[ 2 ] , edge_start[ 3 ] , edge_start[ 4 ] };
    const float t = std::clamp( ( plane.Distance() - ad ) / denominator , LUT_PROJECTION_DISTANCE_NEAR , 1.0f );
    return {
        edge_start[ 0 ] + ( edge_end[ 0 ] - edge_start[ 0 ] ) * t,
        edge_start[ 1 ] + ( edge_end[ 1 ] - edge_start[ 1 ] ) * t,
        edge_start[ 2 ] + ( edge_end[ 2 ] - edge_start[ 2 ] ) * t,
        edge_start[ 3 ] + ( edge_end[ 3 ] - edge_start[ 3 ] ) * t,
        edge_start[ 4 ] + ( edge_end[ 4 ] - edge_start[ 4 ] ) * t,
        edge_start[ 5 ]
    };
}
uint8_t PFX_Triangle_Clipper::Clip( PFX_Plane &plane , const float* triangle , float* buffer ) {
    return PFX_Triangle_Clipper::Clip( plane , triangle , buffer , buffer + LUT_POINT_SIZE_3 );
}
uint8_t PFX_Triangle_Clipper::Clip( PFX_Plane &plane , const float* triangle , float* triangle_1_buffer , float* triangle_2_buffer  ) {

    int inside_count = 0;
    int outside_count = 0;

    int inside_points[ 3 ];
    int outside_points[ 3 ];

    #pragma GCC unroll 3
    for( int p = 0; p < 3; p++ ) {
        const int i = p * LUT_POINT_SIZE;
        const float* point = triangle + i;
        if( plane.PointInFront( point ) ) {
            inside_points[ inside_count++ ] = i;
        } else {
            outside_points[ outside_count++ ] = i;
        }
    }

    if ( outside_count == 3 ) return 0;
    if ( inside_count == 3 ) {
        std::copy_n( triangle , LUT_POINT_SIZE_3 , triangle_1_buffer );
        return 1;
    }
    float tmp[ 18 ];
    std::copy_n( triangle , LUT_POINT_SIZE_3 , tmp );
    if ( outside_count == 1 && inside_count == 2 ) {

        const float* point_in_1 = tmp + inside_points[ 0 ];
        const float* point_in_2 = tmp + inside_points[ 1 ];
        const float* point_out = tmp + outside_points[ 0 ];

        // Вычисляем точки пересечения
        auto clipped_1 = PFX_Triangle_Clipper::IntersectEdgeWithPlane( plane, point_in_1, point_out );
        auto clipped_2 = PFX_Triangle_Clipper::IntersectEdgeWithPlane( plane, point_in_2, point_out );

        std::copy_n( point_in_1 , LUT_POINT_SIZE , triangle_1_buffer );
        std::copy_n( point_in_2 , LUT_POINT_SIZE , triangle_1_buffer + LUT_POINT_SIZE );
        std::copy_n( clipped_1.data() , LUT_POINT_SIZE , triangle_1_buffer + LUT_POINT_SIZE_2 );

        std::copy_n( point_in_2 , LUT_POINT_SIZE , triangle_2_buffer );
        std::copy_n( clipped_1.data() , LUT_POINT_SIZE , triangle_2_buffer + LUT_POINT_SIZE );
        std::copy_n( clipped_2.data() , LUT_POINT_SIZE , triangle_2_buffer + LUT_POINT_SIZE_2 );

        return 2;
    }
    if ( outside_count == 2 && inside_count == 1 ) {

        const float* point_in = tmp + inside_points[ 0 ];
        const float* point_out_1 = tmp + outside_points[ 0 ];
        const float* point_out_2 = tmp + outside_points[ 1 ];

        auto clipped_1 = PFX_Triangle_Clipper::IntersectEdgeWithPlane( plane , point_in , point_out_1 );
        auto clipped_2 = PFX_Triangle_Clipper::IntersectEdgeWithPlane( plane , point_in , point_out_2 );

        std::copy_n( point_in , LUT_POINT_SIZE , triangle_1_buffer );
        std::copy_n( clipped_1.data() , LUT_POINT_SIZE , triangle_1_buffer + LUT_POINT_SIZE );
        std::copy_n( clipped_2.data() , LUT_POINT_SIZE , triangle_1_buffer + LUT_POINT_SIZE_2 );

        return 1;
    }
    return 0;
}
PFX_Triangle_Clipper::~PFX_Triangle_Clipper()
{
    //dtor
}
