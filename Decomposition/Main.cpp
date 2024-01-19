#include <iostream>
#include "Decomposition.hpp"

void test_Polygon();
void test_Polygon_shrink();
void test_Edge_list_complement();
void test_Decomposition();

#define test_shrink_redundancy_edge         0
#define test_shrink_redundancy_edge_loop    1
#define test_shrink_redundancy_point        0

int main(){

//    test_Polygon();
//    test_Polygon_shrink();
//    test_Edge_list_complement();
    test_Decomposition();

    return 0;
}

void test_Polygon()
{
    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(2, 0));
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(0, 2));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.edges_init();

    std::cout << "edges in polygon: " << std::endl;
    for(auto e : poly.edges){
        std::cout << "(" << e.Coor_pair.first.getX() << ", " << e.Coor_pair.first.getY() << ") ";
        std::cout << "(" << e.Coor_pair.second.getX() << ", " << e.Coor_pair.second.getY() << ")" << std::endl;
    }

    Coor<int> point = Coor<int>(1, 1);
    if(poly.isInside(point)){
        std::cout << "point (" << point.getX() << ", " << point.getY() << ") is inside polygon" << std::endl;
    }
    else{
        std::cout << "point (" << point.getX() << ", " << point.getY() << ") is outside polygon" << std::endl;
    }

/*
    Polygon<int> poly2;
    poly2.edges.push_back(edge<int>(Coor<int>(0, 0), Coor<int>(1, 0)));
    poly2.edges.push_back(edge<int>(Coor<int>(1, 0), Coor<int>(1, 1)));
    poly2.edges.push_back(edge<int>(Coor<int>(1, 1), Coor<int>(0, 1)));
    poly2.edges.push_back(edge<int>(Coor<int>(0, 1), Coor<int>(0, 0)));
    poly2.vertexes_init();

    std::cout << "vertexes in polygon: " << std::endl;
    for(auto v : poly2.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
*/
}

void test_Polygon_shrink()
{
    Polygon<int> poly;
/*
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(1, 0));
    poly.vertexes.push_back(Coor<int>(2, 0));
//    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(2, 3));
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(0, 2));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(0, -1));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(0, 5));
    poly.vertexes.push_back(Coor<int>(0, 0));
*/
    poly.vertexes.push_back(Coor<int>(1, 4));
    poly.vertexes.push_back(Coor<int>(2, 4));
    poly.vertexes.push_back(Coor<int>(2, 3));
    poly.vertexes.push_back(Coor<int>(4, 3));
    poly.vertexes.push_back(Coor<int>(4, 4));
    poly.vertexes.push_back(Coor<int>(3, 4));
    poly.vertexes.push_back(Coor<int>(3, 3));
    poly.vertexes.push_back(Coor<int>(2, 3));
    poly.vertexes.push_back(Coor<int>(2, 4));
    poly.vertexes.push_back(Coor<int>(1, 4));

    poly.edges_init();

#if test_shrink_redundancy_edge_loop
    bool redundancy = true;

    while(redundancy){
        Polygon<int> poly_shrink;
        poly_shrink.edges = poly.edges;
        poly_shrink.vertexes = poly.vertexes;

        std::cout << "Polygon before shrink is " << std::endl;
        for(auto v: poly_shrink.vertexes){
            std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
        }

        redundancy = Polygon_shrink_redundancy_edge(poly, poly_shrink);

        std::cout << "Polygon after shrink is " << std::endl;
        for(auto v: poly_shrink.vertexes){
            std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
        }

        std::cout << "============================" << std::endl;

        if(redundancy){
            poly = poly_shrink;
        }
    }

#endif

#if test_shrink_redundancy_point
    /************************************************************
     * Test Polygon_shrink_redundancy_point
    */

    // Copy poly to poly_shrink
    Polygon<int> poly_shrink;
    poly_shrink.edges = poly.edges;
    poly_shrink.vertexes = poly.vertexes;

    std::cout << "Polygon before shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }

    Polygon_shrink_redundancy_point(poly, poly_shrink);

    std::cout << "Polygon after shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
#endif


#if test_shrink_redundancy_edge
    /************************************************************
     * Test Polygon_shrink_redundancy_edge
    */

    // Copy poly to poly_shrink
    Polygon<int> poly_shrink;
    poly_shrink.edges = poly.edges;
    poly_shrink.vertexes = poly.vertexes;

    std::cout << "Polygon before shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }

    Polygon_shrink_redundancy_edge(poly, poly_shrink);

    std::cout << "Polygon after shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
#endif
}

void test_Edge_list_complement()
{

    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(1, 0));
    poly.vertexes.push_back(Coor<int>(2, 0));
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(0, 2));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.edges_init();


/*
    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(2, 0));
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(0, 2));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(2, 0));
    poly.edge_init();
*/

/*
    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.vertexes.push_back(Coor<int>(0, 2));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(2, 0));
    poly.vertexes.push_back(Coor<int>(2, 2));
    poly.edge_init();
*/
    std::cout << "edge in polygon before complement: " << std::endl;
    for(auto e : poly.edges){
        std::cout << "(" << e.Coor_pair.first.getX() << ", " << e.Coor_pair.first.getY() << ") ";
        std::cout << "(" << e.Coor_pair.second.getX() << ", " << e.Coor_pair.second.getY() << ")" << std::endl;
    }
    
    Polygon<int> rect;
    rect.vertexes.push_back(Coor<int>(0, 0));
    rect.vertexes.push_back(Coor<int>(2, 0));
    rect.vertexes.push_back(Coor<int>(2, 1));
    rect.vertexes.push_back(Coor<int>(0, 1));
    rect.vertexes.push_back(Coor<int>(0, 0));
    poly.edges_init();

    Polygon<int> poly_complement;

    Edge_list_complement(poly, rect, poly_complement);
}

void test_Decomposition()
{
    Polygon<int> poly;
/*
    poly.vertexes.push_back(Coor<int>(1, 1));
    poly.vertexes.push_back(Coor<int>(4, 1));
    poly.vertexes.push_back(Coor<int>(4, 2));
    poly.vertexes.push_back(Coor<int>(5, 2));
    poly.vertexes.push_back(Coor<int>(5, 3));
    poly.vertexes.push_back(Coor<int>(4, 3));
    poly.vertexes.push_back(Coor<int>(4, 4));
    poly.vertexes.push_back(Coor<int>(3, 4));
    poly.vertexes.push_back(Coor<int>(3, 3));
    poly.vertexes.push_back(Coor<int>(2, 3));
    poly.vertexes.push_back(Coor<int>(2, 4));
    poly.vertexes.push_back(Coor<int>(1, 4));
    poly.vertexes.push_back(Coor<int>(1, 1));
*/

    poly.vertexes.push_back(Coor<int>(308, 2));
    poly.vertexes.push_back(Coor<int>(308, 66));
    poly.vertexes.push_back(Coor<int>(175, 66));
    poly.vertexes.push_back(Coor<int>(175, 98));
    poly.vertexes.push_back(Coor<int>(5, 98));
    poly.vertexes.push_back(Coor<int>(5, 146));
    poly.vertexes.push_back(Coor<int>(228, 146));
    poly.vertexes.push_back(Coor<int>(228, 242));
    poly.vertexes.push_back(Coor<int>(264, 242));
    poly.vertexes.push_back(Coor<int>(264, 322));
    poly.vertexes.push_back(Coor<int>(485, 322)); //! duplicate point
    poly.vertexes.push_back(Coor<int>(485, 306));
    poly.vertexes.push_back(Coor<int>(297, 306));
    poly.vertexes.push_back(Coor<int>(297, 82));
    poly.vertexes.push_back(Coor<int>(485, 82));
    poly.vertexes.push_back(Coor<int>(485, 322));
    poly.vertexes.push_back(Coor<int>(537, 322));
    poly.vertexes.push_back(Coor<int>(537, 66));
    poly.vertexes.push_back(Coor<int>(314, 66));
    poly.vertexes.push_back(Coor<int>(314, 2));
    poly.vertexes.push_back(Coor<int>(308, 2));

/*
    poly.vertexes.push_back(Coor<int>(5, 98));
    poly.vertexes.push_back(Coor<int>(5, 146));
    poly.vertexes.push_back(Coor<int>(228, 146));
    poly.vertexes.push_back(Coor<int>(228, 242));
    poly.vertexes.push_back(Coor<int>(264, 242));
    poly.vertexes.push_back(Coor<int>(264, 322));
    poly.vertexes.push_back(Coor<int>(485, 322));
    poly.vertexes.push_back(Coor<int>(485, 306));
    poly.vertexes.push_back(Coor<int>(297, 306));
    poly.vertexes.push_back(Coor<int>(297, 82));
    poly.vertexes.push_back(Coor<int>(485, 82));
    poly.vertexes.push_back(Coor<int>(485, 322));
    poly.vertexes.push_back(Coor<int>(537, 322));
    poly.vertexes.push_back(Coor<int>(537, 82));
    poly.vertexes.push_back(Coor<int>(297, 82));
    poly.vertexes.push_back(Coor<int>(297, 98));
    poly.vertexes.push_back(Coor<int>(5, 98));
*/
    poly.edges_init();

    std::vector< Polygon<int> > result;
    Decomposition(poly, result);

/*
    std::cout << "result: " << std::endl;
    for(auto poly : result){
        for(auto v : poly.vertexes){
            std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
        }
        std::cout << std::endl;
    }
*/
}