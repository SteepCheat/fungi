#pragma once

class unity::c_string
{
public:
	char zpad[ 0x10 ]{ };
	int size{ };
	wchar_t buffer[ 128 + 1 ];

	c_string( const wchar_t* st )
	{
		size = min( fungi::crt::string::wcslen( st ), 128 );
		for ( size_t idx{ 0 }; idx < size; idx++ )
			buffer[ idx ] = st[ idx ];

		buffer[ size ] = 0;
	}

	c_string* localized( )
	{
		MONO_OBFUSCATED_METHOD( localize_fn, E( "Assembly-CSharp" ), E( "\\uE69B" ), E( "Localized" ), unity::c_string* ( * )( unity::c_string*, unity::c_string, unity::c_string ) );

		return localize_fn( this, nullptr, nullptr );
	}
};