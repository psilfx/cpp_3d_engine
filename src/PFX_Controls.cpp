#include "PFX_Controls.h"
#include <iostream>

PFX_Controls::PFX_Controls()
{

}
void PFX_Controls::Input( int key , bool flag ) {

    switch (key) {
        case 87:  // W
            this->key_up = flag;
            break;
        case 83:  // S
            this->key_down = flag;
            break;
        case 65:  // A
            this->key_left_strafe = flag;
            break;
        case 68:  // D
            this->key_right_strafe = flag;
            break;
        case 32:  // Space
            this->key_jump = flag;
            break;
        case 263: // Left arrow
            this->key_left = flag;
            break;
        case 262: // Right arrow
            this->key_right = flag;
            break;
        default:
            // Ничего не делаем для других клавиш
            break;
    }
}
void PFX_Controls::SetPlayer( PFX_Player& player ) {
    this->_player = &player;
}
void PFX_Controls::Update() {
    int fw = 1 * ( this->key_up ) + ( -1 ) * ( this->key_down );
    int sf  = -1 * ( this->key_left_strafe ) + 1 * ( this->key_right_strafe );
    int rX = -1 * ( this->key_left ) + 1 * ( this->key_right );
//    const ang_h  = rotSpeed * ( this.mouseMove.x > 0 ? 1 : -1 ) * ( this.mouse ) * ( this.mouseMove.x != 0 );
//    const ang_v = -rotSpeed * ( this.mouseMove.y > 0 ? 1 : -1 ) * ( this.mouse ) * ( this.mouseMove.y != 0 );
    //std::cout << fw << " " << sf << "\n";

    this->_player->Control( fw , sf , rX , 0 );
}
PFX_Controls::~PFX_Controls()
{
    //dtor
}
