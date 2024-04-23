#include <iostream>
#include "Decomposition.hpp"

void test_Edge_based_decomposition();

int main(){
    test_Edge_based_decomposition();
    return 0;
}

void test_Edge_based_decomposition(){
    std::vector< Coor<int> > polygon;
    std::vector< Rect<int> > result;

#if 1
    // Test case 1 which PTR algorithm fails
    polygon.emplace_back(1, 1);
    polygon.emplace_back(4, 1);
    polygon.emplace_back(4, 2);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(5, 3);
    polygon.emplace_back(4, 3);
    polygon.emplace_back(4, 4);
    polygon.emplace_back(3, 4);
    polygon.emplace_back(3, 3);
    polygon.emplace_back(2, 3);
    polygon.emplace_back(2, 4);
    polygon.emplace_back(1, 4);
    //polygon.emplace_back(1, 1);
#endif 

#if 0
    // Test case 2 which PTR algorithm fails
    polygon.emplace_back(2, 1);
    polygon.emplace_back(4, 1);
    polygon.emplace_back(4, 2);
    polygon.emplace_back(5, 2);
    polygon.emplace_back(5, 3);
    polygon.emplace_back(4, 3);
    polygon.emplace_back(4, 5);
    polygon.emplace_back(2, 5);
    polygon.emplace_back(2, 4);
    polygon.emplace_back(1, 4);
    polygon.emplace_back(1, 3);
    polygon.emplace_back(2, 3);
    //polygon.emplace_back(2, 1);
#endif

#if 0
    polygon.emplace_back(308, 2);
    polygon.emplace_back(308, 66);
    polygon.emplace_back(175, 66);
    polygon.emplace_back(175, 98);
    polygon.emplace_back(5, 98);
    polygon.emplace_back(5, 146);
    polygon.emplace_back(228, 146);
    polygon.emplace_back(228, 242);
    polygon.emplace_back(264, 242);
    polygon.emplace_back(264, 322);
    polygon.emplace_back(485, 322); //! duplicate point
    polygon.emplace_back(485, 306);
    polygon.emplace_back(297, 306);
    polygon.emplace_back(297, 82);
    polygon.emplace_back(485, 82);
    polygon.emplace_back(485, 322);
    polygon.emplace_back(537, 322);
    polygon.emplace_back(537, 66);
    polygon.emplace_back(314, 66);
    polygon.emplace_back(314, 2);
 //   polygon.emplace_back(308, 2);
#endif

/*
    polygon.emplace_back(5, 98);
    polygon.emplace_back(5, 146);
    polygon.emplace_back(228, 146);
    polygon.emplace_back(228, 242);
    polygon.emplace_back(264, 242);
    polygon.emplace_back(264, 322);
    polygon.emplace_back(485, 322);
    polygon.emplace_back(485, 306);
    polygon.emplace_back(297, 306);
    polygon.emplace_back(297, 82);
    polygon.emplace_back(485, 82);
    polygon.emplace_back(485, 322);
    polygon.emplace_back(537, 322);
    polygon.emplace_back(537, 82);
    polygon.emplace_back(297, 82);
    polygon.emplace_back(297, 98);
    polygon.emplace_back(5, 98);
*/

    std::cout << "Edge_based_decomposition Result:\n" << std::endl;
    Edge_based_decomposition(polygon.begin(), polygon.end(), result);
    std::cout << "rectangle list:\n";
    for (const auto& rect : result) {
        std::cout << "\t<" << rect.getBL() << " - " << rect.getTR() << ">\n";
    }
}
