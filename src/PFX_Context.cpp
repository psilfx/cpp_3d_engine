#include "PFX_Context.h"

//std::unique_ptr<PFX_Context> PFX_Context::_instance = 0;
//PFX_Context& PFX_Context::_instance = 0;

//PFX_Context* PFX_Context::_instance = 0;

PFX_Context& PFX_Context::GetInstance() {
    static PFX_Context _instance;
    return _instance;
}
//PFX_Context::~PFX_Context() {
//    delete _camera;
//    delete _render;
//    delete _engine;
//    delete _level;
//    delete _projection;
//    delete _config;
//    delete _player;
//    delete _instance;
//}
//Иниты
void PFX_Context::InitEngine() {
    //_engine = new PFX_Engine();
    _engine.Init();
}
void PFX_Context::InitCamera() {
    //_camera = new PFX_Camera();
}
void PFX_Context::InitRender( GLFWwindow* window ) {
    _render.Init( window );
    //_render->SetWindow( window );
    _render.SetProjection( this->_projection );
    _render.SetCamera( this->_camera );
}
void PFX_Context::InitLevel() {
    //_level = new PFX_Level();
}
void PFX_Context::InitProjection() {
    //_projection = new PFX_Projection();
}
void PFX_Context::InitConfig( int screen_width , int screen_height ) {
    _config.Init( screen_width , screen_height );
    _config.CopyToLUT();
}
void PFX_Context::InitPlayer() {
//    _player = new PFX_Player();
    _player.SetCamera( this->_camera );
}
//Геттеры
PFX_Camera& PFX_Context::Camera() {
    return _camera;
}
PFX_Render& PFX_Context::Render() {
    return _render;
}
PFX_Engine& PFX_Context::Engine() {
    return _engine;
}
PFX_Level& PFX_Context::Level() {
    return _level;
}
PFX_Projection& PFX_Context::Projection() {
    return _projection;
}
PFX_Config& PFX_Context::Config() {
    return _config;
}
PFX_Player& PFX_Context::Player() {
    return _player;
}

