#pragma once
#include <array>

struct Collision_Box {
    std::array<float, 3> position = {0};
    std::array<float, 3> heights = {0};
};

class PFX_Collision {
    public:
        PFX_Collision();
        ~PFX_Collision();
        static bool AABB( Collision_Box box_1 , Collision_Box box_2 );
};
