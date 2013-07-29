#ifndef FRMR_VEC2F_H
#define FRMR_VEC2F_H

namespace frmr
{
	class Vec2f
	{
	private:
		float x, y;
		float length;

	public:
		float 	Length();
		Vec2f 	Unit();
		void	Reset();
		float 	GetX() const;
		float 	GetY() const;

	public:
		Vec2f 	operator+ ( const Vec2f &rhs ) const;
		Vec2f 	operator- ( const Vec2f &rhs ) const;
		Vec2f 	operator* ( const float &rhs ) const;
		Vec2f& 	operator+= ( const Vec2f &rhs );
		Vec2f& 	operator-= ( const Vec2f &rhs );
		Vec2f& 	operator*= ( const float &rhs );

	public:
		Vec2f( const float x, const float y );
		Vec2f();
		~Vec2f();
	};
}

#endif
