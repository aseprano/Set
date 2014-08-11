Set
===

Class for managing math sets, including inserting and removing items, sets union, complements, intersect and cartesian product.
Code - now - is for C++11 only, but in future it should become c++98 compatible.

### Usage examples

```
#include "Set.hpp"

// Set of ints
Set<int> A{1,2,3}, B{3,4,5}, A1 = A; // A = {1,2,3}, B = {3,4,5}, A1 = {1,2,3}

// Add elements to set
A.insert(9); // A = {1,2,3,9}
A += 9;      // A = {1,2,3,9,9}
A.insert(10).insert(100); // A = {1,2,3,9,9,10,100}

// Add elements to set only if element is unique
A.insert(9, true); // not inserted

// Creating new set with above operations combined
auto C = A + 10;
auto D = A + B + 1; // C and D are Set<int>, just like A and B

// Finding and counting set elements
auto it = A.find(3); // returns first reference to '3', or A.end()
auto n  = D.count(3); // how many '3' there are in D

// Remove elements from set
A.erase(9);       // Remove just ONE '9' value from the set, returns the number of elements removed
A.erase(9, true); // Removes ALL '9' values from the set, returns the number of elements removed
A -= 10;          // same as A.remove(10);

// Cartesian product
auto P = A*B; // if A = {1,2,3}, B = {3,4}, then P = {{1,3},{1,4},{2,3},{2,4},{3,3},{3,4}}
              // P is Set<Set<int>>

// Size of a Set
A.size();  // Count of items in A (NOT unique): A={1,1,2,3}, A.size() = 4
A.empty(); // Return true if A.count() == 0, false otherwise
A.clear(); // Remove ALL items from A

// Unique, removes all but the first element from the Set
Set<int> A{1,2,1,3,4,3};     // A = {1,1,2,3,3,4}
A.unique();                  // A = {1,2,3,4}
Set<int> B{3,4,5};
Set<int> C = (A+B).unique(); // C = {1,2,3,4,5}

// Intersection
Set<int> A{1,2,3}, B{2,3,4}, C = A.intersectionWith(B); // C = {2,3}

```
