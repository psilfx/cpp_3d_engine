#pragma once
#include <array>
#include <memory>
#include "PFX_Geometry.h"

class PFX_Level_Cell
{
    private:
        std::array<float, 3> _position = {0};
        PFX_Geometry* _geometry[ 10 ] = {nullptr};
        std::unique_ptr<PFX_Geometry> _plane;
    public:
        void AddPlane();
        void AddGeometry();
        PFX_Geometry& GetPlane();
        void Update();
        PFX_Level_Cell( std::array<float, 3> position );
        ~PFX_Level_Cell();

        //Move-конструктор (разрешаем перемещение)
        PFX_Level_Cell( PFX_Level_Cell&& other ) noexcept : _position( other._position ) , _plane( std::move( other._plane ) )  // перемещаем unique_ptr
        {
            for ( int i = 0; i < 10; i++ ) {
                _geometry[i] = other._geometry[i];
                other._geometry[i] = nullptr;
            }
        }

        //«апрещаем копирование
        PFX_Level_Cell( const PFX_Level_Cell& ) = delete;
        PFX_Level_Cell& operator=( const PFX_Level_Cell& ) = delete;

        //–азрешаем move-присваивание
        PFX_Level_Cell& operator=( PFX_Level_Cell&& other ) noexcept {
            if ( this != &other ) {
                _position = other._position;
                _plane = std::move( other._plane );
                for (int i = 0; i < 10; i++) {
                    _geometry[i] = other._geometry[i];
                    other._geometry[i] = nullptr;
                }
            }
            return *this;
        }
};
