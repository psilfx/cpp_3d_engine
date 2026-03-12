#pragma once

#include <core/PFX_Camera.h>
#include <core/PFX_Projection.h>
#include <core/PFX_Render.h>
#include <core/PFX_Level.h>
#include <core/PFX_Engine.h>
#include <core/PFX_Config.h>
#include <core/PFX_Player.h>

class PFX_Context
{
    private:
        //Инициализация
        //static PFX_Context* _instance;
        PFX_Context() = default;
        ~PFX_Context() = default;
        // Запрет копирования
        PFX_Context(const PFX_Context&) = delete;
        PFX_Context& operator=(const PFX_Context&) = delete;

        //Для движка
        PFX_Camera _camera;
        PFX_Render _render;
        PFX_Engine _engine;
        PFX_Level _level;
        PFX_Projection _projection;
        PFX_Config _config;
        PFX_Player _player;

    public:
        static PFX_Context& GetInstance();

        void InitEngine();
        void InitCamera();
        void InitRender( GLFWwindow* window );
        void InitLevel();
        void InitProjection();
        void InitConfig( int screen_width , int screen_height );
        void InitPlayer();

        PFX_Camera& Camera();
        PFX_Render& Render();
        PFX_Engine& Engine();
        PFX_Level& Level();
        PFX_Projection& Projection();
        PFX_Config& Config();
        PFX_Player& Player();
};
