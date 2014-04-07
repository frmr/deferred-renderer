#ifndef FRMR_VEC3F_H
#define FRMR_VEC3F_H

#include <array>
using std::array;

namespace frmr
{
	class Vec3f
	{
	private:
		array<float, 3> point;
		float   		length;

	public:
		array<float, 3>	GetArray() const;
		float			GetAt( const size_t index ) const;
	    float   		GetX() const;
		float   		GetY() const;
		float			GetZ() const;

		float   		Length();
		void    		Reset();

		void			Set( const float x, const float y, const float z );
		void			SetAt( const size_t index, const float newValue );
		void			SetX( const float newX );
		void			SetY( const float newY );
		void			SetZ( const float newZ );

		size_t			Size() const;
		Vec3f   		Unit();

	public:
		Vec3f 	operator+ ( const Vec3f &rhs ) const;
		Vec3f 	operator- ( const Vec3f &rhs ) const;
		Vec3f 	operator* ( const float &rhs ) const;
		Vec3f   operator/ ( const float &rhs ) const;
		Vec3f& 	operator+= ( const Vec3f &rhs );
		Vec3f& 	operator-= ( const Vec3f &rhs );
		Vec3f& 	operator*= ( const float &rhs );
		Vec3f&	operator/= ( const float &rhs );

	public:
		Vec3f( const float x, const float y, const float z );
		Vec3f( const float xyz );
		Vec3f();
		~Vec3f();
	};
}

#endif
