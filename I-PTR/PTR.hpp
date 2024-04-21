#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

#define print_list(x) for (const auto& i : x) { std::cout << i << " "; } std::cout << std::endl;

template <typename T>
static auto findCoorTuple_Refactor(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>;

template <typename const_iterator>
static auto findCoorTuple(const const_iterator& first, const const_iterator& last) 
    -> std::tuple<const_iterator, const_iterator, const_iterator>;

template <typename T>
static void updatePolygon(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm);

template <typename T, typename const_iterator>
void PTR(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    result.clear();

    while (polygon.size() > 0) {

        // return the target coordinate tuple for generating rectangle: Pk, Pl, Pm
        //const auto& coor_tuple = findCoorTuple(polygon.cbegin(), polygon.cend());
        
        const auto& coor_tuple = findCoorTuple_Refactor(polygon);

        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        // extract rectangle, essentially using `Rect(const T x=T(), const T y=T(), const T w=T(), const T h=T())`
        result.emplace_back(Pk.getX(), 
                            Pk.getY(), 
                            Pl.getX() - Pk.getX(), 
                            Pm.getY() - Pk.getY());

        // update polygon (point array)
        updatePolygon(polygon, Pk, Pl, Pm);
    }
}

template <typename T>
static auto findCoorTuple_Refactor(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>
{
    // find Pk: the bottom and the left-most coordinate
    const auto Pk = std::min_element(polygon.begin(), polygon.end(), 
        [](const auto& lhs, const auto& rhs) -> bool {
                if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                    }
            }
        );

    // find Pl: the bottom and the left-most coordinate except Pk
    const auto Pl = std::min_element(polygon.begin(), polygon.end(), 
        [&Pk](const auto& lhs, const auto& rhs) -> bool {
                // skip the element Pk
                if (lhs == (*Pk)) { 
                    return false; 
                    }
                else if (rhs == (*Pk)) { 
                    return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                }
            }
        );

    // find Pm
    const auto Pm = std::min_element(polygon.begin(), polygon.end(), 
        [&Pk, &Pl](const auto& lhs, const auto& rhs) -> bool {
                // skip the element (x, y) out of the range:
                // Pk.getX() <= x < Pl.getX() && Pk.getY() < y
                if ((lhs.getY() <= Pk->getY()) || 
                    (lhs.getX() < Pk->getX()) || 
                    (lhs.getX() >= Pl->getX())) { 
                        return false; 
                    }
                else if ((rhs.getY() <= Pk->getY()) || 
                        (rhs.getX() < Pk->getX()) || 
                        (rhs.getX() >= Pl->getX())) { 
                            return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) {
                    return (lhs.getY() < rhs.getY()); 
                    }
                else {
                    return (lhs.getX() < rhs.getX()); 
                }
                return true;
            }
        );
    return {Pk, Pl, Pm};
}

template <typename const_iterator>
static auto findCoorTuple(const const_iterator& first, const const_iterator& last) 
    -> std::tuple<const_iterator, const_iterator, const_iterator>
{
    // find Pk: the bottom and the left-most coordinate
    const auto Pk = std::min_element(first, last, 
        [](const auto& lhs, const auto& rhs) -> bool {
                if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                    }
            }
        );

    // find Pl: the bottom and the left-most coordinate except Pk
    const auto Pl = std::min_element(first, last, 
        [&Pk](const auto& lhs, const auto& rhs) -> bool {
                // skip the element Pk
                if (lhs == (*Pk)) { 
                    return false; 
                    }
                else if (rhs == (*Pk)) { 
                    return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                }
            }
        );

    // find Pm
    const auto Pm = std::min_element(first, last, 
        [&Pk, &Pl](const auto& lhs, const auto& rhs) -> bool {
                // skip the element (x, y) out of the range:
                // Pk.getX() <= x < Pl.getX() && Pk.getY() < y
                if ((lhs.getY() <= Pk->getY()) || 
                    (lhs.getX() < Pk->getX()) || 
                    (lhs.getX() >= Pl->getX())) { 
                        return false; 
                    }
                else if ((rhs.getY() <= Pk->getY()) || 
                        (rhs.getX() < Pk->getX()) || 
                        (rhs.getX() >= Pl->getX())) { 
                            return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { return (lhs.getX() < rhs.getX()); }
                
                return true;
            }
        );

    return {Pk, Pl, Pm};
}

template <typename T>
static void updatePolygon(std::list< Coor<T> >& polygon, 
                    const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm)
{
    auto iter = polygon.begin();
    const Coor<T> upl(Pk.getX(), Pm.getY()), upr(Pl.getX(), Pm.getY());
    bool insert_upl = true, insert_upr = true;

    // update policy:
    // 1. if the coordinate exists in the point array: remove from the point array
    // 2. otherwise: add into the point array
    while (iter != polygon.end()) {
        if (*iter == Pk)        { iter = polygon.erase(iter); }
        else if (*iter == Pl)   { iter = polygon.erase(iter); }
        else if (*iter == upl)  { iter = polygon.erase(iter); insert_upl = false; }
        else if (*iter == upr)  { iter = polygon.erase(iter); insert_upr = false; }
        else                    { ++iter; }
    }

    if (insert_upl) { polygon.emplace_back(upl); }
    if (insert_upr) { polygon.emplace_back(upr); }
}