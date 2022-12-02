#pragma once
#include "../mono/mono_lib.hpp"
#include "../unity/unity.hpp"

class c_loot_item
{
public:
	auto get_position( ) -> math::vec3_t
	{
		const static auto get_transform_fn = reinterpret_cast< unity::c_transform * ( * )( std::uintptr_t ) >( mono_lib::method( E( "UnityEngine" ), E( "Component" ), E( "get_transform" ), -1 ) );
		const auto transform = get_transform_fn( std::uintptr_t( this ) );

		return transform->get_position( );
	}

	auto get_name( ) -> unity::c_string*
	{
		const auto name_obj = *reinterpret_cast< std::uintptr_t* >( reinterpret_cast< std::uintptr_t >( this ) + 0x60 );

		return reinterpret_cast< unity::c_string* >( name_obj );
	}
};