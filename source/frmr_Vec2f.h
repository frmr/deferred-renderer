#ifndef FRMR_VEC2F_H
#define FRMR_VEC2F_H

#include <array>

using std::array;

namespace frmr
{
	class Vec2f
	{
	private:
		array<float, 2> point;
		float   		length;

	public:
		array<float, 2>	GetArray() const;
	    float 			GetX() const;
		float 			GetY() const;
		float 			Length();
		void			Reset();
		void			Set( const float x, const float y );
		Vec2f 			Unit();

	public:
		Vec2f 	operator+ ( const Vec2f &rhs ) const;
		Vec2f 	operator- ( const Vec2f &rhs ) const;
		Vec2f 	operator* ( const float &rhs ) const;
		Vec2f   operator/ ( const float &rhs ) const;
		Vec2f& 	operator+= ( const Vec2f &rhs );
		Vec2f& 	operator-= ( const Vec2f &rhs );
		Vec2f& 	operator*= ( const float &rhs );
		Vec2f& 	operator/= ( const float &rhs );


	public:
		Vec2f( const float x, const float y );
		Vec2f();
		~Vec2f();
	};
}

#endif
