#ifndef Decomposition_hpp
#define Decomposition_hpp

#include "Polygon.hpp"




template <typename T>
void Decomposition(
    const Polygon<T>& poly,
    std::vector< Polygon<T> >& result
)
{
    result.clear();

    Polygon<T> poly_copy = poly;
    poly_copy.vertexes   = poly.vertexes;
    poly_copy.edges      = poly.edges;

}


#endif