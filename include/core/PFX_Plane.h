#pragma once

#include <array>

class PFX_Plane
{
    public:
        std::array<float, 3> position;
        std::array<float, 3> normal;
        float distance;
        PFX_Plane();
        ~PFX_Plane();
        void Update();
        bool PointInFront( const float* vec );
};
