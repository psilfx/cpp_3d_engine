#pragma once

#include <core/PFX_Camera.h>
#include <core/PFX_Lut.h>

class PFX_Player
{
    private:
        PFX_Camera* _camera;
        //Углы
        float _angle_h = 0.0f; //Горизонтальный угол
        float _angle_v = 0.0f; //Вертикальный угол
        float _angle_v_max = 0.8f; //Ограничение поворота камеры
        //Габариты
        float _width = 0.6f;
        float _width_half = 0.3f;
        float _height = 0.5f;
        float _height_half = 0.25f;
        //Позиционирование
        std::array<float, 3> _position;
        std::array<float, 3> _position_max;
        std::array<float, 3> _normal;
        std::array<float, 3> _normal_camera;
        std::array<float, 3> _up;
        //Характеристики
        float _speed = 3.00f;
        float _speed_rotation = 3.00f;
        //Движение
        std::array<float, 2> _strafe;
        std::array<float, 2> _forward;
    public:
        PFX_Player();
        ~PFX_Player();
        void Update();
        void UpdateCamera();
        void UpdateMove();
        std::array<float, 3>& GetNormal();
        void Control( int move_forward , int move_strafe , float ang_h , float ang_v );
        void SetCamera( PFX_Camera& camera );
        void SetPositionMax( std::array<float, 3> ); //Позиционирование для обрезки по границе уровня
};
