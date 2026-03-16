#pragma once
#include <array>
#include <core\PFX_Level.h>

class PFX_Raycast_Light {
    private:

    public:
        static void Ray( PFX_Level& level , std::array<float, 3> dir , float accuracy );

        PFX_Raycast_Light();
        ~PFX_Raycast_Light();
};
