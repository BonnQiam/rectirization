#include <iostream>
#include "Polygon.hpp"

void test_Polygon();
void test_Polygon_shrink();
void test_Edge_list_complement();

int main(){

//    test_Polygon();
    test_Polygon_shrink();
//    test_Edge_list_complement();

    return 0;
}

void test_Polygon()
{
    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.vertexes.push_back(Coor<int>(1, 0));
    poly.vertexes.push_back(Coor<int>(1, 1));
    poly.vertexes.push_back(Coor<int>(0, 1));
    poly.vertexes.push_back(Coor<int>(0, 0));
    poly.edges_init();

    std::cout << "edges in polygon: " << std::endl;
    for(auto e : poly.edges){
        std::cout << "(" << e.Coor_pair.first.getX() << ", " << e.Coor_pair.first.getY() << ") ";
        std::cout << "(" << e.Coor_pair.second.getX() << ", " << e.Coor_pair.second.getY() << ")" << std::endl;
    }

    std::vector<edge<int>> edges_list;
    poly.find_edges(Coor<int>(0, 0), edges_list);
    std::cout << "edges in polygon that contains (0, 0): " << std::endl;
    for(auto e : edges_list){
        std::cout << "(" << e.Coor_pair.first.getX() << ", " << e.Coor_pair.first.getY() << ") ";
        std::cout << "(" << e.Coor_pair.second.getX() << ", " << e.Coor_pair.second.getY() << ")" << std::endl;
    }

    std::vector<edge<int>> edges_list2;
    poly.find_edges(poly.vertexes.begin(), edges_list2);
    std::cout << "edges in polygon that contains (0, 0): " << std::endl;
    for(auto e : edges_list2){
        std::cout << "(" << e.Coor_pair.first.getX() << ", " << e.Coor_pair.first.getY() << ") ";
        std::cout << "(" << e.Coor_pair.second.getX() << ", " << e.Coor_pair.second.getY() << ")" << std::endl;
    }

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
}

void test_Polygon_shrink()
{
    Polygon<int> poly;
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
    poly.edges_init();
    
    // Copy poly to poly_shrink
    Polygon<int> poly_shrink;
    poly_shrink.edges = poly.edges;
    poly_shrink.vertexes = poly.vertexes;

    std::cout << "Polygon before shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }

    Polygon_shrink(poly, poly_shrink);

    std::cout << "Polygon after shrink is " << std::endl;
    for(auto v: poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
}

void test_Edge_list_complement()
{

    Polygon<int> poly;
    poly.vertexes.push_back(Coor<int>(0, 0));
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
/*
    std::cout << "vertex in polygon after complement: " << std::endl;
    for(auto v : poly_complement.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
*/
}