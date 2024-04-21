#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

#define debug_IPTR 0

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

    for(int i=0; i<3; ++i){
    //while(polygon.size() > 0) {
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
}

template <typename T>
//static auto findCoorTuple_4_I_PTR(std::list< Coor<T> >& polygon) 
static auto findCoorTuple_4_I_PTR(std::list< Coor<T> > polygon) 
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

    // remove there are duplicate polygon.begin() elements in polygon
    polygon.unique([&polygon](const auto& lhs, const auto& rhs) -> bool {
            return (lhs == rhs && lhs == *polygon.begin());
        }
    );
    // find Pk: the bottom and the left-most coordinate
    typename std::list < Coor<T> >::iterator Pk = polygon.begin();

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

    std::cout << "------------------------" << std::endl;
    std::cout << "upl: " << upl << std::endl;
    std::cout << "upr: " << upr << std::endl;
    std::cout << "------------------------" << std::endl;


    bool insert_upl = false, insert_upr = false;
    bool erase_upl = false, erase_upr = false;

    while (iter != polygon.end()) {
        if (*iter == Pk)        { 
            //iter = polygon.erase(iter); 
            ++iter;
        }
        else if (*iter == Pl)   { 
            ///iter = polygon.erase(iter);
            ++iter;
        }
        else if (*iter == upr)  {
            std::cout << "upr!" << std::endl;

            erase_upr = true;

            Coor<T> last_iter = (iter == polygon.begin()) ? polygon.back() : *(std::prev(iter));
            Coor<T> next_iter = (iter == std::prev(polygon.end())) ? polygon.front() : *(std::next(iter));

            std::cout << "last_iter: " << last_iter << std::endl;
            std::cout << "iter: " << *iter << std::endl;
            std::cout << "next_iter: " << next_iter << std::endl;

            if(
                ((iter->getX() - last_iter.getX()) < 0) && 
                ((next_iter.getY() - iter->getY()) > 0)
            ){
                std::cout << "Test 0-1" << std::endl;
                insert_upr = true;
            }
            else if(
                ((iter->getY() - last_iter.getY()) < 0) && 
                ((next_iter.getX() - iter->getX()) > 0)
            ){
                std::cout << "Test 0-2" << std::endl;
                insert_upr = true;
            }

            ++iter;
        }
        else if (*iter == upl)  {
            std::cout << "upl!" << std::endl;

            erase_upl = true;

            Coor<T> last_iter = (iter == polygon.begin()) ? polygon.back() : *(std::prev(iter));
            Coor<T> next_iter = (iter == std::prev(polygon.end())) ? polygon.front() : *(std::next(iter));

            std::cout << "last_iter: " << last_iter << std::endl;
            std::cout << "iter: " << *iter << std::endl;
            std::cout << "next_iter: " << next_iter << std::endl;

            if(
                ((iter->getX() - last_iter.getX()) > 0) && 
                ((next_iter.getY() - iter->getY()) > 0)
            ){
                std::cout << "Test 1" << std::endl;
                insert_upl = true;
            }
            else if(
                ((iter->getY() - last_iter.getY()) < 0) && 
                ((next_iter.getX() - iter->getX()) < 0)
            ){
                std::cout << "Test 2" << std::endl;
                insert_upl = true;
            }
            ++iter;
        }
        else { ++iter; }
    }

    polygon.remove(Pk);
    polygon.remove(Pl);

    if(erase_upl){
        if(insert_upl) { polygon.emplace_back(upl); }
        else{polygon.remove(upl);}
    }
    else{
        polygon.emplace_back(upl);
    }

    if(erase_upr){
        if(insert_upr) { polygon.emplace_back(upr); }
        else{polygon.remove(upr);}
    }
    else{
        polygon.emplace_back(upr);
    }

    //if (insert_upl) { polygon.emplace_back(upl); }
    //if (insert_upr) { polygon.emplace_back(upr); }
}