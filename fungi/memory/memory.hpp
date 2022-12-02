#pragma once
#include <vector>

namespace fungi
{
	template<typename t>
	inline auto valid_pointer( t pointer ) -> bool
	{
		return ( pointer && pointer > ( t )0x400000 && pointer < ( t )0x7FFFFFFFFFFF );
	}

	template<typename t>
	inline auto read_chain( t base, const std::vector<std::uintptr_t>& offsets ) -> std::uintptr_t
	{
		std::uintptr_t result = *reinterpret_cast< std::uintptr_t* >( base + offsets.at( 0 ) );

		if ( !fungi::valid_pointer( ( void* )result ) )
			return {};

		for ( int i = 1; i < offsets.size( ); i++ )
		{
			result = *reinterpret_cast< std::uintptr_t* >( result + offsets.at( i ) );

			if ( !fungi::valid_pointer( ( void* )result ) )
				return {};
		}

		return result;
	};
}