#pragma once
#include <cstdint>
#include <core/PFX_Lut.h>

class PFX_Config
{
    private:
        int _width = 0;
        int _height = 0;
        int _width_half = 0;
        int _height_half = 0;
        int _screen_scale = 0;
        float _aspect_ratio  = 0;
        float _fov = 0;
        float _fov_half = 0;
        float _fov_vertical = 0;
        float _fov_vertical_half = 0;
        float _tan_fov_half = 0;
        float _tan_fov_half_v = 0;
        float _distance_near = 0;
        float _distance_far = 0;
        uint8_t _texture_size = 0;
    public:
        int width = 0;
        int height = 0;
        int width_half = 0;
        int height_half = 0;
        int screen_scale = 0;
        float aspect_ratio  = 0;
        float fov = 0;
        float fov_half = 0;
        float fov_vertical = 0;
        float fov_vertical_half = 0;
        float tan_fov_half = 0;
        float tan_fov_half_v = 0;
        float distance_near = 0;
        float distance_far = 0;
        uint8_t texture_size = 0;
        PFX_Config();
        void Init( int screen_width , int screen_height );
        void Copy();
        void CopyToLUT();
        ~PFX_Config();
};

