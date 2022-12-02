#pragma once

class unity::c_shader
{
public:
	static auto find( unity::c_string name ) -> unity::c_shader*
	{
		MONO_METHOD( find_shader_fn, E( "UnityEngine::Shader.Find()" ), -1, unity::c_shader * ( * )( unity::c_string ) );
		return find_shader_fn( name );
	}
};