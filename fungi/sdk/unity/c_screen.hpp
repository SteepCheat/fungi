#pragma once

class unity::c_screen
{
public:
	static auto get_width( ) -> int
	{
		MONO_METHOD( get_screen_width_fn, E( "UnityEngine::Screen.get_width()" ), 0, int ( * )( ) );
		return get_screen_width_fn( );
	}

	static auto get_height( ) -> int
	{
		MONO_METHOD( get_screen_height_fn, E( "UnityEngine::Screen.get_height()" ), 0, int ( * )( ) );
		return get_screen_height_fn( );
	}

	static auto transform_point( math::vec3_t wrld ) -> math::vec3_t
	{
		const auto current_camera = unity::c_camera::get_main( );
		if ( !current_camera )
			return { 0, 0, 0 };

		auto w2s_point = current_camera->world_to_screen_point( wrld );

		w2s_point.y = unity::c_screen::get_height( ) - w2s_point.y;

		if ( w2s_point.z < 0.01f )
			return { 0, 0, 0 };

		return w2s_point;
	}

	static auto calculate_fov( math::vec3_t pos ) -> float
	{
		auto screen_pos = transform_point( pos );
		if ( screen_pos.x < 0 && screen_pos.y < 0 )
			return 10000;

		auto get_2d_dist = [&]( const math::vec2_t& source, const math::vec3_t& dest )
		{
			return math::sqrtf( ( source.x - dest.x ) * ( source.x - dest.x ) + ( source.y - dest.y ) * ( source.y - dest.y ) );
		};

		return get_2d_dist( math::vec2_t( unity::c_screen::get_width( ) / 2.f, unity::c_screen::get_height( ) / 2.f ), screen_pos );
	}
};