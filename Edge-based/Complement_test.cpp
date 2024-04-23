#include "Polygon.hpp"

#include <iostream>

void test_edge_complement();
void test_add_horizontal_edge();
void test_add_vertical_edge();

int main(){
    //test_edge_complement();
    //test_add_horizontal_edge();
    test_add_vertical_edge();

    return 0;
}

void test_edge_complement(){
    std::vector< edge<int> > complement_edges;

#if 0
    // e1 = e2
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 1));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 1));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e1 = e2
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 1));
    edge <int> e2(Coor<int>(0, 1), Coor<int>(0, 0));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e1 > e2
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 2));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 1));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e1 > e2
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 3));
    edge <int> e2(Coor<int>(0, 2), Coor<int>(0, 3));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e2 > e1
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 1));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 2));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e2 > e1
    edge <int> e1(Coor<int>(0, 2), Coor<int>(0, 3));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 3));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e2 in e1
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 3));
    edge <int> e2(Coor<int>(0, 1), Coor<int>(0, 2));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e1 in e2
    edge <int> e1(Coor<int>(0, 1), Coor<int>(0, 2));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 3));

    edge_complement(e1, e2, complement_edges);
#endif

#if 0
    // e1, e2 intersect
    edge <int> e1(Coor<int>(0, 0), Coor<int>(0, 2));
    edge <int> e2(Coor<int>(0, 1), Coor<int>(0, 3));

    edge_complement(e1, e2, complement_edges);
#endif
    
#if 0
    // e1, e2 intersect
    edge <int> e1(Coor<int>(0, 1), Coor<int>(0, 3));
    edge <int> e2(Coor<int>(0, 0), Coor<int>(0, 2));

    edge_complement(e1, e2, complement_edges);
#endif

#if 1
    // test
    edge <int> e1(Coor<int>(0, 0), Coor<int>(1, 0));
    edge <int> e2(Coor<int>(2, 0), Coor<int>(3, 0));

    edge_complement(e1, e2, complement_edges);
#endif

    if(complement_edges.empty())
    {
        std::cout << "complement_edges is empty" << std::endl;
    }
    else if (complement_edges.size() == 1){
        std::cout << "Edge complement of e1 and e2: " << complement_edges[0].Coor_pair.first << " " << complement_edges[0].Coor_pair.second << std::endl;
    complement_edges.clear();
    }
    else{
        std::cout << "complement_edges size: " << complement_edges.size() << std::endl;
        for (const auto& edge : complement_edges) {
            std::cout << "Edge complement of e1 and e2: " << edge.Coor_pair.first << " " << edge.Coor_pair.second << std::endl;
        }
    }
    
}

void test_add_horizontal_edge()
{
    Polygon_edge_collection<int> Test;

#if 0
    Test.edges.push_back(edge<int>(Coor<int>(1, 0), Coor<int>(2, 0)));
    Test.edges.push_back(edge<int>(Coor<int>(3, 0), Coor<int>(4, 0)));
    Test.edges.push_back(edge<int>(Coor<int>(5, 0), Coor<int>(6, 0)));

    edge<int> e(Coor<int>(0, 0), Coor<int>(7, 0));
#endif

#if 1
    Test.edges.push_back(edge<int>(Coor<int>(2, 3), Coor<int>(3, 3)));
    Test.edges.push_back(edge<int>(Coor<int>(4, 3), Coor<int>(5, 3)));

    edge<int> e(Coor<int>(1, 3), Coor<int>(4, 3));
#endif

    Test.add_horizontal_edge(e);

    for (const auto& edge : Test.edges) {
        std::cout << "Edge: " << edge.Coor_pair.first << " " << edge.Coor_pair.second << std::endl;
    }
}

void test_add_vertical_edge(){
    Polygon_edge_collection<int> Test;

#if 0
    Test.edges.push_back(edge<int>(Coor<int>(0, 1), Coor<int>(0, 2)));
    Test.edges.push_back(edge<int>(Coor<int>(0, 3), Coor<int>(0, 4)));
    Test.edges.push_back(edge<int>(Coor<int>(0, 5), Coor<int>(0, 6)));

    edge<int> e(Coor<int>(0, 0), Coor<int>(0, 7));
#endif

    Test.edges.push_back(edge<int>(Coor<int>(4, 1), Coor<int>(4, 2)));
    Test.edges.push_back(edge<int>(Coor<int>(4, 3), Coor<int>(4, 4)));

    edge<int> e(Coor<int>(4 , 2), Coor<int>(4, 1));

    Test.add_vertical_edge(e);

    for (const auto& edge : Test.edges) {
        std::cout << "Edge: " << edge.Coor_pair.first << " " << edge.Coor_pair.second << std::endl;
    }
}