#include "../hooks.hpp"
#include "../../renderer/engine_renderer.hpp"

auto hooks::hk_get_skinned_mesh_renderer( void* instance ) -> std::uintptr_t
{
	hooks::get_skinned_mesh_renderer.toggle_hook( true );
	const auto renderer = hooks::get_skinned_mesh_renderer.get_original<unity::c_renderer* ( * )( void* )>( )( instance );
	hooks::get_skinned_mesh_renderer.toggle_hook( false );

	if ( renderer )
	{
		if ( !renderer::gui::bundle )
			return std::uintptr_t( renderer );

		const auto material = renderer->get_material( );

		if ( !material )
			return std::uintptr_t( renderer );

		const auto shader = renderer::gui::bundle->load_asset<unity::c_shader*>( E( L"chams.shader" ), mono_lib::type_object( E( "UnityEngine" ), E( "Shader" ) ) );

		if ( !shader )
			return std::uintptr_t( renderer );

		material->set_shader( shader );
		material->set_color<renderer::color_t>( E( L"_ColorVisible" ), { 141, 108, 217, 255 } );
		material->set_color<renderer::color_t>( E( L"_ColorBehind" ), { 198, 139, 232, 255 } );
	}

	return std::uintptr_t( renderer );
}