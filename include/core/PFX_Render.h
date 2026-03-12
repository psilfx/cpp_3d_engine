#pragma once

#include <glfw/glfw3.h>
#include <array>
#include <memory>
#include <algorithm>
#include <core/PFX_Projection.h>
#include <core/PFX_Camera.h>
#include <core/PFX_Texture.h>
#include <core/PFX_Lut.h>
#include <core/PFX_Geometry.h>

class PFX_Render
{
    private:
    GLFWwindow* _window;
    PFX_Projection* _projection;
    PFX_Camera* _camera;
    std::unique_ptr<unsigned char[]> _frame_pixels;
    std::vector<float> _frame_z;
    GLuint _frame_texture;
    PFX_Texture _texture;
    PFX_Geometry _geometry;
    std::vector<float> _points_buffer;
    unsigned int _triangles_number = 0; //Количество треугольников
    unsigned int _triangle_current = 0; //Текущий треугольник по счёту для рендера
    unsigned int _triangle_current_index = 0; //Индекс текущего треугольника по счёту +15
    public:

        PFX_Render();
        void Init( GLFWwindow* window );
        ~PFX_Render();
        void ScanlineTriangle( std::array<float, 3> projected1 , std::array<float, 3> projected2 , std::array<float, 3> projected3 ,
                               std::array<float, 2> uv1 , std::array<float, 2> uv2 , std::array<float, 2> uv3 , unsigned char* texture_pixels );
//        void ScanlineTriangle( float projected1[ 5 ] , float projected2[ 5 ] , float projected3[ 5 ] , unsigned char* texture_pixels );
        void ScanlineTriangle( const float* projected1 , const float* projected2 , const float* projected3 , unsigned char* texture_pixels );
        void ScanlineRectangle( std::array<float, 3> position , float width , float height );
        void Geometry( PFX_Geometry &geometry );
        void Update();
        void Draw();
        void SkyBox();
        void SetCamera( PFX_Camera& camera );
        void SetProjection( PFX_Projection& projection );
        void FillTriangle( short &y_1 , short &startY , short &endY , float &way1_x , float &way2_x ,
                              float &u1_start , float &u2_start , float &v1_start , float &v2_start , float &z1_way , float &z2_way ,
                              float &u1_way , float &u2_way , float &v1_way , float &v2_way ,
                                const float &dir1_x , const float &dir2_x , const float &step1_u , const float &step2_u , const float &step1_v , const float &step2_v ,
                                const float &z1_step , const float &z2_step , float &l1_way , float &l2_way , const float &l1_step , const float &l2_step ,
                                unsigned char* pixels , float* z_buffer , unsigned char* texture_pixels );
        int GetTexturePixelIndexByUVZ( float &u , float &v , float &z );
};
