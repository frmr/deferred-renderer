#ifndef FRMR_BOUNDING_BOX
#define FRMR_BOUNDING_BOX

#include <vector>

using std::vector;

namespace frmr
{
	template<class T>
	class BoundingBox
	{
	private:
		T	min;
		T	max;

	public:
		bool	Contains( const T point ) const;
		T		GetMin() const;
		T		GetMax() const;

	public:
		BoundingBox( const vector<T> &points );

	};
}

#endif // FRMR_BOUNDING_BOX
