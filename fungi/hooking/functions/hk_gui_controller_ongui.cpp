#include "../hooks.hpp"
#include "../../renderer/engine_renderer.hpp"
#include "../../features/features.hpp"

#include <algorithm>

auto hooks::hk_gui_controller_ongui( void* instance ) -> void
{
	renderer::gui::setup( );
	renderer::gl::setup( );

	{
		sdk::game_world = c_world::find_instance( );
		if ( !fungi::valid_pointer( sdk::game_world ) )
		{
			sdk::game_world == nullptr;
			sdk::local_player == nullptr;
			goto end;
		}

		auto players = sdk::game_world->get_players( );
		if ( !fungi::valid_pointer( players ) )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto player_count = players->get_count( );
		if ( player_count <= 0 || player_count > 10000 )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		sdk::local_player = reinterpret_cast< c_player* >( players->get( 0 ) );
		if ( !fungi::valid_pointer( sdk::local_player ) )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto items = sdk::game_world->get_items( );
		if ( !fungi::valid_pointer( items ) )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto item_count = items->get_count( );
		if ( item_count <= 0 || item_count > 10000 )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto exit_controller = *reinterpret_cast< std::uintptr_t* >( sdk::game_world + 0x18 );
		if ( !fungi::valid_pointer( exit_controller ) )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto exit_base = *reinterpret_cast< std::uintptr_t* >( exit_controller + 0x20 );
		if ( !fungi::valid_pointer( exit_base ) )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		auto exit_count = *reinterpret_cast< int* >( exit_base + 0x18 );
		if ( exit_count <= 0 || exit_count > 10000 )
		{
			sdk::game_world = nullptr;
			sdk::local_player = nullptr;
			goto end;
		}

		if ( renderer::c_events::get_current_event( )->type( ) == renderer::event_type::repaint )
		{
			for ( int idx = 0; idx < player_count; idx++ )
			{
				const auto player = reinterpret_cast< c_player* >( players->get( idx ) );
				if ( !fungi::valid_pointer( player ) )
					continue;

				features::c_visuals::player_esp( player );
			}

			for ( int idx = 0; idx < item_count; idx++ )
			{
				const auto item = reinterpret_cast< c_loot_item* >( items->get( idx ) );
				if ( !fungi::valid_pointer( item ) )
					continue;

				features::c_visuals::item_esp( item );
			}

			for ( int idx = 0; idx < exit_count; idx++ )
			{
				const auto extract = *reinterpret_cast< std::uintptr_t* >( exit_base + ( 0x20 + ( idx * 8 ) ) );
				if ( !fungi::valid_pointer( extract ) )
					continue;

				features::c_visuals::extract_esp( extract ); // crashes if i use a class for extracts? -_-
			}
		}

		sdk::camera = unity::c_camera::get_main( );

		if ( sdk::camera )
		{
			sdk::camera->set_aspect_ratio( 1.0f + ( 25.f / 100.f ) );
		}

		features::c_misc::inf_stamina( );
		features::c_misc::instant_aim( );
		features::c_misc::weapon_removals( );
		features::c_misc::no_visor( );
		features::c_misc::loot_through_walls( );
	}

end:
	renderer::gui::string_with_background( 10, 10, 300, 20, L"fungi", { 255, 255, 255, 255 }, true );

	return;
}