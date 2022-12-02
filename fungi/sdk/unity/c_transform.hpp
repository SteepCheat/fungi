#pragma once

class unity::c_transform
{
public:
    inline auto get_position( ) -> math::vec3_t
    {
        math::vec3_t position;
        const static auto unity_base = fungi::get_module( L"UnityPlayer.dll" ).base;
        const static auto get_position_injected = reinterpret_cast< void( __fastcall* )( void*, math::vec3_t& ) >( std::uintptr_t( unity_base ) + 0x9960A0 );
        get_position_injected( this, position );
        return position;
    }
};