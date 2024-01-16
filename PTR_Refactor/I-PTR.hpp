#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

template <typename T>
static auto findCoorTuple__4_I_PTR(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>;

template <typename T>
static void updatePolygon_4_I_PTR(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm);

template <typename T, typename const_iterator>
void I_PTR(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    result.clear();
#if 0
    while(polygon.size() > 0) {
        const auto& coor_tuple = findCoorTuple_4_I_PTR(polygon);

        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        result.emplace_back(Pk.getX(), 
                            Pk.getY(), 
                            Pl.getX() - Pk.getX(), 
                            Pm.getY() - Pk.getY());

        updatePolygon_4_I_PTR(polygon, Pk, Pl, Pm);
    }
#endif

#if 1
    for(int i=0; i<4; ++i){
        const auto& coor_tuple = findCoorTuple_4_I_PTR(polygon);

        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        std::cout << "Pk: " << Pk << std::endl;
        std::cout << "Pl: " << Pl << std::endl;
        std::cout << "Pm: " << Pm << std::endl;

        result.emplace_back(Pk.getX(), 
                                Pk.getY(), 
                                Pl.getX() - Pk.getX(), 
                                Pm.getY() - Pk.getY());

        updatePolygon_4_I_PTR(polygon, Pk, Pl, Pm);

        std::cout << "polygon: " << std::endl;
        for (const auto& i : polygon) { std::cout << i << " " << std::endl; }

        std::cout << "===============================================" << std::endl;
    }
#endif
}

template <typename T>
static auto findCoorTuple_4_I_PTR(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>
{
    // Sort the polygon
    polygon.sort([](const auto& lhs, const auto& rhs) -> bool {
            if (lhs.getY() != rhs.getY()) { 
                return (lhs.getY() < rhs.getY()); 
                }
            else { 
                return (lhs.getX() < rhs.getX()); 
                }
        }
    );

    // find Pk: the bottom and the left-most coordinate
    typename std::list < Coor<T> >::iterator Pk = polygon.begin();
    // remove the duplicate elements of Pk, Pk will conserve still as the first element
    polygon.unique([&Pk](const auto& lhs, const auto& rhs) -> bool {
            return (lhs == rhs && lhs == *Pk);
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

template <typename T>
static void updatePolygon_4_I_PTR(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm)
{
    auto iter = polygon.begin();
    const Coor<T> upl(Pk.getX(), Pm.getY()), upr(Pl.getX(), Pm.getY());

    bool insert_upl = true ,insert_upr, insert_more_upr = true;

    //! 待修正
    while (iter != polygon.end()) {
        if (*iter == Pk)        { iter = polygon.erase(iter); }
        else if (*iter == Pl)   { iter = polygon.erase(iter); }
        else if (*iter == upl)  { iter = polygon.erase(iter); insert_upl = false; }
        else if (*iter == upr)  { iter = polygon.erase(iter); insert_upr = false; }
        else                    { ++iter; }
    }

    // Check Fig 7-d situation
    iter = polygon.begin();
    if(!insert_upr) {
        // check no points in polygon : (iter->getX() < upr.getX() && iter->getY() < upr.getY()) or (iter->getX() > upr.getX() && iter->getY() > upr.getY())
        while (iter != polygon.end()) {
            if ( (iter->getX() < upr.getX() && iter->getY() < upr.getY()) ||
                (iter->getX() > upr.getX() && iter->getY() > upr.getY()) ) {
                insert_more_upr = false;
                break;
            }
            ++iter;
        }
    }

    std::cout << "insert_upl: " << insert_upl << std::endl;
    std::cout << "insert_upr: " << insert_upr << std::endl;
    std::cout << "insert_more_upl: " << insert_more_upr << std::endl;

    if (insert_upl)      { polygon.emplace_back(upl); }
    if (insert_upr)      { polygon.emplace_back(upr); }
    if (insert_more_upr) { polygon.emplace_back(upr); polygon.emplace_back(upr); }
}