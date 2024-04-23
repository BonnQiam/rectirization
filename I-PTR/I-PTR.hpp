#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

#define debug_IPTR 1

template <typename T>
static auto findCoorTuple_4_I_PTR(std::list< Coor<T> >& polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>;

template <typename T>
static void updatePolygon_4_I_PTR(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm);

template <typename T, typename const_iterator>
void I_PTR(const const_iterator& first, const const_iterator& last, 
                    std::vector< Rect<T> >& result)
{
    std::list< Coor<T> > polygon(first, last);

    result.clear();

    //for(int i=0; i<5; ++i){
    while(polygon.size() > 2) {
        const auto& coor_tuple = findCoorTuple_4_I_PTR(polygon);

        const auto Pk = *(std::get<0>(coor_tuple));
        const auto Pl = *(std::get<1>(coor_tuple));
        const auto Pm = *(std::get<2>(coor_tuple));

        std::cout << "polygon before: " << std::endl;
        for (const auto& i : polygon) { std::cout << i << " " << std::endl; }

        std::cout << "Pk: " << Pk << std::endl;
        std::cout << "Pl: " << Pl << std::endl;
        std::cout << "Pm: " << Pm << std::endl;

        result.emplace_back(Pk.getX(), 
                                Pk.getY(), 
                                Pl.getX() - Pk.getX(), 
                                Pm.getY() - Pk.getY());

        updatePolygon_4_I_PTR(polygon, Pk, Pl, Pm);

        std::cout << "polygon after: " << std::endl;
        for (const auto& i : polygon) { std::cout << i << " " << std::endl; }

        std::cout << "===============================================" << std::endl;
    }
}

template <typename T>
static auto findCoorTuple_4_I_PTR(std::list< Coor<T> >& polygon) 
//static auto findCoorTuple_4_I_PTR(std::list< Coor<T> > polygon) 
    -> std::tuple<typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator, 
                    typename std::list< Coor<T> >::iterator>
{   
    while(1){
        // find Pk: the bottom and the left-most coordinate except P0
        auto P_0 = polygon.end();
        const auto Pk = std::min_element(polygon.begin(), polygon.end(), 
            [&P_0](const auto& lhs, const auto& rhs) -> bool {
                    // skip the element P0
                    if (lhs == (*P_0)) { 
                        return false; 
                        }
                    else if (rhs == (*P_0)) { 
                        return true; 
                        }
                    if (lhs.getY() != rhs.getY()) { 
                        return (lhs.getY() < rhs.getY()); 
                        }
                    else { 
                        return (lhs.getX() < rhs.getX()); 
                        }
                }
            );
        
        int count = 0;
        for(auto i=polygon.begin(); i!=polygon.end(); ++i){
            if(*i == *Pk){count++;}
        } 
        if(count == 2){
            polygon.remove(*Pk);
            continue;
        }
        else if (count > 2)
        {
            P_0 = Pk;
            continue;
        }
        
        // find Pl: the bottom and the left-most coordinate except Pk
        const auto Pl = std::min_element(polygon.begin(), polygon.end(), 
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

        // insert Pk-Pl or Pl-Pk into the polygon
        auto iter = polygon.begin();
        while(iter != polygon.end()) {
            auto iter_next = (std::next(iter) == polygon.end()) ? polygon.begin() : (std::next(iter));

            if(iter->getY() == iter_next->getY()) {
                if( (*iter == *Pk && *iter_next == *Pl) || 
                    (*iter == *Pl && *iter_next == *Pk) 
                ){break;}
                else{
                    if(*iter == *Pk && iter_next->getX() > Pl->getX()) {
                        std::cout << "insert Pl" << std::endl;
                        polygon.insert(iter_next, *Pl);
                        break;
                    }
                    else if(*iter == *Pl && iter_next->getX() < Pk->getX()){
                        std::cout << "insert Pk" << std::endl;
                        polygon.insert(iter_next, *Pk);
                        break;
                    }
                    else if(*iter_next == *Pk && iter->getX() > Pl->getX()) {
                        std::cout << "insert Pl" << std::endl;
                        polygon.insert(iter_next, *Pl);
                        break;
                    }
                    else if(*iter_next == *Pl && iter->getX() < Pk->getX()){
                        std::cout << "insert Pk" << std::endl;
                        polygon.insert(iter_next, *Pk);
                        break;
                    }
                }
            }
            iter++;
        }

        // find Pm
        const auto Pm = std::min_element(polygon.begin(), polygon.end(), 
            [&Pk, &Pl](const auto& lhs, const auto& rhs) -> bool {
                    // skip the element (x, y) out of the range:
                    // Pk.getX() <= x < Pl.getX() && Pk.getY() < y
                    if ((lhs.getY() <= Pk->getY()) || 
                        (lhs.getX() < Pk->getX()) || 
                        (lhs.getX() >= Pl->getX())) { 
                            return false; 
                        }
                    else if ((rhs.getY() <= Pk->getY()) || 
                            (rhs.getX() < Pk->getX()) || 
                            (rhs.getX() >= Pl->getX())) { 
                            return true; 
                        }
                    // find the smallest element
                    else if (lhs.getY() != rhs.getY()) {
                        return (lhs.getY() < rhs.getY()); 
                        }
                    else {
                        return (lhs.getX() < rhs.getX()); 
                    }
                    return true;
                }
            );

#if 0
        if(Pm->getY() == Pk->getY()){
            polygon.erase(Pk);
            continue;
        }
        else{
            return {Pk, Pl, Pm};
        }
#endif 
        return {Pk, Pl, Pm};
    }
}

template <typename T>
static void updatePolygon_4_I_PTR(std::list< Coor<T> >& polygon, 
                        const Coor<T>& Pk, const Coor<T>& Pl, const Coor<T>& Pm)
{
    const Coor<T> upl(Pk.getX(), Pm.getY()), upr(Pl.getX(), Pm.getY());

#if debug_IPTR
    std::cout << "upl: " << upl << std::endl;
    std::cout << "upr: " << upr << std::endl;
#endif
    auto iter = polygon.begin();

    bool insert_upr = true, insert_upl = true;
    bool remove_Pk  = true, remove_Pl  = true;

    auto iter_Pk = polygon.begin();
    auto iter_Pl = polygon.begin();
    bool Pk_Pl;
    
    while(iter != polygon.end()) {
        auto iter_next = (std::next(iter) == polygon.end()) ? polygon.begin() : (std::next(iter));
        auto iter_last = (iter == polygon.begin()) ? (std::prev(polygon.end())) : (std::prev(iter));

        if(*iter == upr) {
            insert_upr = false;
            // check special case
            if(
                ((iter->getY() - iter_last->getY()) < 0 && (iter_next->getX()-iter->getX()) > 0) ||
                ((iter->getX() - iter_last->getX()) < 0 && (iter_next->getY()-iter->getY()) > 0)
            ){insert_upr = true;}
        }
        else if(*iter == upl){
            insert_upl = false;
            // check special case
            if(
                ((iter->getX() - iter_last->getX()) > 0 && (iter_next->getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last->getY()) < 0 && (iter_next->getX()-iter->getX()) < 0)
            ){insert_upl = true;}            
        }
        else if(*iter == Pk){
            if(
                ((iter->getX() - iter_last->getX()) > 0 && (iter_next->getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last->getY()) < 0 && (iter_next->getX()-iter->getX()) < 0)
            ){remove_Pk = false;}
        }
        else if(*iter == Pl){
            if(
                ((iter->getX() - iter_last->getX()) < 0 && (iter_next->getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last->getY()) < 0 && (iter_next->getX()-iter->getX()) > 0)
            ){remove_Pl = false;}
        }
        if(*iter == Pk && *iter_next == Pl) {
            iter_Pk = iter;
            iter_Pl = iter_next;
            Pk_Pl = true;
        }
        else if(*iter == Pl && *iter_next == Pk) {
            iter_Pk = iter_next;
            iter_Pl = iter;
            Pk_Pl = false;
        }

        iter++;
    }

#if debug_IPTR
    std::cout << "insert_upl: " << insert_upl << std::endl;
    std::cout << "insert_upr: " << insert_upr << std::endl;
    std::cout << "remove_Pk: " << remove_Pk << std::endl;
    std::cout << "remove_Pl: " << remove_Pl << std::endl;
#endif

    if(Pk_Pl){
#if debug_IPTR
        std::cout << "Case 1: Pk-Pl" << std::endl;
#endif
        if(insert_upl && insert_upr){
#if debug_IPTR
            std::cout << "Insert Pk and Pl" << std::endl;
#endif
            iter_Pl = polygon.insert(polygon.insert(iter_Pl, upr), upl);
            iter_Pl = (std::next(iter_Pl) == polygon.end()) ? polygon.begin() : (std::next(iter_Pl));
            iter_Pl = (std::next(iter_Pl) == polygon.end()) ? polygon.begin() : (std::next(iter_Pl));
            
            if(remove_Pl){polygon.erase(iter_Pl);}
            if(remove_Pk){polygon.erase(iter_Pk);}
        }
        else if(insert_upl && !insert_upr){
            iter_Pl = polygon.insert(iter_Pl, upl);
            iter_Pl = (std::next(iter_Pl) == polygon.end()) ? polygon.begin() : (std::next(iter_Pl));
            
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}
            
            // remove upr
            auto iter_upr = (std::next(iter_Pl)==polygon.end()) ? polygon.begin() : (std::next(iter_Pl));
#if debug_IPTR
            std::cout << "iter_upr == upr: " << (*iter_upr == upr) << std::endl;
#endif
            polygon.erase(iter_upr);
        }
        else if(insert_upr && !insert_upl){
            iter_Pl = polygon.insert(iter_Pl, upr);
            iter_Pl = (std::next(iter_Pl) == polygon.end()) ? polygon.begin() : (std::next(iter_Pl));

            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}

            // remove upl
            auto iter_upl = (iter_Pk == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pk);
#if debug_IPTR
            std::cout << "iter_upl == upl: " << (*iter_upl == upl) << std::endl;
#endif
            polygon.erase(iter_upl);
        }
        else{
#if debug_IPTR
            std::cout << "Remove Pk and Pl" << std::endl;
#endif
            auto iter_Pl_next = (std::next(iter_Pl) == polygon.end()) ? polygon.begin() : (std::next(iter_Pl));
            if(remove_Pl){
                iter_Pl_next = polygon.erase(iter_Pl);
            }
            
            if(remove_Pk){
                iter_Pk = polygon.erase(iter_Pk);
            }
            auto iter_Pk_last = (iter_Pk == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pk);

            if(*iter_Pl_next == upr && *iter_Pk_last == upl){
                std::cout << "1" << std::endl;
                polygon.erase(iter_Pl_next);
                polygon.erase(iter_Pk_last);
            }
            else if(*iter_Pl_next == upr && !(*iter_Pk_last == upl)){
                std::cout << "2" << std::endl;
                iter_Pl_next = polygon.erase(iter_Pl_next);// remove upr
                polygon.erase(iter_Pl_next); // remove upl
            }
            else if(!(*iter_Pl_next == upr) && *iter_Pk_last == upl){
                std::cout << "3" << std::endl;
                auto iter_Pk_last_last = (iter_Pk_last == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pk_last);
                polygon.erase(iter_Pk_last);
                polygon.erase(iter_Pk_last_last);
            }                
        }
    }
    else{
#if debug_IPTR
        std::cout << "Case 2: Pl-Pk" << std::endl;
#endif
        if(insert_upl && insert_upr){
#if debug_IPTR
            std::cout << "Insert Pk and Pl" << std::endl;
#endif
            iter_Pk = polygon.insert(polygon.insert(iter_Pk, upl), upr);
            iter_Pk = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));
            iter_Pk = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));

            if(remove_Pk){polygon.erase(iter_Pk);}
            if(remove_Pl){polygon.erase(iter_Pl);}
        }
        else if(insert_upl && !insert_upr){
            iter_Pk = polygon.insert(iter_Pk, upl);
            iter_Pk = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));

            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}

            // remove upr
            auto iter_upr = (iter_Pl == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pl);
#if debug_IPTR
            std::cout << "iter_upr == upr: " << (*iter_upr == upr) << std::endl;
#endif
            polygon.erase(iter_upr);
        }
        else if(insert_upr && !insert_upl){
            iter_Pk = polygon.insert(iter_Pk, upr);
            iter_Pk = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));

            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}

            // remove upl
            auto iter_upl = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));
#if debug_IPTR
            std::cout << "iter_upl == upl: " << (*iter_upl == upl) << std::endl;
#endif
            polygon.erase(iter_upl);
        }
        else{
#if debug_IPTR
            std::cout << "Remove Pk and Pl" << std::endl;
#endif
            auto iter_Pk_next = (std::next(iter_Pk) == polygon.end()) ? polygon.begin() : (std::next(iter_Pk));
            if(remove_Pk){
                iter_Pk_next = polygon.erase(iter_Pk);
            }
            
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            auto iter_Pl_last = (iter_Pl == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pl);

            if(*iter_Pk_next == upl && *iter_Pl_last == upr){
                std::cout << "1" << std::endl;
                polygon.erase(iter_Pk_next);
                polygon.erase(iter_Pl_last);
            }
            else if(*iter_Pk_next == upl && !(*iter_Pl_last == upr)){
                std::cout << "2" << std::endl;
                iter_Pk_next = polygon.erase(iter_Pk_next);// remove upl
                polygon.erase(iter_Pk_next); // remove upr
            }
            else if(!(*iter_Pk_next == upr) && *iter_Pl_last == upl){
                std::cout << "3" << std::endl;
                auto iter_Pl_last_last = (iter_Pl_last == polygon.begin()) ? std::prev(polygon.end()) : std::prev(iter_Pl_last);
                polygon.erase(iter_Pl_last);
                polygon.erase(iter_Pl_last_last);
            }                
        }
    }
 }