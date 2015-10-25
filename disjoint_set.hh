#ifndef DISJOINT_SET
#define DISJOINT_SET 1

template <class T> class DisjointSet {
 private:
     T elem;
     DisjointSet<T> parent;
     int rank;
 public:
     DisjointSet<T>(T elem, DisjointSet<T> parent, int rank);
     DisjointSet<T> representative();
     DisjointSet<T> setParent(DisjointSet<T> par);
     T getElem();
     int getRank();
     void addRank(int num);
     void compressPath();
};

#endif
