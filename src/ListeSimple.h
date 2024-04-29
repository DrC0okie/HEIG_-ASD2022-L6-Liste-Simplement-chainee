/*-----------------------------------------------------------------------------------
File name : ListeSimple.h
Author(s) : G. Courbat, J. Streckeisen, T. Van Hove
Creation date : 05.05.2022
Description : Implementation of custom forward list (passed cc1 & cc2 successfully)
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/

#ifndef LISTE_H
#define LISTE_H

#include "iostream"
#include "LSIterator.h"
#include <utility> // std::swap;

template<typename T>
class ListeSimple {
public:
   using value_type = T;
   using reference = T &;
   using const_reference = T const &;
   using iterator = LSIterator<value_type>;
   using const_iterator = LSConstIterator<value_type>;

   friend iterator;
   friend const_iterator;

   friend std::ostream &operator<<(std::ostream &s, const ListeSimple<T> &l) {
      Maillon *courant = l.cbegin();
      while (courant != nullptr) {
         std::cout << courant->valeur;
         courant = courant->suivant;
      }
      std::cout << "\n";
      return l;
   }

   ListeSimple() : avant_premier{value_type{}, nullptr} {}

   ListeSimple(const ListeSimple &ls) {
      iterator self = (&avant_premier);
      for (const_iterator other = ls.begin(); other != ls.end(); other++, self++) {
         insert_after(self,other.m->valeur);
      }
      // Le dernier maillon doit pointer sur nullptr
      self.m->suivant = nullptr;
   }

   ~ListeSimple()
   {
      while(!empty())
         pop_front();
   }

   ListeSimple &operator=(const ListeSimple &ls) {
      if (this != &ls) {
         ListeSimple tmp(ls);
         swap(tmp);
      }
      return *this;
   }

   iterator before_begin() noexcept { return iterator(&avant_premier); }

   const_iterator before_begin() const noexcept { return cbefore_begin();}

   const_iterator cbefore_begin() const noexcept {
      return const_iterator(&avant_premier);
   }

   iterator begin() noexcept {return iterator(avant_premier.suivant);}

   const_iterator begin() const noexcept {return cbegin();}

   const_iterator cbegin() const noexcept {
      return const_iterator(avant_premier.suivant);
   }

   const_iterator cend() const noexcept {return const_iterator(nullptr);}

   iterator end() noexcept {return iterator(nullptr);}

   const_iterator end() const noexcept {return cend();}

   bool empty() const noexcept {return avant_premier.suivant == nullptr;}

   reference front() {return avant_premier.suivant->valeur;}

   const_reference front() const {return avant_premier.suivant->valeur;}

   void push_front(const_reference v) {insert_after(before_begin(), v);}

   void pop_front() {erase_after(before_begin());}

   void insert_after(iterator it, const_reference v) {
      it.m->suivant = new Maillon{v, it.m->suivant};
   }

   void erase_after(iterator it) {
      iterator tmp = it.m->suivant;
      it.m->suivant = tmp.m->suivant;
      delete tmp.m;
   }

   void splice_after(iterator it, iterator debut, iterator fin) {
      if (debut != fin) {
         std::swap(fin.m->suivant, it.m->suivant);
         std::swap(it.m->suivant, debut.m->suivant);
      }
   }

   void sort() {
      for (iterator i = begin(); i.m->suivant != nullptr; ++i) {
         for (iterator j = iterator(&avant_premier);
              j.m->suivant->suivant != nullptr; ++j) {
            Maillon *tmp = j.m;
            iterator suivant = j;
            ++suivant;
            if (tmp->suivant->valeur > tmp->suivant->suivant->valeur) {
               splice_after(suivant, j, suivant++);
            }
         }
      }
   }

private:
   struct Maillon {
      value_type valeur;
      Maillon *suivant;
   };

   Maillon avant_premier;
   void swap(ListeSimple &ls) noexcept {
      std::swap(avant_premier, ls.avant_premier);
   }
};
#endif //LISTE_H
