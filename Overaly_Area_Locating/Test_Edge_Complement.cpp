#include "../Edge-based_X_Y/Decomposition.hpp"

void TestCase1();
void TestCase2();

int main(){
    TestCase1();
//    TestCase2();

    return 0;
}

void TestCase1(){
    std::vector< edge<int> > edge_list;

    edge<int> e1(Coor<int>(1, 0), Coor<int>(4, 0));

    //edge<int> e2(Coor<int>(-1, 0), Coor<int>(1, 0));
    //edge<int> e2(Coor<int>(2, 0), Coor<int>(3, 0));
    //edge<int> e2(Coor<int>(3, 0), Coor<int>(5, 0));
    //edge<int> e2(Coor<int>(4, 0), Coor<int>(5, 0));
    edge<int> e2(Coor<int>(5, 0), Coor<int>(6, 0));

    edge_list.push_back(e1);


    edge_list_edge_complement<int>(edge_list, e2, HORIZONTAL);

    for(auto e : edge_list){
        std::cout << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
    }
}

void TestCase2(){
    std::vector< edge<int> > edge_list;

    edge<int> e1(Coor<int>(1, 0), Coor<int>(4, 0));

    edge_list.push_back(e1);

    edge<int> e2(Coor<int>(2, 0), Coor<int>(3, 0));
    edge_list_edge_complement<int>(edge_list, e2, HORIZONTAL);

    edge<int> e3(Coor<int>(3, 0), Coor<int>(4, 0));
    edge_list_edge_complement<int>(edge_list, e3, HORIZONTAL);

    for(auto e : edge_list){
        std::cout << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
    }
}
