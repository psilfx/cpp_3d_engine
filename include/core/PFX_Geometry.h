#pragma once
#include <core\PFX_Triangle.h>
#include <core\PFX_Texture.h>
#include <core\PFX_Triangle_Clipper.h>
#include <core\PFX_Collision.h>
#include <array>
#include <vector>
#include <string>

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
        //Collision
        Collision_Box collision_box;
        float distance = 0.0f;
        //
        bool updated = false;
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
        void Transform();
        unsigned short TrianglesNum();
        std::vector<float>& GetPoints();
        void CreateCollisionBoxFromPoints();
        float* GetPointsF();
        void UpdateNormal();
        void Update();
        void UpdateStatic();
        void Draw();
        ~PFX_Geometry();
};

//Создаёт простой куб из геометрии
inline void Geometry_Create_Cube( PFX_Geometry& geometry , std::array<float, 3> position , float width , float height , float length , std::string texture_path ) {
    float width_h = width * 0.5f;
    float height_h = height * 0.5f;
    float length_h = length * 0.5f;
    //Низ
    PFX_Triangle tri1;
    tri1.SetPoint( 0 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri1.SetPoint( 1 , width_h , -height_h , -length_h , 1.0f , 0.0f );
    tri1.SetPoint( 2 , width_h , -height_h , length_h , 1.0f , 1.0f );
    tri1.normal = { 0.0f , 1.0f , 0.0f };
    PFX_Triangle tri2;
    tri2.SetPoint( 0 , width_h , -height_h , length_h , 1.0f , 1.0f );
    tri2.SetPoint( 1 , -width_h , -height_h , length_h , 0.0f , 1.0f );
    tri2.SetPoint( 2 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri2.normal = { 0.0f , 1.0f , 0.0f };
    //Верх
    PFX_Triangle tri3;
    tri3.SetPoint( 0 , -width_h , height_h , -length_h , 0.0f , 0.0f );
    tri3.SetPoint( 1 , width_h , height_h , -length_h , 1.0f , 0.0f );
    tri3.SetPoint( 2 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri3.normal = { 0.0f , -1.0f , 0.0f };
    PFX_Triangle tri4;
    tri4.SetPoint( 0 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri4.SetPoint( 1 , -width_h , height_h , length_h , 0.0f , 1.0f );
    tri4.SetPoint( 2 , -width_h , height_h , -length_h , 0.0f , 0.0f );
    tri4.normal = { 0.0f , -1.0f , 0.0f };
    //Дальняя часть
    PFX_Triangle tri5;
    tri5.SetPoint( 0 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri5.SetPoint( 1 , width_h , -height_h , -length_h , 1.0f , 0.0f );
    tri5.SetPoint( 2 , width_h , height_h , -length_h , 1.0f , 1.0f );
    tri5.normal = { 0.0f , 0.0f , 1.0f };
    PFX_Triangle tri6;
    tri6.SetPoint( 0 , width_h , height_h , -length_h , 1.0f , 1.0f );
    tri6.SetPoint( 1 , -width_h , height_h , -length_h , 0.0f , 1.0f );
    tri6.SetPoint( 2 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri6.normal = { 0.0f , 0.0f , 1.0f };
    //Ближняя часть
    PFX_Triangle tri7;
    tri7.SetPoint( 0 , -width_h , -height_h , length_h , 0.0f , 0.0f );
    tri7.SetPoint( 1 , width_h , -height_h , length_h , 1.0f , 0.0f );
    tri7.SetPoint( 2 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri7.normal = { 0.0f , 0.0f , -1.0f };
    PFX_Triangle tri8;
    tri8.SetPoint( 0 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri8.SetPoint( 1 , -width_h , height_h , length_h , 0.0f , 1.0f );
    tri8.SetPoint( 2 , -width_h , -height_h , length_h , 0.0f , 0.0f );
    tri8.normal = { 0.0f , 0.0f , -1.0f };
    //Правая часть
    PFX_Triangle tri9;
    tri9.SetPoint( 0 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri9.SetPoint( 1 , -width_h , height_h , -length_h , 1.0f , 0.0f );
    tri9.SetPoint( 2 , -width_h , height_h , length_h , 1.0f , 1.0f );
    tri9.normal = { 1.0f , 0.0f , 0.0f };
    PFX_Triangle tri10;
    tri10.SetPoint( 0 , -width_h , height_h , length_h , 1.0f , 1.0f );
    tri10.SetPoint( 1 , -width_h , -height_h , length_h , 0.0f , 1.0f );
    tri10.SetPoint( 2 , -width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri10.normal = { 1.0f , 0.0f , 0.0f };
    //Левая часть
    PFX_Triangle tri11;
    tri11.SetPoint( 0 , width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri11.SetPoint( 1 , width_h , height_h , -length_h , 1.0f , 0.0f );
    tri11.SetPoint( 2 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri11.normal = { -1.0f , 0.0f , 0.0f };
    PFX_Triangle tri12;
    tri12.SetPoint( 0 , width_h , height_h , length_h , 1.0f , 1.0f );
    tri12.SetPoint( 1 , width_h , -height_h , length_h , 0.0f , 1.0f );
    tri12.SetPoint( 2 , width_h , -height_h , -length_h , 0.0f , 0.0f );
    tri12.normal = { -1.0f , 0.0f , 0.0f };

    geometry.AddTriangle( tri1 );
    geometry.AddTriangle( tri2 );
    geometry.AddTriangle( tri3 );
    geometry.AddTriangle( tri4 );
    geometry.AddTriangle( tri5 );
    geometry.AddTriangle( tri6 );
    geometry.AddTriangle( tri7 );
    geometry.AddTriangle( tri8 );
    geometry.AddTriangle( tri9 );
    geometry.AddTriangle( tri10 );
    geometry.AddTriangle( tri11 );
    geometry.AddTriangle( tri12 );
    geometry.SetTexture( texture_path );
    geometry.Translate( { position[ 0 ] + width_h , position[ 1 ] + height_h , position[ 2 ] + length_h } );
    geometry.UpdateNormal();

    geometry.CreateCollisionBoxFromPoints();
}
