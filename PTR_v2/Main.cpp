#include "Coor.hpp"
#include <iostream>

void Test_Coor();   // Test Coor class and operators overloading

int main(){

    Test_Coor();

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
    Coor<int> result_add_rvalue = std::move(a) + Coor<int>(2, 2);  // Calls the operator+ overload with rvalue reference
    std::cout << "Result of addition with rvalue reference: " << result_add_rvalue << std::endl;

    // Example 4: Subtraction of Coor object with rvalue reference
    Coor<int> result_sub_rvalue = std::move(a) - Coor<int>(2, 2);  // Calls the operator- overload with rvalue reference
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