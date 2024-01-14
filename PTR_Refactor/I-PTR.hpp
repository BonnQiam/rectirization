

#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

template <typename T, typename const_iterator>
void I_PTR(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    print_list(polygon);

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

    Coor<T> Pk = polygon.front();
    // remove the duplicate elements of Pk, Pk will conserve still as the first element
    polygon.unique([&Pk](const auto& lhs, const auto& rhs) -> bool {
            return (lhs == rhs && lhs == Pk);
        }
    );

    std::cout << "after sort" << std::endl;
    print_list(polygon);

}