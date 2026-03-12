#pragma once
#include <array>
#include <cmath>
#include <core/PFX_Plane.h>

class PFX_Camera
{
    private:
    public:
        //Углы
        float angle_h = 0.0f; //Горизонтальный угол
        float angle_v = 0.0f; //Вертикальный угол
        float angle_v_max = 0.8f; //Ограничение поворота камеры
        //Габариты
        float width = 0.6f;
        float width_half = 0.3f;
        float height = 0.5f;
        float height_half = 0.25f;
        //Позиционирование
        std::array<float, 3> position;
        std::array<float, 3> normal;
        std::array<float, 3> player_normal;
        std::array<float, 3> up;
         //Костыли
        float camera_y = 0.0f;
        //Пирамида видимости
        PFX_Plane plane_c;
        PFX_Plane plane_l;
        PFX_Plane plane_r;
        PFX_Plane plane_b;
        PFX_Plane plane_t;
        //Методы
        PFX_Camera();
        ~PFX_Camera();
        void Update();
        void UpdatePyramid();
};
