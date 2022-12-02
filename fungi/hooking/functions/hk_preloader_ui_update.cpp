#include "../hooks.hpp"

auto hooks::hk_preloader_ui_update( void* instance ) -> void
{
	const static auto set_session_id = reinterpret_cast< void( * )( void*, unity::c_string ) >( mono_lib::method( E( "EFT.UI" ), E( "PreloaderUI" ), E( "SetSessionId" ), 1 ) );
	set_session_id( instance, E( L"by lexi" ) );

	hooks::preloader_ui_update.toggle_hook( true );
	hooks::preloader_ui_update.get_original<decltype( &hooks::hk_preloader_ui_update )>( )( instance );
	hooks::preloader_ui_update.toggle_hook( false );

	return;
}