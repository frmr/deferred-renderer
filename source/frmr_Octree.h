#ifndef FRMR_OCTREE_H
#define FRMR_OCTREE_H

#include <vector>

#include "frmr_Triangle.h"
#include "frmr_Vec3f.h"

using std::vector;

namespace frmr
{
    template <class Type> class Octree
    {
    private:
        class Octant
        {
        private:
            frmr::Vec3f     minCoord;
            frmr::Vec3f     maxCoord;
            Type*           data;
            vector<Octant>  children;

        private:
            bool    ContainsPoint( const frmr::Vec3f &point ) const;

        public:
            bool    AddChild( const Octant &newOctant );
            Octant* GetChild( const unsigned int index );
            Type*   GetData( const frmr::Vec3f &point ) const;

        public:
            Octant( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord );
            Octant( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, const Type* const data );
            Octant( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, const vector<Octant> &children );
            ~Octant();
        };

    private:
        Octant  rootNode;

    public:
        bool    AddChild( const vector<unsigned int> &parentCoord, const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, const Type* const data );
        Type*   GetData( const frmr::Vec3f &point ) const;

    public:
        Octree( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord );
    };
}

#endif // FRMR_OCTREE_H
