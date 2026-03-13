#include "PFX_Level_Cell.h"

PFX_Level_Cell::PFX_Level_Cell( std::array<float, 3> position ) : _position( position ) {
    // _plane инициализируетс€ автоматически
}
void PFX_Level_Cell::AddPlane() {
    this->_plane = std::make_unique<PFX_Geometry>();
    //Ќиз
    PFX_Triangle tri1;
    tri1.SetPoint( 0 , -0.5f , 0.0f , -0.5f , 0.0f , 0.0f );
    tri1.SetPoint( 1 , 0.5f , 0.0f , -0.5f , 1.0f , 0.0f );
    tri1.SetPoint( 2 , 0.5f , 0.0f , 0.5f , 1.0f , 1.0f );
    tri1.normal = { 0.0f , -1.0f , 0.0f };
    PFX_Triangle tri2;
    tri2.SetPoint( 0 , 0.5f , 0.0f , 0.5f , 1.0f , 1.0f );
    tri2.SetPoint( 1 , -0.5f , 0.0f , 0.5f , 0.0f , 1.0f );
    tri2.SetPoint( 2 , -0.5f , 0.0f , -0.5f , 0.0f , 0.0f );
    tri2.normal = { 0.0f , -1.0f , 0.0f };
    this->_plane->AddTriangle( tri1 );
    this->_plane->AddTriangle( tri2 );
    this->_plane->SetTexture( "images/textures/flat.jpg" );
    this->_plane->Translate( { this->_position[ 0 ] + 0.5f , this->_position[ 1 ] , this->_position[ 2 ] + 0.5f } );
    this->_plane->UpdateNormal();
    this->_plane->Update();
}
void PFX_Level_Cell::Update() {
    this->_plane->Update();
}
PFX_Geometry& PFX_Level_Cell::GetPlane() {
    return *this->_plane;
}
void PFX_Level_Cell::AddGeometry() {
}
PFX_Level_Cell::~PFX_Level_Cell() {

}
