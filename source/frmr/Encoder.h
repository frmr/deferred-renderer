#ifndef FRMR_ENCODER_H
#define FRMR_ENCODER_H

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

namespace frmr
{
	template <class T>
	class Encoder
	{
		private:
			typedef unsigned char Byte;

			static inline bool IsBigEndian()
			{
				uint32_t testInt = 0x01020304;
				Byte* ptr = (Byte*)&testInt;
				return ptr[0] == 1;
			}

		public:
			static void Encode( const T &var, string &str )
			{
				size_t size = sizeof( T );
				str.clear();
				str.resize( size );
				Byte* ptr = (Byte*)&var;
				if ( IsBigEndian() )
				{
					for ( size_t i = 0; i < size; ++i )
					{
						str[i] = ptr[i];
					}
				}
				else
				{
					for ( size_t i = 0; i < size; ++i )
					{
						str[i] = ptr[(size-1)-i];
					}
				}
			}

			//returning a string might be slow if var is large
			static string Encode( const T &var )
			{
				string str;
				Encode( var, str );
				return str;
			}

			static void Decode( const string &str, T &var )
			{
				size_t size = sizeof( T );
				if ( str.size() != size )
				{
					cout << "frmr::Encoder::Decode() - Encoded variable does not have the right number of characters." << endl;
					std::exit( 1 );
				}
				Byte* ptr = (Byte*)&var;
				if ( IsBigEndian() )
				{
					for ( size_t i = 0; i < size; ++i )
					{
						ptr[i] = str[i];
					}
				}
				else
				{
					for ( size_t i = 0; i < size; ++i )
					{
						ptr[i] = str[(size-1)-i];
					}
				}
			}

			static T Decode( const std::string &str )
			{
				T var;
				Decode( str, var );
				return var;
			}
	};
}

#endif
