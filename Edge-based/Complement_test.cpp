#include "Polygon.hpp"

#include <iostream>

void test_after_overlapped();
void test_edge_list_edge_complement();

int main(){
    //test_after_overlapped();
    test_edge_list_edge_complement();

    return 0;
}

void test_after_overlapped(){

#if 0
    // Test case 1: e2 are the subset of e1
//    edge<int> e1(Coor<int>(0, 0), Coor<int>(4, 0));
//    edge<int> e2(Coor<int>(1, 0), Coor<int>(2, 0));

    // special case: e2 is the subset of e1 and one point of e2 is the same as one point of e1
//    edge<int> e1(Coor<int>(0, 0), Coor<int>(4, 0));
//    edge<int> e2(Coor<int>(0, 0), Coor<int>(2, 0));
#endif

#if 0
    // Test case 1: e1 and e2 are same
    edge<int> e1(Coor<int>(1, 0), Coor<int>(2, 0));
    edge<int> e2(Coor<int>(1, 0), Coor<int>(2, 0));
#endif

#if 0
    // Test case 2: e1 and e2 are overlapped partially
    edge<int> e1(Coor<int>(2, 0), Coor<int>(4, 0));
    edge<int> e2(Coor<int>(1, 0), Coor<int>(3, 0));
#endif

#if 1
    // Test case 3: e1 and e2 are overlapped at a point
    edge<int> e1(Coor<int>(1, 0), Coor<int>(0, 0));
    edge<int> e2(Coor<int>(1, 0), Coor<int>(3, 0));
#endif

#if 0
    // Test case 3: e1 and e2 are not overlapped
    edge<int> e1(Coor<int>(1, 0), Coor<int>(0, 0));
    edge<int> e2(Coor<int>(2, 0), Coor<int>(3, 0));
#endif


    int flag = after_overlapped<int>(e1, e2);

    if(flag == OVERLAP_subset){
        std::cout << "e2 is the subset of e1" << std::endl;
    }
    else if(flag == OVERLAP_full){
        std::cout << "e1 and e2 are same" << std::endl;
    }
    else if(flag == OVERLAP_partial){
        std::cout << "e1 and e2 are overlapped partially" << std::endl;
    }
    else if(flag == OVERLAP_point){
        std::cout << "e1 and e2 are overlapped at a point" << std::endl;
    }
    else if(flag == OVERLAP_none){
        std::cout << "e1 and e2 are not overlapped" << std::endl;
    }

    std::cout << "e1: " << e1.Coor_pair.first << " " << e1.Coor_pair.second << std::endl;
    std::cout << "e2: " << e2.Coor_pair.first << " " << e2.Coor_pair.second << std::endl;   
}


void test_edge_list_edge_complement()
{
    std::vector< edge<int> > edge_list;

    edge<int> e1(Coor<int>(0, 1), Coor<int>(0, 0));
    edge_list.push_back(e1);
    //edge<int> e2(Coor<int>(0, 2), Coor<int>(0, 3));
    //edge_list.push_back(e2);
    //edge<int> e3(Coor<int>(0, 4), Coor<int>(0, 5));
    //edge_list.push_back(e3);
    //edge<int> e4(Coor<int>(3, 0), Coor<int>(4, 0));
    //edge_list.push_back(e4);

    edge<int> e_test(Coor<int>(0, 0), Coor<int>(0, 1));

    edge_list_edge_complement<int>(edge_list, e_test, VERTICAL);
//    edge_list_edge_complement<int>(edge_list, e_test, HORIZONTAL);

    for(auto iter = edge_list.begin(); iter != edge_list.end(); iter++)
    {
        std::cout << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
    }

}