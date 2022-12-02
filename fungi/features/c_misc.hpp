#pragma once

class features::c_misc
{
public:
	static auto inf_stamina( ) -> void
	{
		const auto physical = *reinterpret_cast< std::uintptr_t* >( reinterpret_cast< std::uintptr_t >( sdk::local_player ) + 0x4F0 );

		if ( !fungi::valid_pointer( physical ) )
			return;

		const auto stamina = *reinterpret_cast< std::uintptr_t* >( physical + 0x38 );
		const auto hands_stamina = *reinterpret_cast< std::uintptr_t* >( physical + 0x40 );
		const auto oxygen = *reinterpret_cast< std::uintptr_t* >( physical + 0x48 );

		*reinterpret_cast< float* >( stamina + 0x48 ) = 300.f;
		*reinterpret_cast< float* >( hands_stamina + 0x48 ) = 300.f;
		*reinterpret_cast< float* >( oxygen + 0x48 ) = 300.f;
	}

	static auto instant_aim( ) -> void
	{
		*reinterpret_cast< float* >( sdk::local_player->procedural_weapon_animation( ) + 0x198 ) = 1000.f;
	}

	static auto weapon_removals( ) -> void
	{
		const auto shot_effector = *reinterpret_cast< std::uintptr_t* >( sdk::local_player->procedural_weapon_animation( ) + 0x48 );
		if ( !fungi::valid_pointer( shot_effector ) )
			return;

		*reinterpret_cast< float* >( shot_effector + 0x70 ) = 0.f; // intensity


		const auto breath_effector = *reinterpret_cast< std::uintptr_t* >( sdk::local_player->procedural_weapon_animation( ) + 0x28 );
		if ( !fungi::valid_pointer( breath_effector ) )
			return;

		*reinterpret_cast< float* >( breath_effector + 0xA4 ) = 0.f; // intensity


		*reinterpret_cast< int* >( sdk::local_player->procedural_weapon_animation( ) + 0x100 ) = 1; // mask
	}

	static auto no_visor( ) -> void
	{
		MONO_OBFUSCATED_METHOD( get_instance, E( "Assembly-CSharp" ), E( "\\uE76F" ), E( "get_Instance" ), std::uintptr_t( * )( ) );
		MONO_OBFUSCATED_METHOD( get_visor_effect, E( "Assembly-CSharp" ), E( "\\uE76F" ), E( "get_VisorEffect" ), std::uintptr_t( * )( std::uintptr_t ) );

		auto instance = get_instance( );
		if ( !fungi::valid_pointer( instance ) )
			return;

		auto visor = get_visor_effect( instance );
		if ( !fungi::valid_pointer( visor ) )
			return;

		*reinterpret_cast< float* >( visor + 0xB8 ) = 0.f;
	}

	static auto loot_through_walls( ) -> void
	{
		MONO_METHOD( get_instance_fn, E( "EFTHardSettings.get_Instance()" ), -1, std::uintptr_t( * )( void ) );

		auto hard_settings = get_instance_fn( );

		if ( !fungi::valid_pointer( hard_settings ) )
			return;

		*reinterpret_cast< float* >( hard_settings + 0x1C8 ) = 5.f; // LOOT_RAYCAST_DISTANCE
		//*reinterpret_cast< float* >( hard_settings + 0x1CC ) = 5.f; // DOOR_RAYCAST_DISTANCE
		//*reinterpret_cast< float* >( hard_settings + 0x1D0 ) = -1.f;// BEHIND_CAST
		//*reinterpret_cast< float* >( hard_settings + 0x1D4 ) = 5.f; // PLAYER_RAYCAST_DISTANCE

		*reinterpret_cast< int32_t* >( sdk::game_world + 0xC ) = 0;
	}
};