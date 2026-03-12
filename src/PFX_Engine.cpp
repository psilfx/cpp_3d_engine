#include "PFX_Engine.h"
#include "core/PFX_Context.h"

PFX_Engine::PFX_Engine() {

}
void PFX_Engine::Init() {
    PFX_Context& context = PFX_Context::GetInstance();
    this->_render = &context.Render();
    this->_level = &context.Level();
    this->_camera = &context.Camera();
    this->_player = &context.Player();
}
void PFX_Engine::Update() {
    this->_player->Update();
    this->_camera->Update();
    this->_level->Update();
    this->_render->Update();
}
void PFX_Engine::Draw() {
    this->_render->Draw();
}
PFX_Engine::~PFX_Engine()
{

}
