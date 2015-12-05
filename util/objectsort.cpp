#include "util/objectsort.h"
#include "models/persons.h"
#include "models/computers.h"

ObjectSort::ObjectSort(int sortBy, bool orderOfSort){
  sortByColumn=sortBy;
  orderToSortBy=orderOfSort;
}

bool ObjectSort::operator() (const Persons& p1, const Persons& p2){
  switch(sortByColumn){
      case 1: //Sort by First name
          if(orderToSortBy==0)
            return p1.getF() < p2.getF();
          else
            return p2.getF() < p1.getF();
          break;
      case 2: // Sort by last name
          if(orderToSortBy==0)
            return p1.getL() < p2.getL();
          else
            return p2.getL() < p1.getL();
          break;
      case 3: // Sort by gender
          if(orderToSortBy==0)
            return p1.getGender() < p2.getGender();
          else
            return p2.getGender() < p1.getGender();
          break;
      case 4: //Sort by year born
          if(orderToSortBy==0)
            return p1.getYearBorn() < p2.getYearBorn();
          else
            return p2.getYearBorn() < p1.getYearBorn();
          break;
      case 5: //Sort by year died
          if(orderToSortBy==0)
            return p1.getYearDied() < p2.getYearDied();
          else
            return p2.getYearDied() < p1.getYearDied();
          break;
      default:
          return false; //in case somthing goes wrong
          break;
      }
}

bool ObjectSort::operator() (const Computers& c1, const Computers& c2){
  switch(sortByColumn){
      case 1:
          if(orderToSortBy==0)
            return c1.getName() < c2.getName();
          else
            return c2.getName() < c1.getName();
          break;
      case 2:
          if(orderToSortBy==0)
            return c1.getType() < c2.getType();
          else
            return c2.getType() < c1.getType();
          break;
      case 3:
          if(orderToSortBy==0)
            return c1.getBuild() < c2.getBuild();
          else
            return c2.getBuild() < c1.getBuild();
          break;
      case 4:
          if(orderToSortBy==0)
            return c1.getBuildYear() < c2.getBuildYear();
          else
            return c2.getBuildYear() < c1.getBuildYear();
          break;
      default:
          return false; //in case somthing goes wrong
          break;
      }
}
