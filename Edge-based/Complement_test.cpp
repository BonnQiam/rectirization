#include "Polygon.hpp"

#include <iostream>

void test_after_overlapped();
void test_edge_list_edge_complement();

int main(){
    test_after_overlapped();

    return 0;
}

void test_after_overlapped(){
#if 0
    edge<int> e1(Coor<int>(1, 0), Coor<int>(2, 0));
    edge<int> e2(Coor<int>(1, 0), Coor<int>(2, 0));
#endif

#if 0
    edge<int> e1(Coor<int>(0, 0), Coor<int>(2, 0));
    edge<int> e2(Coor<int>(1, 0), Coor<int>(3, 0));
#endif

#if 1
    edge<int> e1(Coor<int>(0, 0), Coor<int>(2, 0));
    edge<int> e2(Coor<int>(3, 0), Coor<int>(4, 0));
#endif

    int flag = after_overlapped(e1, e2);

    if(flag == OVERLAP_Full){
        std::cout << "OVERLAP_Full" << std::endl;
    }
    else if(flag == OVERLAP_Partial){
        std::cout << "OVERLAP_Partial" << std::endl;
    }
    else if(flag == OVERLAP_None){
        std::cout << "OVERLAP_None" << std::endl;
    }
    else{
        std::cout << "Error" << std::endl;
    }

    std::cout << "e1: " << e1.Coor_pair.first << " " << e1.Coor_pair.second << std::endl;
    std::cout << "e2: " << e2.Coor_pair.first << " " << e2.Coor_pair.second << std::endl;   
}
