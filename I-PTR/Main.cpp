#include <iostream>
#include "PTR.hpp"
#include "I-PTR.hpp"

#define PTR_test        0
#define I_PTR_test      1

void Test_Coor();           // Test Coor class and operators overloading
void Test_PTR();            // Test PTR algorithm

void Test_PTR_Fail_case();  // Test PTR algorithm with fail case

int main(){

//    Test_Coor();
//    Test_PTR();

    Test_PTR_Fail_case();

    return 0;
}

void Test_Coor(){
    Coor<int> a(5, 4);
    Coor<int> b(3, 1);

    // Example 0: stream the Coor object
    std::cout << "Stream the Coor object: " << a << std::endl;

    // Example 1: Addition of two Coor objects
    Coor<int> result_add = a + b;  // Calls the operator+ overload
    std::cout << "Result of addition: " << result_add << std::endl;

    //Example 2: Subtraction of two Coor objects
    Coor<int> result_sub = a - b;  // Calls the operator- overload
    std::cout << "Result of subtraction: " << result_sub << std::endl;

    // Example 3: Addition of Coor object with rvalue reference
    Coor<int> result_add_rvalue = std::move(a) + (2, 2);  // Calls the operator+ overload with rvalue reference
    std::cout << "Result of addition with rvalue reference: " << result_add_rvalue << std::endl;

    // Example 4: Subtraction of Coor object with rvalue reference
    Coor<int> result_sub_rvalue = std::move(a) - (2, 2);  // Calls the operator- overload with rvalue reference
    std::cout << "Result of subtraction with rvalue reference: " << result_sub_rvalue << std::endl;

    // Example 5: Addition of Coor object with scalar value
    Coor<int> result_add_scalar = a + 2;  // Calls the operator+ overload with scalar value
    std::cout << "Result of addition with scalar value: " << result_add_scalar << std::endl;

    // Example 6: Subtraction of Coor object with scalar value
    Coor<int> result_sub_scalar = a - 2;  // Calls the operator- overload with scalar value
    std::cout << "Result of subtraction with scalar value: " << result_sub_scalar << std::endl;

    // Example 7: Addition of Coor object with scalar value and rvalue reference
    Coor<int> result_add_scalar_rvalue = std::move(a) + 2;  // Calls the operator+ overload with scalar value and rvalue reference
    std::cout << "Result of addition with scalar value and rvalue reference: " << result_add_scalar_rvalue << std::endl;

    // Example 8: Subtraction of Coor object with scalar value and rvalue reference
    Coor<int> result_sub_scalar_rvalue = std::move(a) - 2;  // Calls the operator- overload with scalar value and rvalue reference
    std::cout << "Result of subtraction with scalar value and rvalue reference: " << result_sub_scalar_rvalue << std::endl;    
}

void Test_PTR()
{
    std::vector< Coor<int> > polygon;
    std::vector< Rect<int> > result;

    polygon.emplace_back(1, 1);
    polygon.emplace_back(3, 1);
    polygon.emplace_back(3, 3);
    polygon.emplace_back(4, 3);
    polygon.emplace_back(4, 1);
    polygon.emplace_back(5, 1);
    polygon.emplace_back(5, 5);
    polygon.emplace_back(4, 5);
    polygon.emplace_back(4, 4);
    polygon.emplace_back(2, 4);
    polygon.emplace_back(2, 2);
    polygon.emplace_back(1, 2);
    polygon.emplace_back(1, 1);

    PTR(polygon.cbegin(), polygon.cend(), result);

    std::cout << "rectangle list:\n";
    for (const auto& rect : result) {
        std::cout << "\t<" << rect.getBL() << " - " << rect.getTR() << ">\n";
    }
}

void Test_PTR_Fail_case()
{
    std::vector< Coor<int> > polygon;
    std::vector< Rect<int> > result;

#if 1
    // Now Pass! Test case 1 which PTR algorithm fails
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

#if I_PTR_test
    std::cout << "I_PTR Algorithm Result:\n" << std::endl;
    I_PTR(polygon.cbegin(), polygon.cend(), result);
    std::cout << "rectangle list:\n";
    for (const auto& rect : result) {
        std::cout << "\t<" << rect.getBL() << " - " << rect.getTR() << ">\n";
    }
#endif

#if PTR_test
    std::cout << "PTR Algorithm Result:\n" << std::endl;
    PTR(polygon.cbegin(), polygon.cend(), result);
    std::cout << "rectangle list:\n";
    for (const auto& rect : result) {
        std::cout << "\t<" << rect.getBL() << " - " << rect.getTR() << ">\n";
    }
#endif
}