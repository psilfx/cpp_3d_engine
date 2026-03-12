#pragma once

#include <core/PFX_camera.h>

class PFX_Projection
{
    private:

    public:
        PFX_Projection();
        ~PFX_Projection();
        std::array<float, 18> ProjectTriangle( const float* points , PFX_Camera &camera );
        std::array<float, 3> ProjectPoint( std::array<float, 3> point , PFX_Camera &camera );
};
