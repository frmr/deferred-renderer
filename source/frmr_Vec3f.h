#ifndef FRMR_VEC3F_H
#define FRMR_VEC3F_H

namespace frmr
{
	class Vec3f
	{
	private:
		float   x, y, z;
		float   length;
		bool    valid;

	public:
	    float   GetX() const;
		float   GetY() const;
		float   GetZ() const;
	    bool    IsValid() const;
		float   Length();
		void    Reset();
		void    SetValid( const bool newValid );
		Vec3f   Unit();

	public:
		Vec3f 	operator+ ( const Vec3f &rhs ) const;
		Vec3f 	operator- ( const Vec3f &rhs ) const;
		Vec3f 	operator* ( const float &rhs ) const;
		Vec3f   operator/ ( const float &rhs ) const;
		Vec3f& 	operator+= ( const Vec3f &rhs );
		Vec3f& 	operator-= ( const Vec3f &rhs );
		Vec3f& 	operator*= ( const float &rhs );

	public:
		Vec3f( const float x, const float y, const float z );
		Vec3f();
		~Vec3f();
	};
}

#endif
