#ifndef GENERICS_H
#define GENERICS_H

#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <string>

#include "tipos.h"
#include "lista.h"

#define STRING_TOKEN '|'

using namespace std;

  template<typename T>
    Lista<T> sublist(const Lista<T>& l, string elems) {
      stringstream ss(elems);
      int i;
      Lista<int> indices;
      while (ss.rdstate() == 0) {
        ss >> i;
        indices.agregarAtras(i);
      }
      // cout << indices << endl;
      Lista<T> ret;
      for (int i = 0; i < indices.longitud(); i++)
        ret.agregarAtras(l.iesimo(indices.iesimo(i)));

      // cout << ret.longitud() << endl;
      return ret;
    }

    template<typename T, typename K>
    std::ostream & operator<<(std::ostream & os,const  pair<T, K>& j) {
      os << "(" << j.first << ", " << j.second << ")";
      return os;
    }

#endif
