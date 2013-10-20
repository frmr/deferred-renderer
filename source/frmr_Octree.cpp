#include "frmr_Octree.h"

#include <iostream>

using std::cout;
using std::endl;

template<class Type>
bool frmr::Octree<Type>::Octant::ContainsPoint( const frmr::Vec3f &point ) const
{
    if ( point.GetX() >= minCoord.GetX() && point.GetY() >= minCoord.GetY() && point.GetZ() >= minCoord.GetZ() &&
         point.GetX() <= maxCoord.GetX() && point.GetY() <= maxCoord.GetY() && point.GetZ() <= maxCoord.GetZ() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<class Type>
bool frmr::Octree<Type>::Octant::AddChild( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, Type* const newData )
{
    if ( data == nullptr )
    {
        if ( children.size() == 8 )
        {
            cout << "frmr::Octree::Octant::AddChild() - Could not add child, octant already has eight children." << endl;
            return false;
        }
        else
        {
            children.push_back( new Octant( minCoord, maxCoord, newData ) );
            return true;
        }
    }
    else
    {
        cout << "frmr::Octree::Octant::AddChild() - Could not add child to data-carrying octant." << endl;
        return false;
    }
}

template<class Type>
typename frmr::Octree<Type>::Octant* frmr::Octree<Type>::Octant::GetChild( const int index )
{
    if ( data == nullptr )
    {
        if ( index < 0 || index >= children.size() )
        {
            cout << "frmr::Octree::Octant::GetChild() - Could not find child octant with index " << index << "." << endl;
            return nullptr;
        }
        else
        {
            return children[index];
        }
    }
    else
    {
        cout << "frmr::Octree::Octant::GetChild() - Could not get child from data-carrying octant." << endl;
        return nullptr;
    }
}

template<class Type>
Type* frmr::Octree<Type>::Octant::GetData( const frmr::Vec3f &point ) const
{
    if ( ContainsPoint( point ) )
    {
        //if this isn't a terminal node
        if ( data == nullptr )
        {
            //check children
            Type* childData;
            for ( auto childIt : children )
            {
                childData = childIt->GetData( point );
                if ( childData != nullptr )
                {
                    return childData;
                }
            }
            return nullptr;
        }
        else
        {
            return data;
        }
    }
    else
    {
        return nullptr;
    }
}

template<class Type>
frmr::Octree<Type>::Octant::Octant( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, Type* const data )
    : minCoord( minCoord ),
      maxCoord( maxCoord ),
      data( data )
{
}

template<class Type>
frmr::Octree<Type>::Octant::Octant( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, const vector<Octant*> &children )
    : minCoord( minCoord ),
      maxCoord( maxCoord ),
      data( nullptr ),
      children( children )
{
}

template<class Type>
frmr::Octree<Type>::Octant::~Octant()
{
    delete data;
    for ( auto childIt : children )
    {
        delete childIt;
    }
}

template<class Type>
bool frmr::Octree<Type>::AddChild( const vector<int> &parentCoord, const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, Type* const newData )
{
    Octant* targetOctant = &rootNode;

    for ( auto coordIt : parentCoord )
    {
        targetOctant = targetOctant->GetChild( coordIt );
        if ( targetOctant == nullptr )
        {
            return false;
        }
    }

    targetOctant->AddChild( minCoord, maxCoord, newData );
    return true;
}

template<class Type>
Type* frmr::Octree<Type>::GetData( const frmr::Vec3f &point ) const
{
    Type* childData = rootNode.GetData( point );
    if ( childData == nullptr )
    {
        cout << "frmr::Octree::GetData() - Root node returned null pointer, could not find point." << endl;
    }

    return childData;
}

template<class Type>
frmr::Octree<Type>::Octree( const frmr::Vec3f &minCoord, const frmr::Vec3f &maxCoord, Type* const data )
    : rootNode( minCoord, maxCoord, data )
{
}

//valid instantiations
template class frmr::Octree<int>;
template class frmr::Octree<unsigned int>;
template class frmr::Octree<int16_t>;
