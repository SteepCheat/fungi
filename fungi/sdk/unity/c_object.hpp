#pragma once

class unity::c_object
{
public:
	static auto dont_destroy_on_load( std::uintptr_t object ) -> void
	{
		MONO_METHOD( dont_destroy_on_load_fn, E( "UnityEngine::Object.DontDestroyOnLoad()" ), -1, void( * )( std::uintptr_t ) );
		return dont_destroy_on_load_fn( object );
	}

	static auto destroy( std::uintptr_t object ) -> void
	{
		MONO_METHOD( destroy_fn, E( "UnityEngine::Object.Destroy()" ), 1, void( * )( std::uintptr_t ) );
		return destroy_fn( object );
	}
};