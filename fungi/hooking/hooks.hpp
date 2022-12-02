#pragma once
#include "hooking_lib.hpp"

#define JIT_FN( type, name, args ) inline jit_hook_c name; type hk_##name args;

namespace hooks
{
	JIT_FN( void, gui_controller_start, ( void* instance ) );
	JIT_FN( void, gui_controller_ongui, ( void* instance ) );

	JIT_FN( std::uintptr_t, get_skinned_mesh_renderer, ( void* instance ) );

	JIT_FN( void, set_fov, ( void* instance, float x, float time, bool applyFovOnCamera ) );

	JIT_FN( void, preloader_ui_update, ( void* instance ) );
}