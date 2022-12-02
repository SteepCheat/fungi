#pragma once

class unity::c_game_object
{
public:
	static auto create_game_object( std::uintptr_t ptr, unity::c_string name ) -> void
	{
		MONO_METHOD( internal_create_game_object_fn, E( "UnityEngine::GameObject.Internal_CreateGameObject()" ), -1, void( * )( std::uintptr_t, unity::c_string ) );
		return internal_create_game_object_fn( ptr, name );
	}

	static auto add_component( std::uintptr_t ptr, std::uintptr_t type ) -> std::uintptr_t
	{
		MONO_METHOD( add_component_fn, E( "UnityEngine::GameObject.AddComponent()" ), -1, std::uintptr_t( * )( std::uintptr_t, std::uintptr_t ) );
		return add_component_fn( ptr, type );
	}
};