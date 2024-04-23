#ifndef Polygon_hpp
#define Polygon_hpp

#include "Coor.hpp"
#include <vector>
#include <iostream>
#include <algorithm> 

template <typename T>
struct edge
{
    std::pair< Coor<T>, Coor<T> > Coor_pair;
    edge(const Coor<T>& a, const Coor<T>& b) : Coor_pair(a, b) {}
};

template <typename T>
void edge_complement(edge<T> e1, edge<T> e2, std::vector< edge<T> >& complement_edges)
{
    if(e1.Coor_pair.first == e2.Coor_pair.first)
    {
        complement_edges.push_back(edge<T>(e1.Coor_pair.second, e2.Coor_pair.second));
    }
    else if(e1.Coor_pair.first == e2.Coor_pair.second)
    {
        complement_edges.push_back(edge<T>(e1.Coor_pair.second, e2.Coor_pair.first));
    }
    else if(e1.Coor_pair.second == e2.Coor_pair.first)
    {
        complement_edges.push_back(edge<T>(e1.Coor_pair.first, e2.Coor_pair.second));
    }
    else if(e1.Coor_pair.second == e2.Coor_pair.second)
    {
        complement_edges.push_back(edge<T>(e1.Coor_pair.first, e2.Coor_pair.first));
    }
    else
    {
        
        if(
            //check the horizontal edge
            e1.Coor_pair.first.getY() == e1.Coor_pair.second.getY() &&
            e2.Coor_pair.first.getY() == e2.Coor_pair.second.getY()
        )
        {
            // sort the two edges —— first are the leftmost points
            if(e1.Coor_pair.first.getX() > e1.Coor_pair.second.getX())
            {
                std::swap(e1.Coor_pair.first, e1.Coor_pair.second);
            }
            if(e2.Coor_pair.first.getX() > e2.Coor_pair.second.getX())
            {
                std::swap(e2.Coor_pair.first, e2.Coor_pair.second);
            }
            // check if the two edges are intersected
            if(e1.Coor_pair.second.getX() < e2.Coor_pair.first.getX() || e2.Coor_pair.second.getX() < e1.Coor_pair.first.getX())
            {
                //throw std::invalid_argument("The two edges are not connected");
                complement_edges.push_back(e1);
                complement_edges.push_back(e2);
            }
            else
            {
                //complement_edges.push_back(edge<T>(e1.Coor_pair.first, e2.Coor_pair.first));
                //complement_edges.push_back(edge<T>(e1.Coor_pair.second, e2.Coor_pair.second));
            }
        }
        else if (
            //check the vertical edge
            e1.Coor_pair.first.getX() == e1.Coor_pair.second.getX() &&
            e2.Coor_pair.first.getX() == e2.Coor_pair.second.getX()
        )
        {
            // sort the two edges —— first are the bottommost points
            if(e1.Coor_pair.first.getY() > e1.Coor_pair.second.getY())
            {
                std::swap(e1.Coor_pair.first, e1.Coor_pair.second);
            }
            if(e2.Coor_pair.first.getY() > e2.Coor_pair.second.getY())
            {
                std::swap(e2.Coor_pair.first, e2.Coor_pair.second);
            }
            // check if the two edges are intersected
            if(e1.Coor_pair.second.getY() < e2.Coor_pair.first.getY() || e2.Coor_pair.second.getY() < e1.Coor_pair.first.getY())
            {
                //throw std::invalid_argument("The two edges are not connected");
                //complement_edges.push_back(e1);
                //complement_edges.push_back(e2);
            }
            else
            {
                complement_edges.push_back(edge<T>(e1.Coor_pair.first, e2.Coor_pair.first));
                complement_edges.push_back(edge<T>(e1.Coor_pair.second, e2.Coor_pair.second));
            }
        }
        else
        {
            throw std::invalid_argument("The two edges are not connected");
        }

    }
}

template <typename T>
struct Polygon_edge_collection
{
    std::vector< edge<T> > edges;
    std::vector< Coor<T> > vertices;

    void edges_sort();
    void edges_2_vertices();
    void add_horizontal_edge(edge<T> e);
    void add_vertical_edge(edge<T> e);
};

template <typename T>
void Polygon_edge_collection<T>::edges_2_vertices()
{
    vertices.clear();
    for(auto& e : edges)
    {
        vertices.push_back(e.Coor_pair.first);
        vertices.push_back(e.Coor_pair.second);
    }

    // remove the duplicate vertices
    vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());
}

template <typename T>
void Polygon_edge_collection<T>::add_horizontal_edge(edge<T> e)
{
    // chek if the edge is horizontal
    if(e.Coor_pair.first.getY() != e.Coor_pair.second.getY())
    {
        throw std::invalid_argument("The edge is not horizontal");
    }

    T add_edge_Y = e.Coor_pair.first.getY();

    // collect and remove all the horizontal edges in the polygon
    std::vector< edge<T> > horizontal_edges_in_polygon;
    for(auto iter = edges.begin(); iter != edges.end();){
        if(iter->Coor_pair.first.getY() == add_edge_Y && iter->Coor_pair.second.getY() == add_edge_Y)
        {
            horizontal_edges_in_polygon.push_back(*iter);
            iter = edges.erase(iter);
        }
        else{
            iter++;
        }
    }
    // sort the horizontal edges according to the min x-coordinate of first and second point
    std::sort(horizontal_edges_in_polygon.begin(), horizontal_edges_in_polygon.end(), 
        [](const edge<T>& a, const edge<T>& b){
            return std::min(a.Coor_pair.first.getX(), a.Coor_pair.second.getX()) < std::min(b.Coor_pair.first.getX(), b.Coor_pair.second.getX());
        });

#if 1
    std::cout << "e is " << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
    for(auto iter = horizontal_edges_in_polygon.begin(); iter != horizontal_edges_in_polygon.end(); iter++)
    {
        std::cout << "horizontal_edges_in_polygon is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
    }
#endif

    // complement the horizontal edge with the edges in the polygon
    std::vector< edge<T> > operation_edges;
    operation_edges.push_back(e);
    
    for(auto& horizontal_edge : horizontal_edges_in_polygon)
    {
        if(operation_edges.size() == 0)
        {
#if 1
            std::cout << "added edge is " << horizontal_edge.Coor_pair.first << " " << horizontal_edge.Coor_pair.second << std::endl;
#endif
            operation_edges.push_back(horizontal_edge);
            continue;
        }

        std::vector< edge<T> > complement_edges_collection;
        
        for(auto iter = operation_edges.begin(); iter != operation_edges.end();){
            std::vector< edge<T> > complement_edges;
            edge_complement(*iter, horizontal_edge, complement_edges);

#if 1
            std::cout << "iter is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
            std::cout << "horizontal_edge of operation is " << horizontal_edge.Coor_pair.first << " " << horizontal_edge.Coor_pair.second << std::endl;
            for(auto iter = complement_edges.begin(); iter != complement_edges.end(); iter++)
            {
                std::cout << "complement_edges is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
            }
            std::cout << "------" << std::endl;
#endif

            if(complement_edges.size() == 0){iter++;}
            else
            {
                complement_edges_collection.insert(complement_edges_collection.end(), complement_edges.begin(), complement_edges.end());
                iter = operation_edges.erase(iter);
            }
        }

        for(auto& complement_edge : complement_edges_collection)
        {
            // check the edge is not a ponit
            if(complement_edge.Coor_pair.first != complement_edge.Coor_pair.second)
            {
                operation_edges.push_back(complement_edge);
            }
        }
        complement_edges_collection.clear();
    }

    // add the complemented edges back to the polygon
    for(auto& edge : operation_edges)
    {
#if 1
        std::cout << "edge is " << edge.Coor_pair.first << " " << edge.Coor_pair.second << std::endl;
#endif
        edges.push_back(edge);
    }
    std::cout << "-------------------------------------------" << std::endl;
}

template <typename T>
void Polygon_edge_collection<T>::add_vertical_edge(edge<T> e)
{
    // chek if the edge is vertical
    if(e.Coor_pair.first.getX() != e.Coor_pair.second.getX())
    {
        throw std::invalid_argument("The edge is not vertical");
    }

    T add_edge_X = e.Coor_pair.first.getX();

    // collect and remove all the vertical edges in the polygon
    std::vector< edge<T> > vertical_edges_in_polygon;
    for(auto iter = edges.begin(); iter != edges.end();){
        if(iter->Coor_pair.first.getX() == add_edge_X && iter->Coor_pair.second.getX() == add_edge_X)
        {
            vertical_edges_in_polygon.push_back(*iter);
            iter = edges.erase(iter);
        }
        else{
            iter++;
        }
    }
    // sort the horizontal edges according to the min y-coordinate of first and second point
    std::sort(vertical_edges_in_polygon.begin(), vertical_edges_in_polygon.end(), 
        [](const edge<T>& a, const edge<T>& b){
            return std::min(a.Coor_pair.first.getY(), a.Coor_pair.second.getY()) < std::min(b.Coor_pair.first.getY(), b.Coor_pair.second.getY());
        });

#if 1
    std::cout << "e is " << e.Coor_pair.first << " " << e.Coor_pair.second << std::endl;
    for(auto iter = vertical_edges_in_polygon.begin(); iter != vertical_edges_in_polygon.end(); iter++)
    {
        std::cout << "vertical_edges_in_polygon is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
    }
#endif

    // complement the vertical edge with the edges in the polygon
    std::vector< edge<T> > operation_edges;
    operation_edges.push_back(e);
    
    for(auto vertical_edge : vertical_edges_in_polygon)
    {
        // if operation_edges is empty, then add remaining vertical edges to the operation_edges
        if(operation_edges.size() == 0)
        {
#if 1
            std::cout << "added edge is " << vertical_edge.Coor_pair.first << " " << vertical_edge.Coor_pair.second << std::endl;
#endif
            operation_edges.push_back(vertical_edge);
            continue;
        }

        std::vector< edge<T> > complement_edges_collection;
        
        for(auto iter = operation_edges.begin(); iter != operation_edges.end();){
            std::vector< edge<T> > complement_edges;
            edge_complement(*iter, vertical_edge, complement_edges);

#if 1
            std::cout << "iter is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
            std::cout << "vertical_edge of operation is " << vertical_edge.Coor_pair.first << " " << vertical_edge.Coor_pair.second << std::endl;
            for(auto iter = complement_edges.begin(); iter != complement_edges.end(); iter++)
            {
                std::cout << "complement_edges is " << iter->Coor_pair.first << " " << iter->Coor_pair.second << std::endl;
            }
            std::cout << "------" << std::endl;
#endif


            if(complement_edges.size() == 0){iter++;}
            else
            {
                complement_edges_collection.insert(complement_edges_collection.end(), complement_edges.begin(), complement_edges.end());
                iter = operation_edges.erase(iter);
            }
        }

        for(auto& complement_edge : complement_edges_collection)
        {
            // check the edge is not a ponit
            if(complement_edge.Coor_pair.first != complement_edge.Coor_pair.second)
            {
                operation_edges.push_back(complement_edge);
            }
        }
        complement_edges_collection.clear();
    }

    // add the complemented edges back to the polygon

    for(auto& edge : operation_edges)
    {
#if 1
        std::cout << "edge is " << edge.Coor_pair.first << " " << edge.Coor_pair.second << std::endl;
#endif
        edges.push_back(edge);
    }
    std::cout << "-------------------------------------------" << std::endl;
}

#endif