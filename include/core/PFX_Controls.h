#pragma once

#include <core/PFX_Player.h>

class PFX_Controls
{
    private:
        PFX_Player* _player;
    public:
        bool movekey          = false;
        bool key_up           = false;
        bool key_down         = false;
        bool key_left         = false;
        bool key_left_strafe  = false;
        bool key_right        = false;
        bool key_right_strafe = false;
        bool key_jump         = false;
        bool key_crouch       = false;

        PFX_Controls();
        ~PFX_Controls();
        void Input( int key , bool flag );
        void SetPlayer( PFX_Player& player );
        void Update();
};
