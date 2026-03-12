#pragma once
#include <array>

[[nodiscard]] inline std::array<float, 3> Vector3F_Create( const float x , const float y , const float z ) {
    return { x , y , z };
}
[[nodiscard]] inline std::array<float, 3> Vector3F_Plus( const std::array<float, 3>& v1 , const std::array<float, 3>& v2 ) {
    return { v2[ 0 ] + v1[ 0 ] , v2[ 1 ] + v1[ 1 ] , v2[ 2 ] + v1[ 2 ] };
}
[[nodiscard]] inline std::array<float, 3> Vector3F_Subtract( const std::array<float, 3> &v1 , const std::array<float, 3> &v2 ) {
    return { v2[ 0 ] - v1[ 0 ] , v2[ 1 ] - v1[ 1 ] , v2[ 2 ] - v1[ 2 ] };
}
[[nodiscard]] inline std::array<float, 3> Vector3F_Multiply( const std::array<float, 3> &v , const float mult ) {
	return { v[ 0 ] * mult , v[ 1 ] * mult , v[ 2 ] * mult };
}
[[nodiscard]] inline std::array<float, 3> Vector3F_Cross( const std::array<float, 3> &v1 , const std::array<float, 3> &v2 ) {
	return { v1[ 2 ] * v2[ 1 ] - v1[ 1 ] * v2[ 2 ] , v1[ 0 ] * v2[ 2 ] - v1[ 2 ] * v2[ 0 ] , v1[ 1 ] * v2[ 0 ] - v1[ 0 ] * v2[ 1 ] };
}
[[nodiscard]] inline float Vector3F_Dot( const std::array<float, 3> &v1 , const std::array<float, 3> &v2 ) {
    return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}
[[nodiscard]] inline float Vector3F_Dot( const float* v1 , const float* v2 ) {
    return v1[ 0 ] * v2[ 0 ] + v1[ 1 ] * v2[ 1 ] + v1[ 2 ] * v2[ 2 ];
}
//Vector2F
[[nodiscard]] inline std::array<float, 2> Vector2F_Plus( const std::array<float, 2> &v1 , const std::array<float, 2> &v2 ) {
     return { v1[ 0 ] + v2[ 0 ] , v1[ 1 ] + v2[ 1 ] };
}
