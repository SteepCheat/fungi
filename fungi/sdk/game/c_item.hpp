#pragma once
#include "../mono/mono_lib.hpp"
#include "../unity/unity.hpp"

class c_item
{
public:
	auto get_short_name( ) -> unity::c_string*
	{
		const static auto get_short_name_fn = reinterpret_cast< unity::c_string * ( * )( std::uintptr_t ) >( mono_lib::method( E( "EFT.InventoryLogic" ), E( "Item" ), E( "get_ShortName" ), -1 ) );

		return get_short_name_fn( std::uintptr_t( this ) );
	}

	auto get_name( ) -> unity::c_string*
	{
		const static auto get_name_fn = reinterpret_cast< unity::c_string * ( * )( std::uintptr_t ) >( mono_lib::method( E( "EFT.InventoryLogic" ), E( "Item" ), E( "get_Name" ), -1 ) );

		return get_name_fn( std::uintptr_t( this ) );
	}
};