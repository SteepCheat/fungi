#pragma once

class unity::c_camera
{
public:
	static unity::c_camera* get_main( )
	{
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto get_main_camera_fn = reinterpret_cast< c_camera * ( __fastcall* )( ) >( std::uintptr_t( unity_base ) + 0x92C250 );
		return get_main_camera_fn( );
	}

	static unity::c_camera* get_current( )
	{
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto get_current_camera_fn = reinterpret_cast< c_camera * ( __fastcall* )( ) >( std::uintptr_t( unity_base ) + 0x92BAD0 );
		return get_current_camera_fn( );
	}

	math::vec3_t world_to_screen_point( math::vec3_t position )
	{
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto world_to_screen_point_fn = reinterpret_cast< void( __fastcall* )( void*, math::vec3_t, int, math::vec3_t& ) >( std::uintptr_t( unity_base ) + 0x929890 );
		math::vec3_t out;
		world_to_screen_point_fn( this, position, 2, out );
		return out;
	}

	float get_aspect_ratio( )
	{
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto get_aspect_fn = reinterpret_cast< float( __fastcall* )( void* ) >( std::uintptr_t( unity_base ) + 0x92B5F0 );

		return get_aspect_fn( this );
	}

	void set_aspect_ratio( float value )
	{
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto set_aspect_fn = reinterpret_cast< void( __fastcall* )( void*, float ) >( std::uintptr_t( unity_base ) + 0x92D660 );

		return set_aspect_fn( this, value );
	}

	math::mat4x4_t projection_matrix( )
	{
		math::mat4x4_t result;
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto get_projectionMatrix_Injected = reinterpret_cast< void( __fastcall* )( void*, math::mat4x4_t& ) >( std::uintptr_t( unity_base ) + 0x92A120 );

		get_projectionMatrix_Injected( this, result );

		return result;
	}

	math::mat4x4_t world_to_camera_matrix( )
	{
		math::mat4x4_t result;
		const static auto unity_base = fungi::get_module( E( L"UnityPlayer.dll" ) ).base;
		const static auto get_worldToCameraMatrix_Injected = reinterpret_cast< void( __fastcall* )( void*, math::mat4x4_t& ) >( std::uintptr_t( unity_base ) + 0x92A660 );

		get_worldToCameraMatrix_Injected( this, result );

		return result;
	}
};