#ifndef Polygon_hpp
#define Polygon_hpp

#include "Coor.hpp"
#include <vector>
#include <iostream>
#include <algorithm> 

#define OVERLAP_Full    0
#define OVERLAP_Partial 1
#define OVERLAP_None    2

template <typename T>
struct edge
{
    std::pair< Coor<T>, Coor<T> > Coor_pair;
    edge(const Coor<T>& a, const Coor<T>& b) : Coor_pair(a, b) {}
};

template <typename T>
int after_overlapped(edge<T>& e1, edge<T>& e2){
    // remove the overlapped part of e1 and e2 from e1 and e2

    // if e1, e2 are horizontal edges
    if(e1.Coor_pair.first.getY() == e1.Coor_pair.second.getY() && 
        e2.Coor_pair.first.getY() == e2.Coor_pair.second.getY()){
        // sort the e1 and e2, so that first point of e1/e2 is the leftmost point
        if(e1.Coor_pair.first.getX() > e1.Coor_pair.second.getX()){
            std::swap(e1.Coor_pair.first, e1.Coor_pair.second);
        }
        if(e2.Coor_pair.first.getX() > e2.Coor_pair.second.getX()){
            std::swap(e2.Coor_pair.first, e2.Coor_pair.second);
        }
        //check if e1 and e2 overlap
        if(e1.Coor_pair.second.getX() < e2.Coor_pair.first.getX() || 
            e2.Coor_pair.second.getX() < e1.Coor_pair.first.getX()){
            //do nothing
            return OVERLAP_None;
        }
        else{
            // if e1 and e2 overlap, remove the overlapped part
            Coor<T> tmp = e1.Coor_pair.second;
            e1.Coor_pair.second = e2.Coor_pair.first;
            e2.Coor_pair.first = tmp;

            if(e1.Coor_pair.first == e1.Coor_pair.second){
                return OVERLAP_Full;
            }
            else{
                return OVERLAP_Partial;
            }
        }
    }
    // if e1, e2 are vertical edges
    else if(e1.Coor_pair.first.getX() == e1.Coor_pair.second.getX() && 
        e2.Coor_pair.first.getX() == e2.Coor_pair.second.getX()){
        // sort the e1 and e2, so that first point of e1/e2 is the bottommost point
        if(e1.Coor_pair.first.getY() > e1.Coor_pair.second.getY()){
            std::swap(e1.Coor_pair.first, e1.Coor_pair.second);
        }
        if(e2.Coor_pair.first.getY() > e2.Coor_pair.second.getY()){
            std::swap(e2.Coor_pair.first, e2.Coor_pair.second);
        }
        //check if e1 and e2 overlap
        if(e1.Coor_pair.second.getY() < e2.Coor_pair.first.getY() || 
            e2.Coor_pair.second.getY() < e1.Coor_pair.first.getY()){
            //do nothing
            return OVERLAP_None;
        }
        else{
            // if e1 and e2 overlap, remove the overlapped part
            Coor<T> tmp = e1.Coor_pair.second;
            e1.Coor_pair.second = e2.Coor_pair.first;
            e2.Coor_pair.first = tmp;

            if(e1.Coor_pair.first == e1.Coor_pair.second){
                return OVERLAP_Full;
            }
            else{
                return OVERLAP_Partial;
            }
        }
    }
}

template <typename T>
void edge_list_edge_complement(std::vector< edge<T> >& edge_list, 
                    edge<T> e2)
{
    // If the e2 overlap with some edges of edge_list, the overlapped parts of these edges should be removed, and the remaining parts (not exist in the edge_list) of e2 should be added into the edge_list.
    for(auto iter = edge_list.begin(); iter != edge_list.end(); )
    {
        // calculate the overlapped part of e2 and *iter
        edge<T> e1 = *iter;
        int flag = after_overlapped(e1, e2);
        if(flag == OVERLAP_Full){
            // remove the overlapped edge
            iter = edge_list.erase(iter);
            break;
        }
        else if(flag == OVERLAP_Partial){
            // remove the overlapped edge
            iter = edge_list.erase(iter);
            // add the remaining part of e1 into the edge_list
            edge_list.push_back(e1);
        }
        else if(iter == edge_list.end() && flag == OVERLAP_None){
            // add the e2 into the edge_list
            edge_list.push_back(e2);
        }
        else{
            ++iter;
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

}

template <typename T>
void Polygon_edge_collection<T>::add_vertical_edge(edge<T> e)
{

}

#endif