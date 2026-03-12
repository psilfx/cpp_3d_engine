#include "PFX_Triangle.h"
#include "PFX_Lut.h"

PFX_Triangle::PFX_Triangle() {
    this->points = {0};
    this->normal = {0};
}
PFX_Triangle::PFX_Triangle( std::array<float, 5> p1 , std::array<float, 5> p2 , std::array<float, 5> p3 , std::array<float, 3> n ) {
    this->SetPoint( 0 , p1 );
    this->SetPoint( 1 , p2 );
    this->SetPoint( 2 , p3 );
    this->normal = n;
}
void PFX_Triangle::SetPoint( int id , float x , float y , float z , float u , float v ) {
    uint8_t id_i = std::max( 0 , std::min( id , 2 ) ) * LUT_POINT_SIZE;
    this->points[ id_i ] = x;
    this->points[ id_i + 1 ] = y;
    this->points[ id_i + 2 ] = z;
    this->points[ id_i + 3 ] = u;
    this->points[ id_i + 4 ] = v;
    this->points[ id_i + 5 ] = 1.0f; //Свет
}
void PFX_Triangle::SetPoint( int id , std::array<float, 5> p1 ) {
    this->SetPoint( id , p1[ 0 ] , p1[ 1 ] , p1[ 2 ] , p1[ 3 ] , p1[ 4 ] );
}
std::array<float, 6> PFX_Triangle::GetPoint( int id ) {
    uint8_t id_i = id * LUT_POINT_SIZE;
    return { this->points[ id_i ] , this->points[ id_i + 1 ] , this->points[ id_i + 2 ] , this->points[ id_i + 3 ] , this->points[ id_i + 4 ] , this->points[ id_i + 5 ] };
}
PFX_Triangle::~PFX_Triangle() {

}
