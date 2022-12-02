#pragma once
#include "../mono/mono_lib.hpp"
#include "../unity/unity.hpp"
#include "c_item.hpp"

class c_weapon : public c_item
{
public:
	auto get_current_and_max_ammo( float& current, float& max ) -> void
	{
		const static auto get_current_magazine_fn = reinterpret_cast< std::uintptr_t( * )( std::uintptr_t ) >( mono_lib::method( E( "EFT.InventoryLogic" ), E( "Weapon" ), E( "GetCurrentMagazine" ), -1 ) );

		MONO_OBFUSCATED_METHOD( max_count_fn, E( "Assembly-CSharp" ), E( "\\uE8E9" ), E( "get_MaxCount" ), int( * )( std::uintptr_t ) );
		MONO_OBFUSCATED_METHOD( count_fn, E( "Assembly-CSharp" ), E( "\\uE8E9" ), E( "get_Count" ), int( * )( std::uintptr_t ) );

		if ( const auto magazine = get_current_magazine_fn( std::uintptr_t( this ) ) )
		{
			current += count_fn( magazine );
			max += max_count_fn( magazine );
		} 
	}

	auto get_ammo_template( ) -> std::uintptr_t 
	{
		const static auto get_ammo_template_fn = reinterpret_cast<std::uintptr_t( * )( std::uintptr_t )>( mono_lib::method( E( "EFT.InventoryLogic" ), E( "Weapon" ), E( "get_CurrentAmmoTemplate" ), -1 ) );

		return get_ammo_template_fn( std::uintptr_t( this ) );
	}
};