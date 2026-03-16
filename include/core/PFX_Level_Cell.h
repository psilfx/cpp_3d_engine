#pragma once
#include <array>
#include <memory>
#include "PFX_Geometry.h"

class PFX_Level_Cell
{
    private:
        std::array<float, 3> _position = {0};
        std::vector<PFX_Geometry*> _geometry;
        std::unique_ptr<PFX_Geometry> _plane;
        std::array<std::array<float, 16384>, 6> _lightmaps_cube; //64 * 64 * 4
    public:
        void AddPlane();
        void AddGeometry( PFX_Geometry& geo );
        PFX_Geometry& GetPlane();
        const std::array<float, 3>& GetPosition();
        void Update();
        PFX_Level_Cell( std::array<float, 3> position );
        ~PFX_Level_Cell();

        //Move-конструктор (разрешаем перемещение)
        PFX_Level_Cell( PFX_Level_Cell&& other ) noexcept : _position( other._position ) , _plane( std::move( other._plane ) )  // перемещаем unique_ptr
        {
        }

        //«апрещаем копирование
        PFX_Level_Cell( const PFX_Level_Cell& ) = delete;
        PFX_Level_Cell& operator=( const PFX_Level_Cell& ) = delete;

        //–азрешаем move-присваивание
        PFX_Level_Cell& operator=( PFX_Level_Cell&& other ) noexcept {
            if ( this != &other ) {
                _position = other._position;
                _plane = std::move( other._plane );
            }
            return *this;
        }
};
