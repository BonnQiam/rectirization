#ifndef Polygon_hpp
#define Polygon_hpp

#include "Coor.hpp"

template <typename T>
struct edge
{
    std::pair< Coor<T>, Coor<T> > edge;
    edge(const Coor<T>& a, const Coor<T>& b){
        if(a.getX() < b.getX()){
            edge.first = a;
            edge.second = b;
        }
        else if(a.getX() > b.getX()){
            edge.first = b;
            edge.second = a;
        }
        else{
            if(a.getY() < b.getY()){
                edge.first = a;
                edge.second = b;
            }
            else{
                edge.first = b;
                edge.second = a;
            }
        }
    }
};

template <typename T>
struct Polygon
{   
    // vertexes set of the polygon
    std::vector<Coor<T>> vertexes;
    // edges set of the polygon
    std::vector<edge<T>> edges;

    void find_edges(const Coor<T> vertex, std::vector<edge<T>> &edges);
};

#endif