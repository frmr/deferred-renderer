#include "../frmr/BoundingBox.h"

#include <limits>

#include "../frmr/Vec2f.h"
#include "../frmr/Vec3f.h"

template<class T>
bool frmr::BoundingBox<T>::Contains( const T point ) const
{
	for ( unsigned int i = 0; i < point.Size(); i++ )
	{
		if ( point.GetAt( i ) > max.GetAt( i ) || point.GetAt( i ) < min.GetAt( i ) )
		{
			return false;
		}
	}
	return true;
}

template<class T>
T frmr::BoundingBox<T>::GetMin() const
{
	return min;
}

template<class T>
T frmr::BoundingBox<T>::GetMax() const
{
	return max;
}

template<class T>
frmr::BoundingBox<T>::BoundingBox( const vector<T> &points )
	: min( std::numeric_limits<float>::max() ),
	  max( std::numeric_limits<float>::min() )
{
	for ( auto pointIt : points )
	{
		for ( unsigned int i = 0; i < pointIt.Size(); i++ )
		{
			if ( pointIt.GetAt( i ) < min.GetAt( i ) )
			{
				min.SetAt( i, pointIt.GetAt( i ) );
			}
			if ( pointIt.GetAt( i ) > max.GetAt( i ) )
			{
				max.SetAt( i, pointIt.GetAt( i ) );
			}
		}
	}
}

template class frmr::BoundingBox<frmr::Vec2f>;
template class frmr::BoundingBox<frmr::Vec3f>;
