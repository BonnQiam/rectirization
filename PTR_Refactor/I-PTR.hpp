#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

template <typename T>
static auto findCoorTuple_Refactor(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>;

template <typename T, typename const_iterator>
void I_PTR(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    print_list(polygon);

    const auto& coor_tuple = findCoorTuple_4_I_PTR(polygon);

    const auto Pk = *(std::get<0>(coor_tuple));
    const auto Pl = *(std::get<1>(coor_tuple));
    const auto Pm = *(std::get<2>(coor_tuple));

    // print Pk, Pl, Pm
    std::cout << "Pk: " << Pk << std::endl;
    std::cout << "Pl: " << Pl << std::endl;
    std::cout << "Pm: " << Pm << std::endl;

    std::cout << "after sort" << std::endl;
    print_list(polygon);

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