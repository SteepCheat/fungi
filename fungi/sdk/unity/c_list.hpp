#pragma once

template<typename type>
class unity::c_list
{
private:
	char pad_0x10[ 0x10 ];
	uintptr_t list_base;
	uint32_t count;
public:
	int get_count( )
	{
		if ( !this || !list_base )
			return 0;

		return int( this->count );
	}

	type get( uint32_t index )
	{
		if ( !this || !list_base )
			return type( );
		return *reinterpret_cast< type* >( this->list_base + 0x20 + index * 0x8 );
	}
};