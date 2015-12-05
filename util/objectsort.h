#ifndef OBJECTSORT_H
#define OBJECTSORT_H
#include "models/persons.h"
#include "models/computers.h"

class ObjectSort
{
public:
    ObjectSort(int sortBy, bool orderOfSort);

    bool operator() (const Persons& p1, const Persons& p2);
    bool operator() (const Computers& c1, const Computers& c2);
private:
    int sortByColumn;
    bool orderToSortBy;
};

#endif // OBJECTSORT_H
