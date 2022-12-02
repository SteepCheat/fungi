#pragma once
#include "../renderer/engine_renderer.hpp"

class features::c_visuals
{
public:
	static void player_esp( c_player* player )
	{
		if ( player->is_local( ) )
			return;

		auto profile = player->profile( );
		auto info = profile->info( );

		auto base_transform = player->bone_transform<unity::c_transform*>( 0 );
		auto head_transform = player->bone_transform<unity::c_transform*>( 133 );

		auto base_position = base_transform->get_position( );
		auto head_position = head_transform->get_position( );

		auto base_w2s = unity::c_screen::transform_point( base_position );
		auto standing_w2s = unity::c_screen::transform_point( base_position + math::vec3_t{ 0, 1.9f, 0 } );
		auto head_w2s = unity::c_screen::transform_point( head_position );

		if ( base_w2s.empty( ) )
			return;

		const auto distance = static_cast< int >( sdk::local_player->bone_transform<unity::c_transform*>( 133 )->get_position( ).distance_3d( head_position ) );
		const auto distance_str = std::wstring( E( L" [" ) ) + std::to_wstring( distance ) + std::wstring( E( L"m]" ) );

		float box_height = ( base_w2s.y - head_w2s.y ) * 1.2f;
		float box_width = ( base_w2s.y - standing_w2s.y ) * 0.45f;

		auto box_pos = math::vec2_t{ base_w2s.x - box_width * 0.5f, base_w2s.y - box_height };

		renderer::color_t esp_color = { 139, 106, 189, 255 };


		renderer::gui::rect( box_pos.x - 1, box_pos.y - 1, box_width + 2, box_height + 2, { 0, 0, 0, 180 } );
		renderer::gui::rect( box_pos.x, box_pos.y, box_width, box_height, esp_color );

		const auto name = info->name( )->localized( )->buffer;

		const auto str = name + distance_str;
		 
		renderer::gui::string( box_pos.x - 100.f, box_pos.y - 18.f, box_width + 200.f, 20.f, str.c_str( ), { 255, 255, 255, 255 }, true, true );


		float health{}, max_health{};
		player->get_health_and_max_health( health, max_health );

		float hp_height = ( health / max_health ) * ( box_height - 2 );
		renderer::gui::filled_rect( { box_pos.x - 7, box_pos.y, 4, box_height }, { 0, 0, 0, 180 } );
		renderer::gui::filled_rect( { box_pos.x - 6, box_pos.y + box_height - hp_height - 1, 2, hp_height }, esp_color );


		const auto weapon = player->get_weapon( );
		renderer::gui::string( box_pos.x - 100.f, box_pos.y + box_height + 2.f, box_width + 200.f, 20.f, weapon->get_short_name( )->localized( )->buffer, { 255, 255, 255, 255 }, true, true );
		

		float ammo{ }, max_ammo{ };
		weapon->get_current_and_max_ammo( ammo, max_ammo );

		float ammo_bar_width = float( ammo / max_ammo ) * ( box_width - 2.f );
		renderer::gui::filled_rect( { box_pos.x, box_pos.y + box_height - 1 + 5, box_width, 4 }, { 0, 0, 0, 180 } );
		renderer::gui::filled_rect( { box_pos.x + 1, box_pos.y + box_height + 5, ammo_bar_width, 2 }, esp_color );


		std::vector< std::pair< std::wstring, renderer::color_t > > flags;

		const auto level = player->profile( )->info( )->level( );
		const auto level_string = std::wstring( E( L"lvl: " ) ) + std::to_wstring( level );

		flags.emplace_back( level_string, renderer::color_t{ 255, 255, 255, 255 } );

		for ( std::size_t i = 0; i < flags.size( ); ++i )
		{
			auto& [flag, color] = flags[ i ];
			renderer::gui::string( box_pos.x + box_width + 4, box_pos.y + ( 10 * i ) - 4, 300, 20, flag.c_str( ), color, false, true );
		}
	}

	static void item_esp( c_loot_item* loot_item )
	{
		const auto position = loot_item->get_position( );

		const auto name = loot_item->get_name( );

		if ( name->size <= 0 ) // terrible check for if container or whatever
			return;

		const auto item = reinterpret_cast< c_item* >( *reinterpret_cast< std::uintptr_t* >( loot_item ) + 0x50 );

		if ( !fungi::valid_pointer( item ) )
			return;

		const auto distance = static_cast< int >( sdk::local_player->bone_transform<unity::c_transform*>( 133 )->get_position( ).distance_3d( position ) );
		const auto distance_str = std::wstring( E( L" [" ) ) + std::to_wstring( distance ) + std::wstring( E( L"m]" ) );

		if ( distance > 150 )
			return;

		auto w2s_pos = unity::c_screen::transform_point( position );
		if ( w2s_pos.empty( ) )
			return;

		const auto str = name->localized( )->buffer + distance_str;

		renderer::gui::string( w2s_pos.x, w2s_pos.y, 300, 20, str.c_str( ), { 174, 209, 125, 255 }, false, true );
	}

	static void extract_esp( std::uintptr_t extract )
	{
		if ( !is_open( extract ) )
			return;

		const auto settings = *reinterpret_cast< std::uintptr_t* >( extract + 0x58 );
		const auto name_obj = *reinterpret_cast< std::uintptr_t* >( settings + 0x10 );

		const auto name = reinterpret_cast< unity::c_string* >( name_obj )->localized( )->buffer;

		const static auto get_transform_fn = reinterpret_cast< unity::c_transform * ( * )( std::uintptr_t ) >( mono_lib::method( E( "UnityEngine" ), E( "Component" ), E( "get_transform" ), -1 ) );
		const auto transform = get_transform_fn( std::uintptr_t( extract ) );

		const auto position = transform->get_position( );

		const auto distance = static_cast< int >( sdk::local_player->bone_transform<unity::c_transform*>( 133 )->get_position( ).distance_3d( position ) );
		const auto distance_str = std::wstring( E( L" [" ) ) + std::to_wstring( distance ) + std::wstring( E( L"m]" ) );

		auto w2s_pos = unity::c_screen::transform_point( position );
		if ( w2s_pos.empty( ) )
			return;

		const auto str = name + distance_str;

		renderer::gui::string( w2s_pos.x, w2s_pos.y, 300, 20, str.c_str( ), { 125, 187, 209, 255 }, false, true );
	}
	
private:
	static auto is_open( std::uintptr_t extract ) -> bool
	{
		if ( !fungi::valid_pointer( ( void* )extract ) )
			return false;

		const auto status = *reinterpret_cast< int* >( extract + 0xA8 );

		if ( status == 1 || status == 2 )
			return false;

		return true;
	}
};