#include "PFX_Render.h"
#include "PFX_Texture.h"
#include <iostream>

inline bool isValidFloat(float x) {
    return !std::isnan(x) && !std::isinf(x) && std::abs(x) < 1e6f;
}

PFX_Render::PFX_Render() {

}
void PFX_Render::Init( GLFWwindow* window ) {
    int width, height;
    glfwGetFramebufferSize( window , &width , &height );
    //Окно
    this->_window = window;

    glEnable( GL_TEXTURE_2D );
//    glEnable( GL_BLEND );
//    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

    uint32_t buff_size = LUT_RENDER_SCREEN_WIDTH * LUT_RENDER_SCREEN_HEIGHT * 4;
    std::cout << buff_size << "\n";
    //Буфер кадра
    this->_frame_pixels = std::make_unique<unsigned char[]>( buff_size );
    this->_frame_z.resize( buff_size );
    //this->SkyBox();
//    glEnable( GL_BLEND );
//    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );
    // Создаём текстуру
    GLuint textureId;
    glGenTextures( 1 , &textureId );
    glBindTexture( GL_TEXTURE_2D, textureId );
    this->_frame_texture = textureId;
    if ( !glIsTexture( this->_frame_texture ) ) {
        printf("ERROR: Not a valid texture object!\n");
    }
    // Настраиваем параметры текстуры
    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_NEAREST );
    glTexParameterf( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_CLAMP );
    // Выделяем память под текстуру (пустую)
    glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA , LUT_RENDER_SCREEN_WIDTH , LUT_RENDER_SCREEN_HEIGHT , 0 , GL_RGBA , GL_UNSIGNED_BYTE , NULL );

    //Тестовая текстура
    this->_texture.Load( "images/textures/cube.jpg" );
    //Низ
    PFX_Triangle tri1;
    tri1.SetPoint( 0 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri1.SetPoint( 1 , 0.5f , -0.5f , -0.5f , 1.0f , 0.0f );
    tri1.SetPoint( 2 , 0.5f , -0.5f , 0.5f , 1.0f , 1.0f );
    tri1.normal = { 0.0f , 1.0f , 0.0f };
    PFX_Triangle tri2;
    tri2.SetPoint( 0 , 0.5f , -0.5f , 0.5f , 1.0f , 1.0f );
    tri2.SetPoint( 1 , -0.5f , -0.5f , 0.5f , 0.0f , 1.0f );
    tri2.SetPoint( 2 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri2.normal = { 0.0f , 1.0f , 0.0f };
    //Верх
    PFX_Triangle tri3;
    tri3.SetPoint( 0 , -0.5f , 0.5f , -0.5f , 0.0f , 0.0f );
    tri3.SetPoint( 1 , 0.5f , 0.5f , -0.5f , 1.0f , 0.0f );
    tri3.SetPoint( 2 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri3.normal = { 0.0f , -1.0f , 0.0f };
    PFX_Triangle tri4;
    tri4.SetPoint( 0 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri4.SetPoint( 1 , -0.5f , 0.5f , 0.5f , 0.0f , 1.0f );
    tri4.SetPoint( 2 , -0.5f , 0.5f , -0.5f , 0.0f , 0.0f );
    tri4.normal = { 0.0f , -1.0f , 0.0f };
    //Дальняя часть
    PFX_Triangle tri5;
    tri5.SetPoint( 0 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri5.SetPoint( 1 , 0.5f , -0.5f , -0.5f , 1.0f , 0.0f );
    tri5.SetPoint( 2 , 0.5f , 0.5f , -0.5f , 1.0f , 1.0f );
    tri5.normal = { 0.0f , 0.0f , 1.0f };
    PFX_Triangle tri6;
    tri6.SetPoint( 0 , 0.5f , 0.5f , -0.5f , 1.0f , 1.0f );
    tri6.SetPoint( 1 , -0.5f , 0.5f , -0.5f , 0.0f , 1.0f );
    tri6.SetPoint( 2 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri6.normal = { 0.0f , 0.0f , 1.0f };
    //Ближняя часть
    PFX_Triangle tri7;
    tri7.SetPoint( 0 , -0.5f , -0.5f , 0.5f , 0.0f , 0.0f );
    tri7.SetPoint( 1 , 0.5f , -0.5f , 0.5f , 1.0f , 0.0f );
    tri7.SetPoint( 2 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri7.normal = { 0.0f , 0.0f , -1.0f };
    PFX_Triangle tri8;
    tri8.SetPoint( 0 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri8.SetPoint( 1 , -0.5f , 0.5f , 0.5f , 0.0f , 1.0f );
    tri8.SetPoint( 2 , -0.5f , -0.5f , 0.5f , 0.0f , 0.0f );
    tri8.normal = { 0.0f , 0.0f , -1.0f };
    //Правая часть
    PFX_Triangle tri9;
    tri9.SetPoint( 0 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri9.SetPoint( 1 , -0.5f , 0.5f , -0.5f , 1.0f , 0.0f );
    tri9.SetPoint( 2 , -0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri9.normal = { 1.0f , 0.0f , 0.0f };
    PFX_Triangle tri10;
    tri10.SetPoint( 0 , -0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri10.SetPoint( 1 , -0.5f , -0.5f , 0.5f , 0.0f , 1.0f );
    tri10.SetPoint( 2 , -0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri10.normal = { 1.0f , 0.0f , 0.0f };
    //Левая часть
    PFX_Triangle tri11;
    tri11.SetPoint( 0 , 0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri11.SetPoint( 1 , 0.5f , 0.5f , -0.5f , 1.0f , 0.0f );
    tri11.SetPoint( 2 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri11.normal = { -1.0f , 0.0f , 0.0f };
    PFX_Triangle tri12;
    tri12.SetPoint( 0 , 0.5f , 0.5f , 0.5f , 1.0f , 1.0f );
    tri12.SetPoint( 1 , 0.5f , -0.5f , 0.5f , 0.0f , 1.0f );
    tri12.SetPoint( 2 , 0.5f , -0.5f , -0.5f , 0.0f , 0.0f );
    tri12.normal = { -1.0f , 0.0f , 0.0f };

    this->_geometry.AddTriangle( tri1 );
    this->_geometry.AddTriangle( tri2 );
    this->_geometry.AddTriangle( tri3 );
    this->_geometry.AddTriangle( tri4 );
    this->_geometry.AddTriangle( tri5 );
    this->_geometry.AddTriangle( tri6 );
    this->_geometry.AddTriangle( tri7 );
    this->_geometry.AddTriangle( tri8 );
    this->_geometry.AddTriangle( tri9 );
    this->_geometry.AddTriangle( tri10 );
    this->_geometry.AddTriangle( tri11 );
    this->_geometry.AddTriangle( tri12 );
    this->_geometry.SetTexture( "images/textures/cube.jpg" );
    this->_geometry.Translate( { 2.0f , 0.5f , 2.0f } );
    this->_geometry.Update();
}
PFX_Render::~PFX_Render()
{
 //   delete this->_texture;
}
void PFX_Render::SkyBox() {
    unsigned char* pixels = this->_frame_pixels.get();
    for( uint_fast32_t b = 0; b < LUT_RENDER_BUFF_MAX_INDEX; b +=4 ) {
        pixels[ 0 ] = 0;
        pixels[ 1 ] = 255;
        pixels[ 2 ] = 255;
        pixels[ 3 ] = 1;
        pixels += 4;
    }
//    for( uint_fast16_t x = 0; x < LUT_RENDER_SCREEN_WIDTH; x++ ) {
//        for( uint_fast16_t y = 0; y < LUT_RENDER_SCREEN_HEIGHT; y++ ) {
//            uint_fast32_t key = LUT_RENDER_BUFF_Y[ y ] + LUT_RENDER_BUFF_X[ x ];
//            pixels[ key ] = 0;
//            pixels[ key + 1 ] = 255;
//            pixels[ key + 2 ] = 255;
//            pixels[ key + 3 ] = 1;
//        }
//    }
}
void PFX_Render::Update() {
    std::fill_n( this->_frame_z.begin() , this->_frame_z.size() , 0 );
    this->SkyBox();

    this->_geometry.RotateX( 1.00f );
    this->_geometry.Update();
    this->Geometry( this->_geometry );

}
void PFX_Render::Geometry( PFX_Geometry &geometry ) {
    //geometry.Update();
    float* points = geometry.GetPointsF();
    unsigned short num = geometry.TrianglesNum();
    //Цикл
    unsigned char& pixels = geometry.GetTexturePixels();
    for( unsigned int t = 0; t < num; t++ ) {
        //Проекция всех 3 точек
        const auto projection = this->_projection->ProjectTriangle( points , *this->_camera );
        //Копируем в буффер
        const float* projection_data = projection.data();
        //Пишем пиксели в буфер
        this->ScanlineTriangle( projection_data , projection_data + LUT_POINT_SIZE , projection_data + LUT_POINT_SIZE_2 , &pixels );
        //Итерация цикла
        points += LUT_POINT_SIZE_3; //Увеличиваем каждый цикл - 18 x y z u v координаты для 3х точек
    }
}
void PFX_Render::FillTriangle( short &y_1 , short &startY , short &endY , float &way1_x , float &way2_x ,
                              float &u1_start , float &u2_start , float &v1_start , float &v2_start , float &z1_way , float &z2_way ,
                              float &u1_way , float &u2_way , float &v1_way , float &v2_way ,
                                const float &dir1_x , const float &dir2_x , const float &step1_u , const float &step2_u , const float &step1_v , const float &step2_v ,
                                const float &z1_step , const float &z2_step , float &l1_way , float &l2_way , const float &l1_step , const float &l2_step ,
                                unsigned char* pixels , float* z_buffer , unsigned char* texture_pixels ) {

    unsigned char* pixel_pointer;
    unsigned char* texture_pointer;

    for ( short y = startY; y < endY; y++ ) {
        const int x_diff = static_cast<int>( way2_x ) - static_cast<int>( way1_x );
        short x_dist = std::abs( x_diff );
        const float t = LUT_DIST_INV[ x_dist ];
        const int x_dir = ( x_diff >= 0 ) ? 1 : -1;
        //UV
        float u1_i = u1_start + u1_way;
        float v1_i = v1_start + v1_way;
        float u2_i = u2_start + u2_way;
        float v2_i = v2_start + v2_way;
        const float u_d = ( u2_i - u1_i );
        const float v_d = ( v2_i - v1_i );
        const float u_s = u_d * t;
        const float v_s = v_d * t;
        const float z_step = ( z2_way - z1_way ) * t;
        //Свет вершины
        float light_step = ( l2_way - l1_way ) * t;
        //Вводные данные для закраски линии экрана
        float u_way  = u1_i;
        float v_way  = v1_i;
        float z_way  = z1_way;
        float l_way  = l1_way;

        const int x_i = static_cast<int>( way1_x );
        const int y_i = y_1 + y;

        //Часть для закраски разрывов полигонов
        //Отсекаем края по x
        int x_offset = 0;
        int x_dist_offset = 0;
        //Если старт линии находится за экраном
        if( way1_x < 0 || way1_x >= LUT_RENDER_SCREEN_WIDTH ) {
            x_offset = std::abs( way1_x ) * ( way1_x < 0 ) + ( way1_x - LUT_RENDER_SCREEN_WIDTH ) * ( way1_x >= LUT_RENDER_SCREEN_WIDTH );
            float x_off_float = static_cast<float>( x_offset );
            //Сдвигаем координаты на начало экрана
            u_way += u_s * x_off_float;
            v_way += v_s * x_off_float;
            z_way += z_step * x_off_float;
            l_way += light_step * x_off_float;
        }
        //Если линия заканчивается за границами экрана
        if( way2_x >= LUT_RENDER_SCREEN_WIDTH || way2_x < 0  ) {
            x_dist_offset = std::abs( way2_x ) * ( way2_x < 0 ) + ( way2_x - LUT_RENDER_SCREEN_WIDTH ) * ( way2_x >= LUT_RENDER_SCREEN_WIDTH );
        }
        //Считаем x на экране, тут нужно отсечение, потому что + 0.5f может уходить за экран
        int x = std::clamp( x_i - 1 * x_dir , 0 , LUT_RENDER_SCREEN_WIDTH - 1 );
        int x_2 = std::clamp( static_cast<int>( way2_x ) + 1 * x_dir , 0 , LUT_RENDER_SCREEN_WIDTH - 1 );
        //Получаем пиексель и адрес пикселя экранного буфера
        int pixel_i = this->GetTexturePixelIndexByUVZ( u1_i , v1_i , z1_way );
        int pixel_i_2 = this->GetTexturePixelIndexByUVZ( u2_i , v2_i , z2_way );
        int buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
        int buffer_2 = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x_2 ];
        //Пишем пиксель
        if( z_buffer[ buffer ] < z_way ) {
            pixel_pointer = pixels + buffer;
            texture_pointer = texture_pixels + pixel_i;
            pixel_pointer[ 0 ] = texture_pointer[ 0 ] * l_way;
            pixel_pointer[ 1 ] = texture_pointer[ 1 ] * l_way;
            pixel_pointer[ 2 ] = texture_pointer[ 2 ] * l_way;
            pixel_pointer[ 3 ] = 255;
            //std::copy_n( texture_pointer , 4 , pixel_pointer );
            z_buffer[ buffer ] = z_way;
        }
        if( z_buffer[ buffer_2 ] < z2_way ) {
            pixel_pointer = pixels + buffer_2;
            texture_pointer = texture_pixels + pixel_i_2;
            pixel_pointer[ 0 ] = texture_pointer[ 0 ] * l_way;
            pixel_pointer[ 1 ] = texture_pointer[ 1 ] * l_way;
            pixel_pointer[ 2 ] = texture_pointer[ 2 ] * l_way;
            pixel_pointer[ 3 ] = 255;
            //std::copy_n( texture_pointer , 4 , pixel_pointer );
            z_buffer[ buffer_2 ] = z2_way;
        }
        //Основной цикл
        short xd = x_offset;
        for ( ; xd <= x_dist - x_dist_offset - 2; xd += 2 ) {
            x = x_i + xd * x_dir;
            buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
            buffer_2 = buffer + 4 * x_dir; //Для отрисовки второго пикселя
            bool buff1_sw = ( z_buffer[ buffer ] < z_way );
            bool buff2_sw = ( z_buffer[ buffer_2 ] < z_way );
            //Если перекрытие, идём дальше
            if( !buff1_sw && !buff2_sw ) {
                #pragma gcc unroll 2
                for( int i = 0; i < 2; i++ ) {
                    u_way += u_s;
                    v_way += v_s;
                    z_way += z_step;
                    l_way += light_step;
                }
                continue;
            }
            //Получаем коордианты пикселя по uv
            pixel_i = this->GetTexturePixelIndexByUVZ( u_way , v_way , z_way );
            //Накладываем текстуру
            texture_pointer = texture_pixels + pixel_i;
            if( buff1_sw ) {
                //std::copy_n( texture_pointer , 4 , pixels + buffer );
                pixel_pointer = pixels + buffer;
                pixel_pointer[ 0 ] = texture_pointer[ 0 ] * l_way;
                pixel_pointer[ 1 ] = texture_pointer[ 1 ] * l_way;
                pixel_pointer[ 2 ] = texture_pointer[ 2 ] * l_way;
                pixel_pointer[ 3 ] = 255;

                z_buffer[ buffer ] = z_way;
            }
            if( buff2_sw ) {
                //std::copy_n( texture_pointer , 4 , pixels + buffer_2 );
                pixel_pointer = pixels + buffer_2;
                pixel_pointer[ 0 ] = texture_pointer[ 0 ] * l_way;
                pixel_pointer[ 1 ] = texture_pointer[ 1 ] * l_way;
                pixel_pointer[ 2 ] = texture_pointer[ 2 ] * l_way;
                pixel_pointer[ 3 ] = 255;
                z_buffer[ buffer_2 ] = z_way;
            }
            //Шаг сканлайна по x
            #pragma gcc unroll 2
            for( int i = 0; i < 2; i++ ) {
                u_way += u_s;
                v_way += v_s;
                z_way += z_step;
                l_way += light_step;
            }
        }
        for( ; xd <= x_dist - x_dist_offset; xd++ ) {
            x = x_i + xd * x_dir;
            buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
            //Если перекрытие, идём дальше
            if( z_buffer[ buffer ] > z_way ) {
                u_way += u_s;
                v_way += v_s;
                z_way += z_step;
                l_way += light_step;
                continue;
            }
            //Получаем коордианты пикселя по uv
            pixel_i = this->GetTexturePixelIndexByUVZ( u_way , v_way , z_way );
            //Накладываем текстуру
            texture_pointer = texture_pixels + pixel_i;
            //std::copy_n( texture_pointer , 4 , pixels + buffer );
            pixel_pointer = pixels + buffer;
            pixel_pointer[ 0 ] = texture_pointer[ 0 ] * l_way;
            pixel_pointer[ 1 ] = texture_pointer[ 1 ] * l_way;
            pixel_pointer[ 2 ] = texture_pointer[ 2 ] * l_way;
            pixel_pointer[ 3 ] = 255;
            z_buffer[ buffer ] = z_way;
            //Шаг сканлайна по x
            u_way += u_s;
            v_way += v_s;
            z_way += z_step;
            l_way += light_step;
        }
        //Шаг сканлайна по y
        way1_x += dir1_x;
        way2_x += dir2_x;
        u1_way += step1_u;
        v1_way += step1_v;
        u2_way += step2_u;
        v2_way += step2_v;
        z1_way += z1_step;
        z2_way += z2_step;
        l1_way += l1_step;
        l2_way += l2_step;
    }
}
//Возвращает координаты пикселя на текстуре по координатам с параметром глубины
int PFX_Render::GetTexturePixelIndexByUVZ( float &u , float &v , float &z ) {
    int z_way_i = std::abs( static_cast<int>( z * 1000 ) );
    float inv_z = LUT_RENDER_TEXTURE_Z_INV[ z_way_i ];
    int uz = static_cast<int>( std::abs( u * inv_z ) );
    int vz = static_cast<int>( std::abs( v * inv_z ) );
    int px = LUT_RENDER_TEXTURE_DIVISION[ uz ];
    int py = LUT_RENDER_TEXTURE_DIVISION[ vz ];
    return LUT_RENDER_TEXTURE_Y[ py ] + LUT_RENDER_TEXTURE_X[ px ];
}
//unsigned short - вместо uint16_t и unsigned char вместо uint8_t, дают выше производительность
void PFX_Render::ScanlineTriangle( const float* projected1 , const float* projected2 , const float* projected3 , unsigned char* texture_pixels ) {

    if ( projected1[ 1 ] > projected2[ 1 ] ) {
        std::swap( projected1 , projected2 );
    }
    if ( projected1[ 1 ] > projected3[ 1 ] ) {
        std::swap( projected1 , projected3 );
    }
    if ( projected2[ 1 ] > projected3[ 1 ] ){
        std::swap( projected2 , projected3 );
    }

    short y_1 = static_cast<int>( projected1[ 1 ] );
    short y_2 = static_cast<int>( projected2[ 1 ] );
    short y_3 = static_cast<int>( projected3[ 1 ] );

    short x_1 = static_cast<int>( projected1[ 0 ] );
    short x_2 = static_cast<int>( projected2[ 0 ] );
    short x_3 = static_cast<int>( projected3[ 0 ] );

    const float z_1 = projected1[ 2 ];
    const float z_2 = projected2[ 2 ];
    const float z_3 = projected3[ 2 ];

    const float w1 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>( z_1 * 1000 ) ];
    const float w2 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>( z_2 * 1000 ) ];
    const float w3 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>( z_3 * 1000 ) ];

    const float u1 = projected1[ 3 ] * w1 , v1 = projected1[ 4 ] * w1;
    const float u2 = projected2[ 3 ] * w2 , v2 = projected2[ 4 ] * w2;
    const float u3 = projected3[ 3 ] * w3 , v3 = projected3[ 4 ] * w3;
    //Освещение вершины
    const float l1 = projected1[ 5 ];
    const float l2 = projected2[ 5 ];
    const float l3 = projected3[ 5 ];

    const short diff1_y = y_2 - y_1;
    const short diff2_y = y_3 - y_1;
    const short diff3_y = y_3 - y_2;

    short startY = ( y_1 < 0 ) ? std::abs( y_1 ) : 0;
    short endY   = ( y_1 + diff1_y > LUT_RENDER_SCREEN_HEIGHT ) ? ( ( y_1 + diff1_y ) - LUT_RENDER_SCREEN_HEIGHT ) : 0;

    const float dis1_inv = LUT_DIST_INV[ diff1_y ];
    const float dis2_inv = LUT_DIST_INV[ diff2_y ];
    const float dis3_inv = LUT_DIST_INV[ diff3_y ];

    const float dir1_x  = ( x_2 - x_1 ) * dis1_inv;
    const float dir2_x  = ( x_3 - x_1 ) * dis2_inv;
    const float dir3_x  = ( x_3 - x_2 ) * dis3_inv;

    const float u_diff1 = u2 - u1;
    const float u_diff2 = u3 - u1;
    const float u_diff3 = u3 - u2;

    const float v_diff1 = v2 - v1;
    const float v_diff2 = v3 - v1;
    const float v_diff3 = v3 - v2;

    const float step1_u = u_diff1 * dis1_inv;
    const float step2_u = u_diff2 * dis2_inv;
    const float step3_u = u_diff3 * dis3_inv;

    const float step1_v = v_diff1 * dis1_inv;
    const float step2_v = v_diff2 * dis2_inv;
    const float step3_v = v_diff3 * dis3_inv;

    const float z1_step  = ( w2 - w1 ) * dis1_inv;
    const float z2_step  = ( w3 - w1 ) * dis2_inv;
    const float z3_step  = ( w3 - w2 ) * dis3_inv;

    const float l1_step = ( l2 - l1 ) * dis1_inv;
    const float l2_step = ( l3 - l1 ) * dis2_inv;
    const float l3_step = ( l3 - l2 ) * dis3_inv;

    float u1_start = u1;
    float v1_start = v1;
    float u2_start = u1;
    float v2_start = v1;

    float l1_start = l1;
    float l2_start = l1;

    float startYF = static_cast<float>( startY );

    float u1_way = step1_u * startYF;
    float v1_way = step1_v * startYF;
    float u2_way = step2_u * startYF;
    float v2_way = step2_v * startYF;

    float z1_way = w1 + z1_step * startYF;
    float z2_way = w1 + z2_step * startYF;

    float way1_x = x_1 + dir1_x * startYF;
    float way2_x = x_1 + dir2_x * startYF;

    unsigned char* pixels = this->_frame_pixels.get();
    float* z_buffer = this->_frame_z.data();
    unsigned char* pixel_pointer;
    unsigned char* texture_pointer;

    short t_y = diff1_y - endY;

    this->FillTriangle( y_1 , startY , t_y , way1_x , way2_x , u1_start , u2_start , v1_start ,
                       v2_start , z1_way , z2_way , u1_way , u2_way , v1_way , v2_way ,
                       dir1_x , dir2_x , step1_u , step2_u , step1_v , step2_v , z1_step , z2_step ,
                       l1_start , l2_start , l1_step , l2_step ,
                       pixels , z_buffer , texture_pixels );

    startY = ( y_2 < 0 ) ? std::abs( y_2 ) : 0;
    endY = ( y_3 >= LUT_RENDER_SCREEN_HEIGHT ) ? ( y_3 - LUT_RENDER_SCREEN_HEIGHT ) : 0;

    startYF = static_cast<float>( startY );

    way1_x = x_2 + ( dir3_x * startYF );
    u1_way = step3_u * startYF;
    v1_way = step3_v * startYF;
    z1_way = w2 + z3_step * startYF;

    u1_start = u2;
    v1_start = v2;

    l1_start = l2 + l3_step * startYF;

    t_y = diff3_y - endY;

    this->FillTriangle( y_2 , startY , t_y , way1_x , way2_x , u1_start , u2_start , v1_start ,
                       v2_start , z1_way , z2_way , u1_way , u2_way , v1_way , v2_way ,
                       dir3_x , dir2_x , step3_u , step2_u , step3_v , step2_v , z3_step , z2_step ,
                       l1_start , l2_start , l3_step , l2_step ,
                       pixels , z_buffer , texture_pixels );
}
void PFX_Render::ScanlineTriangle( std::array<float, 3> projected1 , std::array<float, 3> projected2 , std::array<float, 3> projected3 ,
                                  std::array<float, 2> uv1 , std::array<float, 2> uv2 , std::array<float, 2> uv3 , unsigned char* texture_pixels ) {
    float point1[ 5 ];
    float point2[ 5 ];
    float point3[ 5 ];

    point1[ 0 ] = projected1[ 0 ];
    point1[ 1 ] = projected1[ 1 ];
    point1[ 2 ] = projected1[ 2 ];
    point1[ 3 ] = uv1[ 0 ];
    point1[ 4 ] = uv1[ 1 ];

    point2[ 0 ] = projected2[ 0 ];
    point2[ 1 ] = projected2[ 1 ];
    point2[ 2 ] = projected2[ 2 ];
    point2[ 3 ] = uv2[ 0 ];
    point2[ 4 ] = uv2[ 1 ];

    point3[ 0 ] = projected3[ 0 ];
    point3[ 1 ] = projected3[ 1 ];
    point3[ 2 ] = projected3[ 2 ];
    point3[ 3 ] = uv3[ 0 ];
    point3[ 4 ] = uv3[ 1 ];

    this->ScanlineTriangle( point1 , point2 , point3 , texture_pixels );
}
void PFX_Render::ScanlineRectangle( std::array<float, 3> position , float width , float height ) {
    float scale = 20.0f;
    unsigned char* pixels = this->_frame_pixels.get();
    uint_fast16_t start_x = position[ 0 ] * scale;
    uint_fast16_t start_y = position[ 2 ] * scale;
    uint_fast16_t width_x = width * scale;
    uint_fast16_t width_y = height * scale;
    for( unsigned short y = start_y; y < start_y + width_y; y++ ) {
        for( unsigned short x = start_x; x < start_x + width_x; x++ ) {
            uint_fast32_t buffer = ( y * LUT_RENDER_SCREEN_WIDTH ) * 4 + x * 4;
            pixels[ buffer ] = 255;
            pixels[ buffer + 1 ] = 0;
            pixels[ buffer + 2 ] = 0;
            pixels[ buffer + 3 ] = 255;
        }
    }
}
void PFX_Render::Draw() {
    unsigned char* pixels = this->_frame_pixels.get();
    glBindTexture( GL_TEXTURE_2D , this->_frame_texture );
    glTexSubImage2D( GL_TEXTURE_2D , 0 , 0 , 0 , LUT_RENDER_SCREEN_WIDTH , LUT_RENDER_SCREEN_HEIGHT , GL_RGBA , GL_UNSIGNED_BYTE , pixels );
    glEnable( GL_TEXTURE_2D );
    glBegin( GL_QUADS );
            glTexCoord2f( 0 , 1 ); glVertex2f( -1 , -1 );
            glTexCoord2f( 1 , 1 ); glVertex2f( 1 , -1 );
            glTexCoord2f( 1 , 0 ); glVertex2f( 1 , 1 );
            glTexCoord2f( 0 , 0 ); glVertex2f( -1 , 1 );
    glEnd();
    glfwSwapBuffers( this->_window );
}
void PFX_Render::SetProjection( PFX_Projection& projection ) {
    this->_projection = &projection;
}
void PFX_Render::SetCamera( PFX_Camera& camera ) {
    this->_camera = &camera;
}

//
//
//    // Быстрая проверка bounding box
//    int min_x = std::min({(int)projected1[0], (int)projected2[0], (int)projected3[0]});
//    int max_x = std::max({(int)projected1[0], (int)projected2[0], (int)projected3[0]});
//    int min_y = std::min({(int)projected1[1], (int)projected2[1], (int)projected3[1]});
//    int max_y = std::max({(int)projected1[1], (int)projected2[1], (int)projected3[1]});
//
//    // Если bounding box полностью вне экрана - выходим
//    if ( max_x < 0 || min_x >= LUT_RENDER_SCREEN_WIDTH ||
//         max_y < 0 || min_y >= LUT_RENDER_SCREEN_HEIGHT ) {
//        return;
//    }
//
//    if ( projected1[ 1 ] > projected2[ 1 ] ) {
//        std::swap( projected1 , projected2 );
//    }
//    if ( projected1[ 1 ] > projected3[ 1 ] ) {
//        std::swap( projected1 , projected3 );
//    }
//    if ( projected2[ 1 ] > projected3[ 1 ] ){
//        std::swap( projected2 , projected3 );
//    }
//
//    short y_1 = (int)projected1[ 1 ];
//    short y_2 = (int)projected2[ 1 ];
//    short y_3 = (int)projected3[ 1 ];
//
//    int x_1 = (int)projected1[ 0 ];
//    int x_2 = (int)projected2[ 0 ];
//    int x_3 = (int)projected3[ 0 ];
//
//    const float z_1 = projected1[ 2 ];
//    const float z_2 = projected2[ 2 ];
//    const float z_3 = projected3[ 2 ];
//
//    const float w1 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>(z_1 * 1000) ];
//    const float w2 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>(z_2 * 1000) ];
//    const float w3 = LUT_PROJECTION_DIST_INV[ static_cast<unsigned short>(z_3 * 1000) ];
//
//    const float u1 = projected1[ 3 ] * w1 , v1 = projected1[ 4 ] * w1;
//    const float u2 = projected2[ 3 ] * w2 , v2 = projected2[ 4 ] * w2;
//    const float u3 = projected3[ 3 ] * w3 , v3 = projected3[ 4 ] * w3;
//
//    if( ( x_1 <= 0 && x_2 <= 0 && x_3 <= 0 ) ||
//       ( x_1 >= LUT_RENDER_SCREEN_WIDTH && x_2 >= LUT_RENDER_SCREEN_WIDTH && x_3 >= LUT_RENDER_SCREEN_WIDTH ) ||
//       ( y_1 >= LUT_RENDER_SCREEN_HEIGHT && y_2 >= LUT_RENDER_SCREEN_HEIGHT && y_3 >= LUT_RENDER_SCREEN_HEIGHT ) ) return;
//
//    const short diff1_y = y_2 - y_1;
//    const short diff2_y = y_3 - y_1;
//    const short diff3_y = y_3 - y_2;
//
//    short startY = ( y_1 < 0 ) ? std::abs( y_1 ) : 0;
//    short endY   = ( y_1 + diff1_y > LUT_RENDER_SCREEN_HEIGHT ) ? ( ( y_1 + diff1_y ) - LUT_RENDER_SCREEN_HEIGHT ) : 0;
//
//    const float dis1_inv = LUT_DIST_INV[ diff1_y ];
//    const float dis2_inv = LUT_DIST_INV[ diff2_y ];
//    const float dis3_inv = LUT_DIST_INV[ diff3_y ];
//
//    const float dir1_x  = ( projected2[ 0 ] - projected1[ 0 ] ) * dis1_inv;
//    const float dir2_x  = ( projected3[ 0 ] - projected1[ 0 ] ) * dis2_inv;
//    const float dir3_x  = ( projected3[ 0 ] - projected2[ 0 ] ) * dis3_inv;
//
//    const float u_diff1 = u2 - u1;
//    const float u_diff2 = u3 - u1;
//    const float u_diff3 = u3 - u2;
//
//    const float v_diff1 = v2 - v1;
//    const float v_diff2 = v3 - v1;
//    const float v_diff3 = v3 - v2;
//
//    const float step1_u = u_diff1 * dis1_inv;
//    const float step2_u = u_diff2 * dis2_inv;
//    const float step3_u = u_diff3 * dis3_inv;
//
//    const float step1_v = v_diff1 * dis1_inv;
//    const float step2_v = v_diff2 * dis2_inv;
//    const float step3_v = v_diff3 * dis3_inv;
//
//    const float z1_step  = ( w2 - w1 ) * dis1_inv;
//    const float z2_step  = ( w3 - w1 ) * dis2_inv;
//    const float z3_step  = ( w3 - w2 ) * dis3_inv;
//
//    float u1_start = u1;
//    float v1_start = v1;
//    float u2_start = u1;
//    float v2_start = v1;
//
//    float startYF = static_cast<float>( startY );
//
//    float u1_way = step1_u * startYF;
//    float v1_way = step1_v * startYF;
//    float u2_way = step2_u * startYF;
//    float v2_way = step2_v * startYF;
//
//    float z1_way = w1 + z1_step * startYF;
//    float z2_way = w1 + z2_step * startYF;
//
//    float way1_x = projected1[ 0 ] + ( dir1_x * startYF );
//    float way2_x = projected1[ 0 ] + ( dir2_x * startYF );
//
//    unsigned char* pixels = this->_frame_pixels.get();
//    float* z_buffer = this->_frame_z.data();
//    unsigned char* pixel_pointer;
//    unsigned char* texture_pointer;
//
//    short t_y = diff1_y - endY;
//
//    this->FillTriangle( y_1 , startY , t_y , way1_x , way2_x , u1_start , u2_start , v1_start ,
//                       v2_start , z1_way , z2_way , u1_way , u2_way , v1_way , v2_way ,
//                       dir1_x , dir2_x , step1_u , step2_u , step1_v , step2_v , z1_step , z2_step , pixels , z_buffer , texture_pixels );
////    for ( unsigned short y = startY; y < diff1_y - endY; y++ ) {
////        const int x_diff = way2_x - way1_x;
////        unsigned short x_dist = std::abs( x_diff );
////        const float t = LUT_DIST_INV[ x_dist ];
////        const int x_dir = ( x_diff >= 0 ) ? 1 : -1;
////
////        //UV
////        const float u1_i = u1_start + u1_way;
////        const float v1_i = v1_start + v1_way;
////        const float u2_i = u2_start + u2_way;
////        const float v2_i = v2_start + v2_way;
////        const float u_d = ( u2_i - u1_i );
////        const float v_d = ( v2_i - v1_i );
////        const float u_s = u_d * t;
////        const float v_s = v_d * t;
////        const float z_step = ( z2_way - z1_way ) * t;
////
////
////        float u_way  = u1_i;
////        float v_way  = v1_i;
////        float z_way  = z1_way;
////
////        const int x_i = static_cast<int>( way1_x );
////        const int y_i = y_1 + y;
////
////        //Часть для закраски разрывов полигонов
////        int x_offset = 0;
////        if( way1_x < 0 || way1_x > LUT_RENDER_SCREEN_WIDTH - 1 ) {
////            x_offset = std::abs( way1_x ) * ( way1_x < 0 ) + ( way1_x - LUT_RENDER_SCREEN_WIDTH ) * ( way1_x > LUT_RENDER_SCREEN_WIDTH - 1 );
////            float x_off_float = (float)x_offset;
////            u_way += u_s * x_off_float;
////            v_way += v_s * x_off_float;
////            z_way += z_step * x_off_float;
////        }
////        int x = way1_x + x_offset + 1 * ( -x_dir );
////
////        unsigned short z_way_i = z_way * 1000;
////        float inv_z = LUT_RENDER_TEXTURE_Z_INV[ z_way_i ]; //LUT_RENDER_TEXTURE_SIZE_F / ;
////        uint_fast8_t px = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( u_way * inv_z ) ];
////        uint_fast8_t py = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( v_way * inv_z ) ];
////
////        uint_fast32_t pixel_i = LUT_RENDER_TEXTURE_Y[ py ] + LUT_RENDER_BUFF_X[ px ];
////        uint_fast32_t buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
////
////        if( z_buffer[ buffer ] < z_way ) {
////            pixel_pointer = pixels + buffer;
////            texture_pointer = texture_pixels + pixel_i;
////            std::copy_n( texture_pointer , 4 , pixel_pointer );
////            z_buffer[ buffer ] = z_way;
////        }
////
////        //Основной цикл
////        for ( unsigned short xd = x_offset; xd <= x_dist; xd++ ) {
////            x = x_i + xd * x_dir;
////            buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
////            if( z_buffer[ buffer ] > z_way ) {
////                u_way += u_s;
////                v_way += v_s;
////                z_way += z_step;
////                continue;
////            }
////            //Текстура
////            z_way_i = z_way * 1000;
////            inv_z = LUT_RENDER_TEXTURE_Z_INV[ z_way_i ];
////
////            px = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( u_way * inv_z ) ];
////            py = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( v_way * inv_z ) ];
////
////            pixel_i = LUT_RENDER_TEXTURE_Y[ py ] + LUT_RENDER_BUFF_X[ px ];
////
////            if( buffer > LUT_RENDER_BUFF_MAX_INDEX - 1 || pixel_i > LUT_RENDER_TEXTURE_MAX_INDEX - 1 ) return;
////
////            pixel_pointer = pixels + buffer;
////            texture_pointer = texture_pixels + pixel_i;
////            std::copy_n( texture_pointer , 4 , pixel_pointer );
////            z_buffer[ buffer ] = z_way;
////
////            u_way += u_s;
////            v_way += v_s;
////            z_way += z_step;
////        }
////        way1_x += dir1_x;
////        way2_x += dir2_x;
////        u1_way += step1_u;
////        v1_way += step1_v;
////        u2_way += step2_u;
////        v2_way += step2_v;
////        z1_way += z1_step;
////        z2_way += z2_step;
////    }
//
//    startY = ( y_2 < 0 ) ? std::abs( y_2 ) : 0;
//    endY = ( y_3 >= LUT_RENDER_SCREEN_HEIGHT ) ? ( y_3 - LUT_RENDER_SCREEN_HEIGHT ) : 0;
//
//    startYF = static_cast<float>( startY );
//
//    way1_x = projected2[ 0 ] + ( dir3_x * startYF );
//    u1_way = step3_u * startYF;
//    v1_way = step3_v * startYF;
//    z1_way = w2 + z3_step * startYF;
//
//    u1_start = u2;
//    v1_start = v2;
//
//    t_y = diff3_y - endY;
//
//    this->FillTriangle( y_2 , startY , t_y , way1_x , way2_x , u1_start , u2_start , v1_start ,
//                       v2_start , z1_way , z2_way , u1_way , u2_way , v1_way , v2_way ,
//                       dir3_x , dir2_x , step3_u , step2_u , step3_v , step2_v , z3_step , z2_step , pixels , z_buffer , texture_pixels );
//
////    for ( unsigned short y = startY; y < diff3_y - endY; y++ ) {
////        const int x_diff = way2_x - way1_x;
////        unsigned short x_dist = std::abs( x_diff );
////        const float t = LUT_DIST_INV[ x_dist ];
////        const int x_dir = ( x_diff >= 0 ) ? 1 : -1;
////
////        //UV
////        const float u1_i = u1_start + u1_way;
////        const float v1_i = v1_start + v1_way;
////        const float u2_i = u2_start + u2_way;
////        const float v2_i = v2_start + v2_way;
////        const float u_d = ( u2_i - u1_i );
////        const float v_d = ( v2_i - v1_i );
////        const float u_s = u_d * t;
////        const float v_s = v_d * t;
////        const float z_step = ( z2_way - z1_way ) * t;
////
////        float u_way  = u1_i;
////        float v_way  = v1_i;
////        float z_way  = z1_way;
////        const int x_i = static_cast<int>( way1_x );
////        const int y_i = y_2 + y;
////
////
////        //Часть для закраски разрывов полигонов
////        int x_offset = 0;
////        if( way1_x < 0 || way1_x > LUT_RENDER_SCREEN_WIDTH - 1 ) {
////            x_offset = std::abs( way1_x ) * ( way1_x < 0 ) + ( way1_x - LUT_RENDER_SCREEN_WIDTH ) * ( way1_x > LUT_RENDER_SCREEN_WIDTH - 1 );
////            float x_off_float = (float)x_offset;
////            u_way += u_s * x_off_float;
////            v_way += v_s * x_off_float;
////            z_way += z_step * x_off_float;
////        }
////        int x = way1_x + x_offset + 1 * ( -x_dir );
////
////        unsigned short z_way_i = z_way * 1000;
////        float inv_z = LUT_RENDER_TEXTURE_Z_INV[ z_way_i ]; //LUT_RENDER_TEXTURE_SIZE_F / ;
////        uint_fast8_t px = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( u_way * inv_z ) ];
////        uint_fast8_t py = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( v_way * inv_z ) ];
////
////        uint_fast32_t pixel_i = LUT_RENDER_TEXTURE_Y[ py ] + LUT_RENDER_BUFF_X[ px ];
////        uint_fast32_t buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
////
////        if( z_buffer[ buffer ] < z_way ) {
////            pixel_pointer = pixels + buffer;
////            texture_pointer = texture_pixels + pixel_i;
////            std::copy_n( texture_pointer , 4 , pixel_pointer );
////            z_buffer[ buffer ] = z_way;
////        }
////
////        for ( unsigned short xd = x_offset; xd <= x_dist; xd++ ) {
////            x = x_i + xd * x_dir;
////            buffer = LUT_RENDER_BUFF_Y[ y_i ] + LUT_RENDER_BUFF_X[ x ];
////            if( z_buffer[ buffer ] > z_way ) {
////                u_way += u_s;
////                v_way += v_s;
////                z_way += z_step;
////                continue;
////            }
////            //Текстура
////            z_way_i = z_way * 1000;
////            //z_way_i = ( z_way_i > 9999 ) ? 9999 : z_way_i;
////
////            inv_z = LUT_RENDER_TEXTURE_Z_INV[ z_way_i ]; //LUT_RENDER_TEXTURE_SIZE_F / ;
////           // if( !isValidFloat( u_way * inv_z ) ) std::cout << "t2 u_way: " << u_way * inv_z << "\n";
////           // if( !isValidFloat( v_way * inv_z ) ) std::cout << "t2 v_way: " << v_way * inv_z << "\n";
////            px = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( u_way * inv_z ) ];
////            py = LUT_RENDER_TEXTURE_DIVISION[ static_cast<uint_fast8_t>( v_way * inv_z ) ];
////
////            pixel_i = LUT_RENDER_TEXTURE_Y[ py ] + LUT_RENDER_BUFF_X[ px ];
////            //if( !isValidFloat( z_way ) ) std::cout << "t2 z_way: " << z_way << "\n";
////            //if( !isValidFloat( inv_z ) ) std::cout << "t2 inv_z: " << inv_z << "\n";
////            //if( buffer > LUT_RENDER_BUFF_MAX_INDEX - 1 || pixel_i > LUT_RENDER_TEXTURE_MAX_INDEX - 1 ) return;
////            pixel_pointer = pixels + buffer;
////            texture_pointer = texture_pixels + pixel_i;
////
////            std::copy_n( texture_pointer , 4 , pixel_pointer );
////            z_buffer[ buffer ] = z_way;
////
////            u_way += u_s;
////            v_way += v_s;
////            z_way += z_step;
////        }
////        way1_x += dir3_x;
////        way2_x += dir2_x;
////        u1_way += step3_u;
////        v1_way += step3_v;
////        u2_way += step2_u;
////        v2_way += step2_v;
////        z1_way += z3_step;
////        z2_way += z2_step;
////    }
