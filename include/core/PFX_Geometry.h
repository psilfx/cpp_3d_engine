#pragma once
#include <core/PFX_Triangle.h>
#include <core/PFX_Texture.h>
#include <core/PFX_Triangle_Clipper.h>
#include <array>
#include <vector>

class PFX_Geometry
{
    private:
        uint16_t _id = 0;
        //Углы
        float _yaw = 0.0f;
        float _pitch = 0.0f;
        float _roll = 0.0f;
        std::array<float, 4> _quternion = {0};
        //
        std::array<float, 3> _position = {0};
        //Базисные вектора
        std::array<float, 9> _normal = {0}; //forward, right, up
        //
        std::vector<PFX_Triangle> _triangles;
        std::vector<float> _transformed_points;
        unsigned short _triangles_num; //Кол-во треугольников на вывод
        PFX_Texture _texture;
        void _Init( std::array<float, 3> position , std::array<float, 9> normal );
        void _Transform();
    public:

        float distance = 0.0f;
        //
        PFX_Geometry();
        PFX_Geometry( std::array<float, 3> position , std::array<float, 9> normal );
        void AddTriangle( const PFX_Triangle &triangle );
        void AddTriangle( PFX_Triangle&& triangle );
        void SetTexture( std::string path );
        unsigned char& GetTexturePixels();
        void RotateY( float angle );
        void RotateX( float angle );
        void RotateZ( float angle );
        void Translate( std::array<float, 3> position );
        unsigned short TrianglesNum();
        std::vector<float>& GetPoints();
        float* GetPointsF();
        void UpdateNormal();
        void Update();
        void Draw();
        ~PFX_Geometry();
};
