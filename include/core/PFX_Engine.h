#pragma once

#include <string>
#include <core/PFX_Render.h>
#include <core/PFX_Camera.h>
#include <core/PFX_Level.h>
#include <core/PFX_Player.h>

class PFX_Engine
{
    private:
    PFX_Render* _render = nullptr;
    PFX_Camera* _camera = nullptr;
    PFX_Level* _level = nullptr;
    PFX_Player* _player = nullptr;
    public:
        float time_delta = 0.0f;
        PFX_Engine();
        void Init();
        ~PFX_Engine();
        void Update();
        void Draw();
};
