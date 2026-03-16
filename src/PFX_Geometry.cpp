#include "PFX_Geometry.h"
#include <cmath>
#include <limits>
#include <core\PFX_Context.h>
#include <core\PFX_Lut.h>
#include <core\PFX_Vector.h>
#include <core\PFX_Angles.h>
#include <iostream>

PFX_Geometry::PFX_Geometry() {
    this->_Init( { 0.0f , 0.0f , 0.0f } , { 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f , 0.0f } );
}
PFX_Geometry::PFX_Geometry( std::array<float, 3> position , std::array<float, 9> normal ) {
    this->_Init( position , normal );
}
void PFX_Geometry::_Init( std::array<float, 3> position , std::array<float, 9> normal ) {
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
void PFX_Geometry::CreateCollisionBoxFromPoints() {
    float x_min = std::numeric_limits<float>::max();
    float y_min = std::numeric_limits<float>::max();
    float z_min = std::numeric_limits<float>::max();
    float x_max = -std::numeric_limits<float>::max();
    float y_max = -std::numeric_limits<float>::max();
    float z_max = -std::numeric_limits<float>::max();

    for ( auto &triangle : this->_triangles ) {
        float* points = triangle.points.data();
        for( int p = 0; p < LUT_POINT_SIZE_3; p += LUT_POINT_SIZE ) {
            float* point = points + p;
            float x = point[ 0 ];
            float y = point[ 1 ];
            float z = point[ 2 ];
            if ( x < x_min ) x_min = x;
            if ( y < y_min ) y_min = y;
            if ( z < z_min ) z_min = z;
            if ( x > x_max ) x_max = x;
            if ( y > y_max ) y_max = y;
            if ( z > z_max ) z_max = z;
        }
    }
    this->collision_box.position = { this->_position[ 0 ] + x_min , this->_position[ 1 ] + y_min , this->_position[ 2 ] + z_min };
    this->collision_box.heights = { x_max - x_min , y_max - y_min , z_max - z_min };
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
void PFX_Geometry::RotateX( float angle ) {
    this->_yaw += angle * LUT_TIME_DELTA;
    while ( this->_yaw > LUT_PI )  this->_yaw -= LUT_PI_DOUBLE;
    while ( this->_yaw < -LUT_PI ) this->_yaw += LUT_PI_DOUBLE;
}
void PFX_Geometry::RotateY( float angle ) {
    this->_pitch += angle * LUT_TIME_DELTA;
    while ( this->_pitch > LUT_PI )  this->_pitch -= LUT_PI_DOUBLE;
    while ( this->_pitch < -LUT_PI ) this->_pitch += LUT_PI_DOUBLE;
}
void PFX_Geometry::RotateZ( float angle ) {
    this->_roll += angle * LUT_TIME_DELTA;
    while ( this->_roll > LUT_PI )  this->_roll -= LUT_PI_DOUBLE;
    while ( this->_roll < -LUT_PI ) this->_roll += LUT_PI_DOUBLE;
}
void PFX_Geometry::UpdateNormal() {
    this->_quternion = EulerToQuaternion( this->_yaw , this->_pitch , this->_roll );
    const float* q_data = this->_quternion.data();
    this->_normal = QuaternionToBasis( q_data );
}
//Collision_Box& PFX_Geometry::GetCollisionBox() {
//    return this->_collision_box;
//}
void PFX_Geometry::Transform() {
    //Треугольники
    PFX_Triangle* tris = this->_triangles.data();
    const unsigned int tris_count = this->_triangles.size();
    this->_triangles_num = 0;
    //Позиция геометрии
    const float px = this->_position[ 0 ];
    const float py = this->_position[ 1 ];
    const float pz = this->_position[ 2 ];

    float* normal = this->_normal.data();

    const float nx = normal[ 0 ];
    const float ny = normal[ 1 ];
    const float nz = normal[ 2 ];

    const float rx = normal[ 3 ];
    const float ry = normal[ 4 ];
    const float rz = normal[ 5 ];

    const float ux = normal[ 6 ];
    const float uy = normal[ 7 ];
    const float uz = normal[ 8 ];
    //Пишем точки треугольника в буфер геометрии
    for( unsigned int t = 0; t < tris_count; t++ ) {
        PFX_Triangle& tri = tris[ t ];
        float* in = tri.points.data(); //Точки треугольника
        float* out = tri.points_transformed.data();

        const float* tn = tri.normal.data(); //Нормаль треугольника
        float* tn_t = tri.normal_transformed.data();

        tn_t[ 0 ] = tn[ 0 ] * rx + tn[ 1 ] * ux + tn[ 2 ] * nx;
        tn_t[ 1 ] = tn[ 0 ] * ry + tn[ 1 ] * uy + tn[ 2 ] * ny;
        tn_t[ 2 ] = tn[ 0 ] * rz + tn[ 1 ] * uz + tn[ 2 ] * nz;

        for( int o = 0; o < LUT_POINT_SIZE_3; o += LUT_POINT_SIZE ) {
            float* point_out = out + o;
            float* point_in = in + o;
            //Точка 1
            point_out[ 0 ] = px + point_in[ 0 ] * rx + point_in[ 1 ] * ux + point_in[ 2 ] * nx;
            point_out[ 1 ] = py + point_in[ 0 ] * ry + point_in[ 1 ] * uy + point_in[ 2 ] * ny;
            point_out[ 2 ] = pz + point_in[ 0 ] * rz + point_in[ 1 ] * uz + point_in[ 2 ] * nz;
            point_out[ 3 ] = point_in[ 3 ];
            point_out[ 4 ] = point_in[ 4 ];
            point_out[ 5 ] = 1.0f;
        }
    }
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

    float* normal = this->_normal.data();

    const float nx = normal[ 0 ];
    const float ny = normal[ 1 ];
    const float nz = normal[ 2 ];

    const float rx = normal[ 3 ];
    const float ry = normal[ 4 ];
    const float rz = normal[ 5 ];

    const float ux = normal[ 6 ];
    const float uy = normal[ 7 ];
    const float uz = normal[ 8 ];

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
        const float point_light = std::min( 1.0f - dot / LUT_PROJECTION_DISTANCE_FAR , 1.0f );
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
            point_out[ 5 ] = point_light;
        }
        //Цикл разрезания треугольников
        uint_fast8_t t_copy = 0; //Количество скопированных треугольников
        uint_fast8_t t_cycle = PFX_Triangle_Clipper::Clip( camera.plane_c , out , tri_buff_2 );
        #pragma gcc unroll 4
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
void PFX_Geometry::UpdateStatic() {
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
        float* in = tri.points_transformed.data(); //Точки треугольника
        const float* tn = tri.normal_transformed.data(); //Нормаль треугольника
        const float dot = tn[ 0 ] * cam_x + tn[ 1 ] * cam_y + tn[ 2 ] * cam_z;
        if( dot <= 0 ) continue;
        const float point_light = std::min( 1.0f - dot / LUT_PROJECTION_DISTANCE_FAR , 1.0f );
        //std::copy_n( in , LUT_POINT_SIZE_3 , out );
        in[ LUT_POINT_SIZE - 1 ] = point_light;
        in[ LUT_POINT_SIZE_2 - 1 ] = point_light;
        in[ LUT_POINT_SIZE_3 - 1 ] = point_light;
        //Цикл разрезания треугольников
        uint_fast8_t t_copy = 0; //Количество скопированных треугольников
        uint_fast8_t t_cycle = PFX_Triangle_Clipper::Clip( camera.plane_c , in , tri_buff_2 );
        #pragma gcc unroll 4
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
