#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

#define debug_IPTR 1

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
#if debug_IPTR
    for(int i=0; i<9; ++i){
        std::cout << "polygon before: " << std::endl;
        for (const auto& i : polygon) { std::cout << i << " " << std::endl; }

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

        std::cout << "polygon after: " << std::endl;
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

    // check if there are duplicate elements in polygon
    bool duplicate_flag = false;
    for (auto iter = polygon.begin(); iter != polygon.end(); ++iter) {
        if (iter != Pk && (*iter == *Pk)) {
            duplicate_flag = true;
            polygon.erase(iter);
        }
    }
    if(duplicate_flag)
        polygon.erase(Pk);

    /*
    remove the duplicate elements of Pk, Pk will conserve still as the first element
    polygon.unique([&Pk](const auto& lhs, const auto& rhs) -> bool {
            return (lhs == rhs && lhs == *Pk);
        }
    );
    */

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

    bool insert_upl = true, insert_upr = true;
    int  flag_Pk = 1, flag_Pl = 1, flag_upl = 1, flag_upr = 1;

    while (iter != polygon.end()) {
        if ( flag_Pk && (*iter == Pk) ) { 
            iter = polygon.erase(iter); 
            flag_Pk = 0;
        }
        else if ( flag_Pl && (*iter == Pl) ) { 
            iter = polygon.erase(iter); 
            flag_Pl = 0;
        }
        else if ( flag_upl && (*iter == upl) ) { 
            iter = polygon.erase(iter); 
            flag_upl = 0;
            insert_upl = false;
        }
        else if ( flag_upr && (*iter == upr) ) { 
            iter = polygon.erase(iter); 
            flag_upr = 0;
            insert_upr = false;
        }
        else { 
            ++iter; 
        }
    }

    // Check Fig 7-d situation
    bool empty_ur_dl = true; // point out that no points in polygon : (iter->getX() < upr.getX() && iter->getY() < upr.getY()) or (iter->getX() > upr.getX() && iter->getY() > upr.getY())
    bool exit_dr = false; // point out that exits at least one point in polygon : (iter->getX() > upr.getX() && iter->getY() < upr.getY())
    bool exit_Ul = false; // point out that exits at least one point in polygon : (iter->getX() < upr.getX() && iter->getY() > upr.getY())
    iter = polygon.begin();
    if(!insert_upr) {
        while (iter != polygon.end()) {
            if ( (iter->getX() < upr.getX() && iter->getY() < upr.getY()) ||
                (iter->getX() > upr.getX() && iter->getY() > upr.getY()) ) {
                empty_ur_dl = false;
                break;
            }

            if (iter->getX() > upr.getX() && iter->getY() < upr.getY()) {
                exit_dr = true;
            }

            if (iter->getX() < upr.getX() && iter->getY() > upr.getY()) {
                exit_Ul = true;
            }

            ++iter;
        }
    }

    bool insert_more_upr = empty_ur_dl && exit_dr && exit_Ul;

#if debug_IPTR
    std::cout << "insert_upl: " << insert_upl << std::endl;
    std::cout << "insert_upr: " << insert_upr << std::endl;

    std::cout << "empty_ur_dl: " << empty_ur_dl << std::endl;
    std::cout << "exit_dr: " << exit_dr << std::endl;
    std::cout << "exit_Ul: " << exit_Ul << std::endl;
    std::cout << "insert_more_upr: " << insert_more_upr << std::endl;
#endif
    if (insert_upl)      { polygon.emplace_back(upl); }
    if (insert_upr)      { polygon.emplace_back(upr); }
    if (insert_more_upr) { polygon.emplace_back(upr); polygon.emplace_back(upr);}
}