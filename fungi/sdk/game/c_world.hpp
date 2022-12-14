#pragma once
#include "../mono/mono_lib.hpp"
#include "../unity/unity.hpp"

class c_world
{
public:
	static auto find_instance( ) -> c_world*
	{
		MONO_METHOD( game_object_find, E( "UnityEngine::GameObject.Find()" ), 1, std::uintptr_t( * )( unity::c_string ) );

		const auto game_world = game_object_find( E( L"GameWorld" ) );
		if ( !game_world )
			return nullptr;

		const auto world = *reinterpret_cast< uintptr_t* >( game_world + 0x10 );
		if ( !world )
			return nullptr;

		const auto lgw_buffer = *reinterpret_cast< uintptr_t* >( world + 0x30 );
		if ( !lgw_buffer )
			return nullptr;

		const auto lgw_buffer2 = *reinterpret_cast< uintptr_t* >( lgw_buffer + 0x18 );
		if ( !lgw_buffer2 )
			return nullptr;

		return *reinterpret_cast< c_world** >( lgw_buffer2 + 0x28 );
	}

	auto get_players( )
	{
		return *reinterpret_cast< unity::c_list<std::uintptr_t>** >( this + 0x88 );
	}

	auto get_items( )
	{
		return *reinterpret_cast< unity::c_list<std::uintptr_t>** >( this + 0x68 );
	}
};