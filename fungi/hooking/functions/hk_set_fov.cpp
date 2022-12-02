#include "../hooks.hpp"

auto hooks::hk_set_fov( void* instance, float x, float time, bool applyFovOnCamera ) -> void
{
	x += 20;

	hooks::set_fov.toggle_hook( true );
	hooks::set_fov.get_original<decltype( &hooks::hk_set_fov )>( )( instance, x, time, applyFovOnCamera );
	hooks::set_fov.toggle_hook( false );

	return;
}