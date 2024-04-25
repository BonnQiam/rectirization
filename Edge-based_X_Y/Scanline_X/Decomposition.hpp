#ifndef Decomposition_hpp
#define Decomposition_hpp

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <tuple>
#include <algorithm>

#include "Polygon.hpp"
#include "Rectangle.hpp"

template <typename T>
static auto findCoorTuple_4_I_PTR(std::vector< Coor<T> >& vertices) // if not using the reference, the vertices will be changed
    -> std::tuple<typename std::vector< Coor<T> >::iterator, 
                    typename std::vector< Coor<T> >::iterator, 
                    typename std::vector< Coor<T> >::iterator>;


template <typename T, typename const_iterator>
void Edge_based_decomposition(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    result.clear();
    std::vector< Coor<T> > polygon(first, last);
    //establish the Polygon_edge_collection
    Polygon_edge_collection<T> Polygon_edges;
    for(auto it = polygon.begin(); it != polygon.end(); it++)
    {
        auto next = (std::next(it) == polygon.end()) ? polygon.begin() : std::next(it);
        Polygon_edges.edges.push_back(edge<T>(*it, *next));
    }
    Polygon_edges.edges_2_vertices();

#if 0
    //display the edges
    std::cout << "Edges: " << std::endl;
    for(auto iter = Polygon_edges.edges.begin(); iter != Polygon_edges.edges.end(); iter++)
    {
        std::cout << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
    }   
#endif

    while (Polygon_edges.edges.size()>1)
    //for(int i=0; i<5; ++i)
    //for(int i=0; i<1188; ++i)
    {
        const auto& coor_tuple = findCoorTuple_4_I_PTR(Polygon_edges.vertices);
        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

//        std::cout << "i: " << i << std::endl;
        std::cout << "Pk: " << Pk << std::endl;
        std::cout << "Pl: " << Pl << std::endl;
        std::cout << "Pm: " << Pm << std::endl;
        std::cout << "----------------------------------------------------------" << std::endl;

        result.emplace_back(Pk.getX(), 
                                Pk.getY(), 
                                Pl.getX() - Pk.getX(), 
                                Pm.getY() - Pk.getY());

        // Upl and Upr
        Coor<T> upl(Pk.getX(), Pm.getY()), upr(Pl.getX(), Pm.getY());
        
        // edges of the rectangle
        edge<T> e1(Pk, upl), e2(upl, upr), e3(upr, Pl), e4(Pl, Pk);
        // add to the Polygon_edges.edges

        edge_list_edge_complement<T>(Polygon_edges.edges, e1, VERTICAL);
        edge_list_edge_complement<T>(Polygon_edges.edges, e2, HORIZONTAL);
        edge_list_edge_complement<T>(Polygon_edges.edges, e3, VERTICAL);
        edge_list_edge_complement<T>(Polygon_edges.edges, e4, HORIZONTAL);
#if 0
        if(i >= 1){
            edge_list_edge_complement<T>(Polygon_edges.edges, e1, VERTICAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e2, HORIZONTAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e3, VERTICAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e4, HORIZONTAL);
        }
        else{
            edge_list_edge_complement<T>(Polygon_edges.edges, e1, VERTICAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e2, HORIZONTAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e3, VERTICAL);
            edge_list_edge_complement<T>(Polygon_edges.edges, e4, HORIZONTAL);
        }
#endif
        Polygon_edges.edges_2_vertices();

#if 1
        //output to Edge.txt
        std::ofstream outfile("Edge.txt");
        //clear the file
        outfile.clear();
        for(auto iter = Polygon_edges.edges.begin(); iter != Polygon_edges.edges.end(); iter++)
        {
            outfile << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
        }
        outfile.close();
#endif

#if 0
        //display the edges
        std::cout << "Edges: " << std::endl;
        for(auto iter = Polygon_edges.edges.begin(); iter != Polygon_edges.edges.end(); iter++)
        {
            std::cout << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
        }
        // display the vertices
        std::cout << "Vertices: " << std::endl;
        for(auto iter = Polygon_edges.vertices.begin(); iter != Polygon_edges.vertices.end(); iter++)
        {
            std::cout << *iter << std::endl;
        }

        std::cout << "----------------------------------------------------------" << std::endl;
#endif
    }   
}


/***********************************************************************/

template <typename T>
static auto findCoorTuple_4_I_PTR(std::vector< Coor<T> >& vertices) 
    -> std::tuple<typename std::vector< Coor<T> >::iterator, 
                    typename std::vector< Coor<T> >::iterator, 
                    typename std::vector< Coor<T> >::iterator>
{
    // find Pk: the bottom and the left-most coordinate
    const auto Pk = std::min_element(vertices.begin(), vertices.end(), 
        [](const auto& lhs, const auto& rhs) -> bool {
                if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                    }
            }
        );
    // find Pl: the bottom and the left-most coordinate except Pk
    const auto Pl = std::min_element(vertices.begin(), vertices.end(), 
        [&Pk](const auto& lhs, const auto& rhs) -> bool {
                // skip the element Pk
                if (lhs == (*Pk)) { 
                    return false; 
                    }
                else if (rhs == (*Pk)) { 
                    return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { 
                    return (lhs.getX() < rhs.getX()); 
                }
            }
        );

    // find Pm
    const auto Pm = std::min_element(vertices.begin(), vertices.end(), 
        [&Pk, &Pl](const auto& lhs, const auto& rhs) -> bool {
                // skip the element (x, y) out of the range:
                // Pk.getX() <= x < Pl.getX() && Pk.getY() < y
                if ((lhs.getY() <= Pk->getY()) || 
                    (lhs.getX() < Pk->getX()) || 
                    //(lhs.getX() >= Pl->getX())) {
                    (lhs.getX() > Pl->getX())) {
                        return false; 
                    }
                else if ((rhs.getY() <= Pk->getY()) || 
                        (rhs.getX() < Pk->getX()) || 
                        //(rhs.getX() >= Pl->getX())) {
                        (rhs.getX() > Pl->getX())) {  
                            return true; 
                    }
                // find the smallest element
                else if (lhs.getY() != rhs.getY()) { 
                    return (lhs.getY() < rhs.getY()); 
                    }
                else { return (lhs.getX() < rhs.getX()); }
                
                return true;
            }
        );

    return {Pk, Pl, Pm};
}

#endif