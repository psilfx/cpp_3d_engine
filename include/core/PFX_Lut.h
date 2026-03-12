#pragma once
#include <cstdint>

// ќбъ€вл€ем массивы как extern
extern const float radian;
extern float LUT_TIME_DELTA;
extern const float LUT_PI;
extern const float LUT_PI_DOUBLE;
extern float LUT_FOV;
extern float LUT_FOV_H;
extern float LUT_V_FOV;
extern float LUT_V_FOV_H;
extern float LUT_SIN[ 10000 ];      // дл€ углов в радианах ( угол в радианах * 1000 )
extern float LUT_COS[ 10000 ];
extern float LUT_DIST_INV[ 10000 ]; // предрасчитанные 1/n
//
extern const float LUT_PROJECTION_DISTANCE_NEAR;
extern const float LUT_PROJECTION_DISTANCE_FAR;
extern float LUT_PROJECTION_DIST_INV[ 100000 ];
//
extern uint_fast32_t LUT_RENDER_BUFF_Y[ 10000 ];
extern uint_fast32_t LUT_RENDER_BUFF_X[ 10000 ];
extern uint_fast16_t LUT_RENDER_TEXTURE_Y[ 10000 ];
extern uint_fast16_t LUT_RENDER_TEXTURE_X[ 10000 ];
extern uint_fast32_t LUT_RENDER_BUFF_MAX_INDEX;
extern uint_fast32_t LUT_RENDER_TEXTURE_MAX_INDEX;
extern uint_fast16_t LUT_RENDER_SCREEN_WIDTH;
extern uint_fast16_t LUT_RENDER_SCREEN_WIDTH_HALF;
extern uint_fast16_t LUT_RENDER_SCREEN_HEIGHT;
extern uint_fast16_t LUT_RENDER_SCREEN_HEIGHT_HALF;
extern uint_fast16_t LUT_RENDER_SCREEN_SCALE;
extern float LUT_RENDER_SCREEN_WIDTH_F;
extern float LUT_RENDER_SCREEN_WIDTH_HALF_F;
extern float LUT_RENDER_SCREEN_HEIGHT_F;
extern float LUT_RENDER_SCREEN_HEIGHT_HALF_F;
extern float LUT_RENDER_SCREEN_SCALE_F;
//
extern uint_fast8_t LUT_RENDER_TEXTURE_SIZE;
extern float LUT_RENDER_TEXTURE_SIZE_F;
extern float LUT_RENDER_TEXTURE_Z_INV[ 10000 ];
extern uint_fast8_t LUT_RENDER_TEXTURE_DIVISION[ 10000 ];
//
extern const int LUT_POINT_SIZE;
extern const int LUT_POINT_SIZE_2;
extern const int LUT_POINT_SIZE_3;
extern const int LUT_POINT_SIZE_4;
extern const int LUT_POINT_SIZE_5;

void InitLUT();
void InitRenderLut();
