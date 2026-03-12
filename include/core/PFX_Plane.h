#pragma once

#include <array>

class PFX_Plane
{
    public:
        std::array<float, 3> position;
        std::array<float, 3> normal;
        PFX_Plane();
        ~PFX_Plane();
        float Distance();
        bool PointInFront( const float* vec );
};
