#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>


template <typename const_iterator>
static auto findCoorTuple(const const_iterator& first, const const_iterator& last) 
    -> std::tuple<const_iterator, const_iterator, const_iterator>;

template <typename T>
static void updatePolygon(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm);

template <typename T, typename const_iterator>
void rectirization(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    result.clear();

    while (polygon.size() > 0) {
        const auto& coor_tuple = findCoorTuple(polygon.cbegin(), polygon.cend());

        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        // extract rectangle
        result.emplace_back(Pk.getX(), 
                            Pk.getY(), 
                            Pl.getX() - Pk.getX(), 
                            Pm.getY() - Pk.getY());

        // update polygon (point array)
        updatePolygon(polygon, Pk, Pl, Pm);
    }
}