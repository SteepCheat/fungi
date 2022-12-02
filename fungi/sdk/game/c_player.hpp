#pragma once
#include "../mono/mono_lib.hpp"
#include "../unity/unity.hpp"

#include "c_weapon.hpp"

class c_settings
{
public:
	auto role( ) -> int
	{
		return *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( this ) + 0x10 );
	}
};

class c_info
{
public:
	auto settings( ) -> c_settings*
	{
		return *reinterpret_cast< c_settings** >( reinterpret_cast< std::uintptr_t >( this ) + 0x40 );
	}

	auto level( ) -> int
	{
		MONO_OBFUSCATED_METHOD( get_level_fn, E( "Assembly-CSharp" ), E( "\\uE632" ), E( "get_Level" ), int( * )( std::uintptr_t ) );
		return get_level_fn( std::uintptr_t( this ) );
	}

	auto registration_date( ) -> int
	{
		return *reinterpret_cast< int* >( reinterpret_cast< std::uintptr_t >( this ) + 0x64 );
	}

	auto player_side( ) -> int
	{
		return *reinterpret_cast<int*>( reinterpret_cast<std::uintptr_t>( this ) + 0x60 );
	}

	auto group_id( ) -> const wchar_t*
	{
		auto group = *reinterpret_cast< std::uintptr_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x20 );

		if ( !group )
			return nullptr;

		return reinterpret_cast< unity::c_string* >( group )->buffer;
	}

	auto name( ) -> unity::c_string*
	{
		if ( this->player_side( ) == 4 && this->registration_date( ) > 0 )
		{
			auto name = *reinterpret_cast<std::uintptr_t*>( reinterpret_cast<std::uintptr_t>( this ) + 0x18 );

			if ( !name )
				return nullptr;

			return reinterpret_cast<unity::c_string*>( name );
		}
		else
		{
			auto name = *reinterpret_cast<std::uintptr_t*>( reinterpret_cast<std::uintptr_t>( this ) + 0x10 );

			if ( !name )
				return nullptr;

			return reinterpret_cast<unity::c_string*>( name );
		}
	}
};

class c_profile
{
public:
	auto info( ) -> c_info*
	{
		return *reinterpret_cast< c_info** >( reinterpret_cast< std::uintptr_t >( this ) + 0x28 );
	}

	auto inventory( ) -> std::uintptr_t
	{
		return *reinterpret_cast< std::uintptr_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x48 );
	}
};

class c_player
{
public:
	auto is_local( ) -> bool
	{
		MONO_METHOD( get_is_your_player_fn, E( "EFT::Player.get_IsYourPlayer()" ), -1, bool( * )( decltype( this ) ) );
		return get_is_your_player_fn( this );
	}

	auto get_health_and_max_health( float& health, float& max_health ) -> void
	{
		MONO_METHOD( get_health_controller_fn, E( "EFT::Player.get_HealthController()" ), -1, std::uintptr_t( * )( decltype( this ) ) );
		const auto health_controller = get_health_controller_fn( this );

		if ( !health_controller )
			return;

		const auto health_body = *reinterpret_cast< uintptr_t* >( health_controller + 0x50 );

		if ( !health_body )
			return;

		const auto body_controller = *reinterpret_cast< uintptr_t* >( health_body + 0x18 );

		if ( !body_controller )
			return;

		for ( int i = 0; i <= 6; i++ )
		{
			auto bodyPart = *reinterpret_cast< uintptr_t* >( body_controller + 0x30 + ( i * 0x18 ) );
			if ( !bodyPart )
				return;

			auto healthContainer = *reinterpret_cast< std::uintptr_t* >( bodyPart + 0x10 );

			if ( !healthContainer )
				return;

			auto cur = *reinterpret_cast< int* >( healthContainer + 0x10 );
			auto max = *reinterpret_cast< int* >( healthContainer + 0x14 );

			health += cur;
			max_health += max;
		}
	}

	auto procedural_weapon_animation( ) -> std::uintptr_t
	{
		MONO_METHOD( get_procedural_weapon_animation_fn, E( "EFT::Player.get_ProceduralWeaponAnimation()" ), -1, std::uintptr_t( * )( decltype( this ) ) );
		return get_procedural_weapon_animation_fn( this );
	}

	auto get_weapon( ) -> c_weapon*
	{
		const auto weapon = fungi::read_chain( this->procedural_weapon_animation( ), { 0x48, 0x28 } );

		if ( !fungi::valid_pointer( weapon ) )
			return nullptr;

		return reinterpret_cast< c_weapon* >( weapon );
	}

	auto movement_context( ) -> std::uintptr_t
	{
		MONO_METHOD( get_movement_context_fn, E( "EFT::Player.get_MovementContext()" ), -1, std::uintptr_t( * )( decltype( this ) ) );
		return get_movement_context_fn( this );
	}

	auto in_group( c_player* player ) -> bool
	{
		const auto info = player->profile( )->info( );
		return profile( )->info( )->group_id( ) == player->profile( )->info( )->group_id( );
	}

	template<typename t>
	auto bone_transform( int index ) -> t
	{
		auto temp = *reinterpret_cast< std::uintptr_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0xA8 );

		if ( !temp )
			return nullptr;

		temp = *reinterpret_cast< std::uintptr_t* >( temp + 0x28 );

		if ( !temp )
			return nullptr;

		temp = *reinterpret_cast< std::uintptr_t* >( temp + 0x28 );

		if ( !temp )
			return nullptr;

		const auto bone_matrix = *reinterpret_cast< std::uintptr_t* >( temp + 0x10 );

		if ( !bone_matrix )
			return nullptr;

		return *reinterpret_cast< t* >( bone_matrix + ( 0x20 + ( index * 8 ) ) );
	}

	auto profile( ) -> c_profile*
	{
		MONO_METHOD( get_profile_fn, E( "EFT::Player.get_Profile()" ), -1, c_profile * ( * )( void* ) );
		return get_profile_fn( this );
	}
};