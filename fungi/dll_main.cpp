#include "hooking/hooks.hpp"
#include "sdk/unity/unity.hpp"

auto __stdcall DllMain( void*, std::uint32_t call_reason, void* ) -> bool
{
	if ( call_reason != 1 )
		return false;

	mono_lib::init( );
	{
		MONO_OBFUSCATED_METHOD( set_fov, E( "Assembly-CSharp" ), E( "\\uE76F" ), E( "SetFov" ), void* );
		MONO_OBFUSCATED_METHOD( create_shot, E( "Assembly-CSharp" ), E( "\\uEA6D" ), E( "\\uE004" ), void* );

		const auto game_object = mono_lib::object_new( mono_lib::get_root_domain( ), mono_lib::find_class( E( "GameObject" ), E( "UnityEngine" ) ) );
		unity::c_game_object::create_game_object( game_object, E( L"" ) );
		const auto component = unity::c_game_object::add_component( game_object, mono_lib::type_object( E( "" ), E( "GUIController" ) ) );
		unity::c_object::dont_destroy_on_load( game_object );

		hooks::gui_controller_start.setup( E( "GUIController.Start()" ), &hooks::hk_gui_controller_start );
		hooks::gui_controller_ongui.setup( E( "GUIController.OnGUI()" ), &hooks::hk_gui_controller_ongui );

		hooks::get_skinned_mesh_renderer.setup( E( "Diz.Skinning" ), E( "Skin" ), E( "get_SkinnedMeshRenderer" ), &hooks::hk_get_skinned_mesh_renderer );

		hooks::set_fov.setup( std::uintptr_t( set_fov ), &hooks::hk_set_fov );

		hooks::preloader_ui_update.setup( E( "EFT.UI" ), E( "PreloaderUI" ), E( "Update" ), &hooks::hk_preloader_ui_update );
	}

	return true;
}