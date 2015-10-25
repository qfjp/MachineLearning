#include "disjoint_set.hh"
#include <cstdlib>

template <class T> DisjointSet<T>::DisjointSet(T elem,
                                               DisjointSet<T> parent,
                                               int rank) {
    this->elem = elem;
    this->parent = parent;
    this->rank = rank;
}

template <class T> DisjointSet<T> DisjointSet<T>::representative() {
    DisjointSet<T> representative = this;
    while (representative.parent != NULL) {
        representative = representative.parent;
    }
    return representative;
}

template <class T> DisjointSet<T>
DisjointSet<T>::setParent(DisjointSet<T> par) {
    parent = par;
}

template <class T> T DisjointSet<T>::getElem() {
    return elem;
}

template <class T> int DisjointSet<T>::getRank() {
    return rank;
}

template <class T> void DisjointSet<T>::addRank(int num) {
    rank += num;
}

template <class T> void DisjointSet<T>::compressPath() {
    DisjointSet<T> rep = representative();
    DisjointSet<T> iter = this;
    while (iter != rep) {
        iter.parent = rep;
    }
}
