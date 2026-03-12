#pragma once
#include <cmath>
#include <array>

[[nodiscard]] inline std::array<float, 4> EulerToQuaternion( float yaw , float pitch , float roll ) {
    float cy = std::cos( yaw * 0.5f );
    float sy = std::sin( yaw * 0.5f );
    float cp = std::cos( pitch * 0.5f );
    float sp = std::sin( pitch * 0.5f );
    float cr = std::cos( roll * 0.5f );
    float sr = std::sin( roll * 0.5f );
    //w , x , y , z
    return { cy * cp * cr + sy * sp * sr , cy * cp * sr - sy * sp * cr , sy * cp * sr + cy * sp * cr , sy * cp * cr - cy * sp * sr };
}

[[nodiscard]] inline std::array<float, 9> QuaternionToBasis( const float q[ 4 ] ) {
    float w = q[ 0 ] , x = q[ 1 ] , y = q[ 2 ] , z = q[ 3 ];

    //    // forward (Z axis)
//    forward[ 0 ] = 2.0f * ( x * z + w * y );
//    forward[ 1 ] = 2.0f * ( y * z - w * x );
//    forward[ 2 ] = 1.0f - 2.0f * ( x * x + y * y );
//
//    // right (X axis)
//    right[ 0 ] = 1.0f - 2.0f * ( y * y + z * z );
//    right[ 1 ] = 2.0f * ( x * y + w * z );
//    right[ 2 ] = 2.0f * ( x * z - w * y );
//
//    // up (Y axis)
//    up[ 0 ] = 2.0f * ( x * y - w * z );
//    up[ 1 ] = 1.0f - 2.0f * ( x * x + z * z );
//    up[ 2 ] = 2.0f * ( y * z + w * x );
    return { 2.0f * ( x * z + w * y ) , 2.0f * ( y * z - w * x ) , 1.0f - 2.0f * ( x * x + y * y ) ,
            1.0f - 2.0f * ( y * y + z * z ) , 2.0f * ( x * y + w * z ) , 2.0f * ( x * z - w * y ) ,
            2.0f * ( x * y - w * z ) , 1.0f - 2.0f * ( x * x + z * z ) , 2.0f * ( y * z + w * x )
            };

}
