#pragma once
#include <array>
#include <cstdint>

class PFX_Triangle
{
    public:
        std::array<float, 18> points;
        std::array<float, 18> points_transformed;
        std::array<float, 3> normal;
        std::array<float, 3> normal_transformed;

        PFX_Triangle();
        PFX_Triangle( std::array<float, 5> p1 , std::array<float, 5> p2 , std::array<float, 5> p3 , std::array<float, 3> n );
        void SetPoint( int id , float x , float y , float z , float u , float v );
        void SetPoint( int id , std::array<float, 5> p1 );
        std::array<float, 6> GetPoint( int id );
        ~PFX_Triangle();
};
