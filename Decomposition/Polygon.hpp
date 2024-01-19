#ifndef Polygon_hpp
#define Polygon_hpp

#include "Coor.hpp"
#include <vector>

/************************************************************
 * Edge Definition
*/
template <typename T>
struct edge
{
    std::pair< Coor<T>, Coor<T> > Coor_pair;
    edge(const Coor<T>& a, const Coor<T>& b) : Coor_pair(a, b) {}
/*
    edge(const Coor<T>& a, const Coor<T>& b){
        if(a.getX() < b.getX()){
            Coor_pair.first = a;
            Coor_pair.second = b;
        }
        else if(a.getX() > b.getX()){
            Coor_pair.first = b;
            Coor_pair.second = a;
        }
        else{
            if(a.getY() < b.getY()){
                Coor_pair.first = a;
                Coor_pair.second = b;
            }
            else{
                Coor_pair.first = b;
                Coor_pair.second = a;
            }
        }
    }
*/
};
/************************************************************
 * Polygon Definition
*/
template <typename T>
struct Polygon
{   
    // vertexes set of the polygon
    std::vector<Coor<T>> vertexes;
    // edges set of the polygon
    std::vector<edge<T>> edges;

    void edges_init(); // according to vertexes, initialize edges
    void vertexes_init(); // according to edges, initialize vertexes

    void find_edges(const Coor<T> vertex, std::vector<edge<T>> &edges_list);
    void find_edges(const typename std::vector<Coor<T>>::iterator vertex, std::vector<edge<T>> &edges_list);
};

template <typename T>
void Polygon<T>::edges_init()
{
    edges.clear();
    auto vertex = vertexes.begin();
    for(; vertex != (vertexes.end()-1); vertex++){
        edges.push_back(edge<T>(*vertex, *(vertex+1)));
    } 
}

template <typename T>
void Polygon<T>::vertexes_init()
{
    vertexes.clear();
    auto edge = edges.begin();
    for(; edge != edges.end(); edge++){
        vertexes.push_back(edge->Coor_pair.first);
    }
    vertexes.push_back(edges.back().Coor_pair.second);
}

template <typename T>
void Polygon<T>::find_edges(const Coor<T> vertex, std::vector<edge<T>> &edges_list)
{
    auto edge = edges.begin();
    for(; edge != edges.end(); edge++){
        if(edge->Coor_pair.first == vertex || edge->Coor_pair.second == vertex){
            edges_list.push_back(*edge);
        }
    }
}

template <typename T>
void Polygon<T>::find_edges(const typename std::vector<Coor<T>>::iterator vertex, std::vector<edge<T>> &edges_list)
{
    auto edge = edges.begin();
    for(; edge != edges.end(); edge++){
        if(edge->Coor_pair.first == *vertex || edge->Coor_pair.second == *vertex){
            edges_list.push_back(*edge);
        }
    }
}

/**************************************************************************************
 * remove the redundancy point in the polygon
*/
template <typename T>
void Polygon_shrink_redundancy_point(const Polygon<T> &polygon,  Polygon<T> &polygon_shrink)
{
    auto v = polygon_shrink.vertexes.begin() + 1;

    for(auto e = polygon.edges.begin(); ; e++){
        auto e_nxt = ( (e+1) == polygon.edges.end() ) ? polygon.edges.begin() : (e+1);

        bool find_duplicate = false;

        T e_X     = e->Coor_pair.second.getX() - e->Coor_pair.first.getX();
        T e_nxt_X = e_nxt->Coor_pair.second.getX() - e_nxt->Coor_pair.first.getX();
        
        T e_Y     = e->Coor_pair.second.getY() - e->Coor_pair.first.getY();
        T e_nxt_Y = e_nxt->Coor_pair.second.getY() - e_nxt->Coor_pair.first.getY();

        if(
            (e->Coor_pair.second.getY() == e->Coor_pair.first.getY() ) &&
            (e_nxt->Coor_pair.second.getY() == e_nxt->Coor_pair.first.getY() )
        ){
            if(e_X*e_nxt_X > 0)
                find_duplicate = true;
        }
        else if ( (e->Coor_pair.second.getX() == e->Coor_pair.first.getX() ) &&
            (e_nxt->Coor_pair.second.getX() == e_nxt->Coor_pair.first.getX() )
        ){
            if(e_Y*e_nxt_Y > 0)
                find_duplicate = true;
        }

        if (find_duplicate)
        {
            if((e+1) == polygon.edges.end()){
                polygon_shrink.vertexes.erase(v);
                polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
                break;
            }
            else{
                polygon_shrink.vertexes.erase(v);
                e = e+1;
                v = v+1;
                if(e == (polygon.edges.end()-1))
                    break;
                continue;
            }
        }
        v=v+1;

        if( (e+1) == polygon.edges.end() )
            break;
    }
    polygon_shrink.edges_init();
}

/****************************************************************************************
 * remove the redundancy edge in the polygon
*/
template <typename T>
void Polygon_shrink_redundancy_edge(const Polygon<T> &polygon,  Polygon<T> &polygon_shrink)
{
    auto v = polygon_shrink.vertexes.begin() + 1;

    for(auto e = polygon.edges.begin(); ; e++){
        auto e_nxt = ( (e+1) == polygon.edges.end() ) ? polygon.edges.begin() : (e+1);
        
//        std::cout << "e is " << e->Coor_pair.first << " -> " << e->Coor_pair.second << std::endl;
//        std::cout << "e_nxt is " << e_nxt->Coor_pair.first << " -> " << e_nxt->Coor_pair.second << std::endl;
//        std::cout << "v is " << *v << std::endl;

        // e and e_nxt area horizontal edges
        bool find_duplicate = false;

        T e_X     = e->Coor_pair.second.getX() - e->Coor_pair.first.getX();
        T e_nxt_X = e_nxt->Coor_pair.second.getX() - e_nxt->Coor_pair.first.getX();
        
        T e_Y     = e->Coor_pair.second.getY() - e->Coor_pair.first.getY();
        T e_nxt_Y = e_nxt->Coor_pair.second.getY() - e_nxt->Coor_pair.first.getY();
        
        if(
            (e->Coor_pair.second.getY() == e->Coor_pair.first.getY() ) &&
            (e_nxt->Coor_pair.second.getY() == e_nxt->Coor_pair.first.getY() )
        ){
            if(e_X*e_nxt_X < 0)
                find_duplicate = true;
        }
        else if ( (e->Coor_pair.second.getX() == e->Coor_pair.first.getX() ) &&
            (e_nxt->Coor_pair.second.getX() == e_nxt->Coor_pair.first.getX() )
        ){
            if(e_Y*e_nxt_Y < 0)
                find_duplicate = true;
        }

        if(find_duplicate){
            T v_NewX  = e_nxt->Coor_pair.second.getX();
            T v_NewY  = e_nxt->Coor_pair.second.getY();

            if( (v_NewX == e->Coor_pair.first.getX()) && (v_NewY == e->Coor_pair.first.getY()) ){
                if((e+1) == polygon.edges.end()){
                    polygon_shrink.vertexes.erase(v);
                    polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
                    break;
                }
                else{
                    polygon_shrink.vertexes.erase(v);
                    polygon_shrink.vertexes.erase(v);

                    e = e+1;
                    if(e == (polygon.edges.end()-1))
                        break;
                    continue;
                }
            }
            else{
                if((e+1) == polygon.edges.end()){

                    *(polygon_shrink.vertexes.end()-1) = *(polygon_shrink.vertexes.begin()+1);
                    polygon_shrink.vertexes.erase(polygon_shrink.vertexes.begin());
                    break;
                }
                else{
                    polygon_shrink.vertexes.erase(v);

                    e = e+1;
                    v = v+1;
                    if(e == (polygon.edges.end()-1))
                        break;
                    continue;
                }
            }
        }

        v=v+1;

        if( (e+1) == polygon.edges.end() )
            break;
    }
        
    polygon_shrink.edges_init();
}

/***************************************************************************************
 * Edge complement operation
*/

template <typename T>
void Edge_list_complement(
    const Polygon<T> &polygon,
    const Polygon<T> &rectangle, // Pk -> Pl -> Upr -> Upl -> Pk
    Polygon<T> &polygon_complement)
{
    Coor<T> Pk  = rectangle.vertexes[0];
    Coor<T> Pl  = rectangle.vertexes[1];
    Coor<T> Upr = rectangle.vertexes[2];
    Coor<T> Upl = rectangle.vertexes[3];

//    std::cout << "Pk is " << Pk << std::endl;
//    std::cout << "Pl is " << Pl << std::endl;
//    std::cout << "Upr is " << Upr << std::endl;
//    std::cout << "Upl is " << Upl << std::endl;

    /***********************************************************************************
     * complement edges step 0: remove all redundancy points in polygon
     */
    Polygon<T> polygon_tmp = polygon;
    polygon_tmp.vertexes = polygon.vertexes;
    polygon_tmp.edges = polygon.edges;

    Polygon_shrink_redundancy_point(polygon, polygon_tmp);

    std::cout << "Polygon_tmp is " << std::endl;
    for(auto v : polygon_tmp.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }

    /***********************************************************************************
     * complement edges step 1: remove Pk-Pl and collect all other edges in polygon and rectangle
     */
    // find Pi->Pk, Pk -> Pl, Pl->Pj edges in polygon
    auto itr_kl = polygon_tmp.edges.begin();
    edge<T> edge_ik = *itr_kl;
    edge<T> edge_lj = *itr_kl;

    for(; itr_kl != polygon_tmp.edges.end(); itr_kl++){
        if(itr_kl->Coor_pair.first == Pk && itr_kl->Coor_pair.second == Pl){
            break;
        }
        if( (itr_kl+1) == polygon_tmp.edges.end()){
            std::cout << "Error: Pk -> Pl edge not found in polygon" << std::endl;
            return;
        }
    }

    if(itr_kl == polygon_tmp.edges.begin()){
//        std::cout << "Case 1:" << std::endl;
        edge_ik = *(polygon_tmp.edges.end()-1);
        edge_lj = *(polygon_tmp.edges.begin()+1);
    }
    else if(itr_kl == polygon_tmp.edges.end()-1){
//        std::cout << "Case 2:" << std::endl;
        edge_ik = *(polygon_tmp.edges.end()-2);
        edge_lj = *(polygon_tmp.edges.begin());
    }
    else{
//        std::cout << "Case 3:" << std::endl;
        edge_ik = *(itr_kl - 1);
        edge_lj = *(itr_kl + 1);
    }

    // remove Pk-Pl and collect all other edges in polygon and rectangle
    for(auto e = polygon_tmp.edges.begin(); e != polygon_tmp.edges.end(); e++){
        if(e == itr_kl){
            polygon_complement.edges.push_back(edge<T>(Pk, Upl));
            polygon_complement.edges.push_back(edge<T>(Upl, Upr));
            polygon_complement.edges.push_back(edge<T>(Upr, Pl));
        }
        else
            polygon_complement.edges.push_back(*e);
    }
    polygon_complement.vertexes_init();

    std::cout << "Before shrink, polygon_complement is " << std::endl;
    for(auto v : polygon_complement.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }

   /**********************************************************************************
     * complement egdes step 2: 
    */ 
    
    Polygon<int> poly_shrink;
    poly_shrink.vertexes = polygon_complement.vertexes;

    Polygon_shrink_redundancy_edge(polygon_complement, poly_shrink);

    std::cout << "After shrink, polygon_complement is " << std::endl;
    for(auto v : poly_shrink.vertexes){
        std::cout << "(" << v.getX() << ", " << v.getY() << ")" << std::endl;
    }
}

#endif