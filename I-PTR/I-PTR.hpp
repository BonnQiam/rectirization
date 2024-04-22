#include "Rectangle.hpp"

#include <vector>
#include <list>
#include <tuple>
#include <algorithm>

#define debug_IPTR 1

template <typename T>
static auto findCoorTuple__4_I_PTR(std::list< Coor<T> >& polygon) 
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
        // find Pk: the bottom and the left-most coordinate
        const auto Pk = std::min_element(polygon.begin(), polygon.end(), 
            [](const auto& lhs, const auto& rhs) -> bool {
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
            if(count > 1){
                polygon.erase(i);
            }
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
        if(Pm->getY() == Pk->getY()){
            polygon.erase(Pk);
            continue;
        }
        else{
            return {Pk, Pl, Pm};
        }
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
        Coor<T> iter_last = (iter == polygon.begin()) ? polygon.back() : *(std::prev(iter));
        
        Coor<T> iter_next = (std::next(iter) == polygon.end()) ? polygon.front() : *(std::next(iter));

        if(*iter == upr) {
            insert_upr = false;
            // check special case
            if(
                ((iter->getY() - iter_last.getY()) < 0 && (iter_next.getX()-iter->getX()) > 0) ||
                ((iter->getX() - iter_last.getX()) < 0 && (iter_next.getY()-iter->getY()) > 0)
            ){insert_upr = true;}
        }
        else if(*iter == upl){
            insert_upl = false;
            // check special case
            if(
                ((iter->getX() - iter_last.getX()) > 0 && (iter_next.getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last.getY()) < 0 && (iter_next.getX()-iter->getX()) < 0)
            ){insert_upl = true;}            
        }
        else if(*iter == Pk){
            if(
                ((iter->getX() - iter_last.getX()) > 0 && (iter_next.getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last.getY()) < 0 && (iter_next.getX()-iter->getX()) < 0)
            ){remove_Pk = false;}
        }
        else if(*iter == Pl){
            if(
                ((iter->getX() - iter_last.getX()) < 0 && (iter_next.getY()-iter->getY()) > 0) ||
                ((iter->getY() - iter_last.getY()) < 0 && (iter_next.getX()-iter->getX()) > 0)
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
        if(insert_upl && insert_upr){
            iter_pl = polygon.insert(polygon.insert(iter_Pl, upr), upl)
            iter_pl = ((iter_Pl+2) == polygon.end()) ? polygon.begin() : (iter_Pl+2);
            
            if(remove_Pl){polygon.erase(iter_Pl);}
            if(remove_Pk){polygon.erase(iter_Pk);}
        }
        else if(insert_upl && !insert_upr){
            iter_Pl = polygon.insert(iter_Pl, upl);
            iter_Pl = ((iter+1) == polygon.end()) ? polygon.begin() : (iter+1);
            
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}
            
            // remove upr
            while(1){
                if(*iter_Pk == upr){
                    polygon.erase(iter_Pk);
                    break;
                }
                else if (*iter_Pl == upr){
                    polygon.erase(iter_Pl);
                    break;
                }
                else{
                    iter_Pk = (iter_Pk == polygon.begin()) ? (polygon.end(-1)) : (iter_Pk-1);// polygon.end(-1) means the last element
                    iter_Pl = ((iter_Pl+1) == polygon.end()) ? polygon.begin() : (iter_Pl+1);
                }
            }

        }
        else if(insert_upr && !insert_upl){
            iter_Pl = polygon.insert(iter_Pl, upr);
            iter_Pl = ((iter+1) == polygon.end()) ? polygon.begin() : (iter+1);

            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}

            // remove upl
            while(1){
                if(*iter_Pk == upl){
                    polygon.erase(iter_Pk);
                    break;
                }
                else if (*iter_Pl == upl){
                    polygon.erase(iter_Pl);
                    break;
                }
                else{
                    iter_Pk = (iter_Pk == polygon.begin()) ? (polygon.end(-1)) : (iter_Pk-1);
                    iter_Pl = ((iter_Pl+1) == polygon.end()) ? polygon.begin() : (iter_Pl+1);
                }
            }
        }
        else{
            if(remove_Pl){iter_Pl = polygon.erase(iter_Pl);}
            if(remove_Pk){iter_Pk = polygon.erase(iter_Pk);}

            // remove upl and upr
            bool remove_upl_flag = false, remove_upr_flag = false;
            while(1){
                // wait 
            }
        }
    }
    

    

}