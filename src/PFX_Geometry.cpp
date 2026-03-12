#include "PFX_Geometry.h"
#include <cmath>
#include <core\PFX_Context.h>
#include <core\PFX_Lut.h>
#include <core\PFX_Vector.h>
#include <iostream>

PFX_Geometry::PFX_Geometry() {
    this->_Init( { 0.0f , 0.0f , 0.0f } , { 0.0f , 0.0f , 0.0f } );
}
PFX_Geometry::PFX_Geometry( std::array<float, 3> position , std::array<float, 3> normal ) {
    this->_Init( position , normal );
}
void PFX_Geometry::_Init( std::array<float, 3> position , std::array<float, 3> normal ) {
    this->_position = position;
    this->_normal = normal;
}
void PFX_Geometry::_Transform() {
}
void PFX_Geometry::AddTriangle( const PFX_Triangle &triangle ) {
    this->_triangles.push_back( triangle );
    this->_transformed_points.resize( LUT_POINT_SIZE_3 * this->_triangles.size() * 20 ); //Резервим адрес, 15 для каждого треугольника и *3 с запасом для разрезания
}
void PFX_Geometry::AddTriangle( PFX_Triangle&& triangle ) {
    this->AddTriangle( std::move( triangle ) );
}
void PFX_Geometry::SetTexture( std::string path ) {
    this->_texture.Load( path );
}
void PFX_Geometry::Translate( std::array<float, 3> position ) {
    this->_position = Vector3F_Plus( this->_position , position );
}
std::vector<float>& PFX_Geometry::GetPoints() {
    return this->_transformed_points;
}
float* PFX_Geometry::GetPointsF() {
    return this->_transformed_points.data();
}
unsigned short PFX_Geometry::TrianglesNum() {
    return this->_triangles_num;
}
unsigned char& PFX_Geometry::GetTexturePixels() {
    return *this->_texture.Pixels();
}
void PFX_Geometry::RotateY( float angle ) {
    this->_angle_h += angle * LUT_TIME_DELTA;
    while ( this->_angle_h > LUT_PI )  this->_angle_h -= LUT_PI_DOUBLE;
    while ( this->_angle_h < -LUT_PI ) this->_angle_h += LUT_PI_DOUBLE;
    this->UpdateNormal();
}
void PFX_Geometry::RotateX( float angle ) {
    this->_angle_v += angle * LUT_TIME_DELTA;
    while ( this->_angle_v > LUT_PI )  this->_angle_v -= LUT_PI_DOUBLE;
    while ( this->_angle_v < -LUT_PI ) this->_angle_v += LUT_PI_DOUBLE;
    this->UpdateNormal();
}
void PFX_Geometry::UpdateNormal() {
    this->_normal[ 0 ] = std::cos( this->_angle_h ) * std::cos( this->_angle_v );
    this->_normal[ 1 ] = std::sin( this->_angle_v ) ;
    this->_normal[ 2 ] = std::sin( this->_angle_h ) * std::cos( this->_angle_v );
}
void PFX_Geometry::Update() {
    PFX_Context& context = PFX_Context::GetInstance();
    PFX_Camera& camera = context.Camera();
    float* camera_position = camera.position.data();
    float* camera_normal = camera.player_normal.data();
    //Треугольники
    PFX_Triangle* tris = this->_triangles.data();
    const unsigned int tris_count = this->_triangles.size();
    this->_triangles_num = 0;
    //Позиция геометрии
    const float px = this->_position[ 0 ];
    const float py = this->_position[ 1 ];
    const float pz = this->_position[ 2 ];

    const float nx = this->_normal[ 0 ];
    const float ny = this->_normal[ 1 ];
    const float nz = this->_normal[ 2 ];

    float len = std::sqrt( nz * nz + nx * nx );

    const float rx = nz / len;
    const float ry = 0.0f;
    const float rz = -nx / len;

    const float ux = ry * nz - rz * ny;
    const float uy = rz * nx - rx * nz;
    const float uz = rx * ny - ry * nx;

    const float cam_x = px - camera_position[ 0 ];
    const float cam_y = py - camera.camera_y;
    const float cam_z = pz - camera_position[ 2 ];
    const float dot_g = camera_normal[ 0 ] * cam_x + camera_normal[ 2 ] * cam_z;
    if( dot_g <= 0 ) return;
    //Преобразованные точки
    float* out = this->_transformed_points.data();
    // Отсекаем по каждой плоскости
    PFX_Plane* planes[] = { &camera.plane_r , &camera.plane_l , &camera.plane_t , &camera.plane_b };
    //Буферы для хранения данных обработки треугольников
    //tri_1_2 - нужен для хранения данных двух треугольников при рассечении
    //buff_1 и buff_2 нужны для хранения промежуточных данных рассечения
    float tri_1_2_buff[ 36 ];
    float tri_buff_1[ 360 ];
    float tri_buff_2[ 360 ];
    //Пишем точки треугольника в буфер геометрии
    for( unsigned int t = 0; t < tris_count; t++ ) {
        PFX_Triangle& tri = tris[ t ];
        float* in = tri.points.data(); //Точки треугольника
        const float* tn = tri.normal.data(); //Нормаль треугольника
        //Преобразуем нормаль треугольника в нормаль геометрии
        const float  tn_x = tn[ 0 ] * rx + tn[ 1 ] * ux + tn[ 2 ] * nx;
        const float  tn_y = tn[ 0 ] * ry + tn[ 1 ] * uy + tn[ 2 ] * ny;
        const float  tn_z = tn[ 0 ] * rz + tn[ 1 ] * uz + tn[ 2 ] * nz;
        const float dot = tn_x * cam_x + tn_y * cam_y + tn_z * cam_z;
        if( dot <= 0 ) continue;
        //Мировое пространство
        #pragma gcc unroll 3
        for( int o = 0; o < LUT_POINT_SIZE_3; o += LUT_POINT_SIZE ) {
            float* point_out = out + o;
            float* point_in = in + o;
            //Точка 1
            point_out[ 0 ] = px + point_in[ 0 ] * rx + point_in[ 1 ] * ux + point_in[ 2 ] * nx;
            point_out[ 1 ] = py + point_in[ 0 ] * ry + point_in[ 1 ] * uy + point_in[ 2 ] * ny;
            point_out[ 2 ] = pz + point_in[ 0 ] * rz + point_in[ 1 ] * uz + point_in[ 2 ] * nz;
            point_out[ 3 ] = point_in[ 3 ];
            point_out[ 4 ] = point_in[ 4 ];
            point_out[ 5 ] = std::min( 1.0f - dot / LUT_PROJECTION_DISTANCE_FAR , 1.0f );
        }
        //Цикл разрезания треугольников
        uint_fast8_t t_copy = 0; //Количество скопированных треугольников
        uint_fast8_t t_cycle = PFX_Triangle_Clipper::Clip( camera.plane_c , out , tri_buff_2 );
        for( int p = 0; p < 4; p++ ) {
            t_copy = 0;
            std::copy_n( tri_buff_2 , LUT_POINT_SIZE_3 * t_cycle , tri_buff_1 );
            while( t_cycle > 0 ) {
                t_cycle--;
                uint_fast8_t t_plus = PFX_Triangle_Clipper::Clip( *planes[ p ] , tri_buff_1 + t_cycle * LUT_POINT_SIZE_3 , tri_1_2_buff , tri_1_2_buff + LUT_POINT_SIZE_3 );
                for( uint_fast8_t p = 0; p < t_plus; p++ ) {
                    std::copy_n( tri_1_2_buff + p *  LUT_POINT_SIZE_3 , LUT_POINT_SIZE_3 , tri_buff_2 + t_copy * LUT_POINT_SIZE_3 );
                    t_copy++;
                }
            }
            t_cycle = t_copy;
        }
        //Копируем в буффер рассеченный треугольник
        std::copy_n( tri_buff_2 , LUT_POINT_SIZE_3 * t_copy , out );
        //Шагаем к следующему треугольнику геометрии
        out += LUT_POINT_SIZE_3 * t_copy;
        this->_triangles_num += t_copy;
    }
}
PFX_Geometry::~PFX_Geometry() {

}
