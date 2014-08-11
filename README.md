Set
===

Class for managing math sets, including inserting and removing items, sets union, complements, intersect and cartesian product.
Code - now - is for C++11 only, but in future it should become c++98 compatible.

### Init
Just include "Set.hpp" to your project and go on.

### Create new Sets
```
#include "Set.hpp"

// Set of ints
Set<int> A{1,2,3}, B{3,4,5}; // A = {1,2,3}, B = {3,4,5}
Set<int> A1 = A;             // A1 = {1,2,3}

```

### Adding elements to Set
Sets can contain repeated elements, so Set.hpp allows you to do so.

```
Set<int> A{1,2,3,3}; // A = {1,2,3,3}
A.insert(9);         // A = {1,2,3,3,9}
A += 9;              // A = {1,2,3,3,9,9}
A.insert(10)         // A = {1,2,3,3,9,9,10}
A.insert(100).insert(90); // A = {1,2,3,3,9,9,10,90,100}

// Add elements to set only if it doesn't exist
A.insert(9, true); // not inserted
```

### Removing elements from set
You can remove one or more elements from your Set using the remove() method. It allows you to remove elements by iterator, range or direct value.

```
Set<int> A{1,2,2,3,3,4};
A.erase(A.begin()); // Removes first element, A = {2,2,3,3,4}
A.erase(2, false)   // Remove one '2' element, A = {2,3,3,4}
A.erase(3, true);   // Remove all '3' elements, A = {2,4}
A.erase(4);         // The short form for A.erase(4, false)
A.erase(A.begin(), A.end()); // Removes all the elements, same as A.clear()
```

### Union of sets
Set can be joined each other using the '+' operator, without modifying the original ones. They can be joined on the fly or in sub-expressions, allowing you to join Set-to-Set and Set-to-value:

```
Set<int> A{1,2,3}, B{1,2};
Set<int> C = A+B; // C={1,1,2,2,3}, A and B won't change
Set<int> D = A+1; // D = {1,1,2,3}, A won't change
Set<int> E = (A+B)+((C+D)+4); // same as above
```

You can also add an entire set, or just one value, to a Set using the '+=' operator. Doing this you will update the Set:

```
Set<int> A{1,2,3}, B{3,4,5};
A += B; // A = {1,2,3,3,4,5}, B won't change
A += 9; // A = {1,2,3,3,4,5,9}
```

### Difference / Relative complement
The relative complement of A in B, denoted as A \ B, is the set with all elements of B not present in A.
You can obtain the relative complements using the '-' operator. It's possible to concatenate more complement as it is possible to make multiple joins. Again, original sets won't change:

```
Set<int> A{1,2,3}, B{1,1,2};
Set<int> D = A-B; // D = {3}, A and B won't change
Set<int> E = B-A; // E = {1}, A and B won't change
Set<int> D = A-B-3; // D = {}, A and B won't change
```

It is possible to update a Set, removing one direct value or another Set, using the '-=' operator. It is another form of relative complement:

```
Set<int> A{1,2,3}, B{1,2};
A -= B; // A = {3}
A -= 3; // A = {}
```

You can also mix union and complement forms:

```
Set<int> A{1,2,3};
Set<int> B = A+4; // B = {1,2,3,4}
Set<int> C = B+B+5-(A+A);
```

### Find and counting elements
Set use iterators to allows you (and stl functions as std::find) to iterate through elements. Also, it provide a find() method that returns an iterator to the first item, if an item with that value is found, or Set::end() otherwise.
```
Set<int> A{1,2,3,3};
auto it = A.begin();  // iterator to '1'
auto it = A.end();    // iterator to the past-the-end element of A (NOT to '3')
auto it = A.find(3);  // returns an iterator to the first '3'
auto it = A.find(4);  // it == A.end()
```
It is possible to count elements of a set with the same value:

```
size_t n = A.count(3); // returns 2
size_t n = A.count(4); // returns 0
```

### Cartesian product
From <a href="http://en.wikipedia.org/wiki/Cartesian_product">Wikipiedia</a>, the Cartesian product A × B is the set of all ordered pairs (a, b) where a ∈ A and b ∈ B.
Set allows you to make Cartesian Product of two Sets using the '*' operator, which returns a Set&lt;Set&lt;...&gt;&gt;:

```
Set<int> A{1,2,3};
Set<int> B{2,3};
auto P = A*B; // P is Set<Set<int>>; P = {{1,2},{1,3},{2,2},{2,3},{2,3},{3,3}}
```

### Size and cleanup of a Set
You can know the size of a Set, that is the number of total elements in it. The size is greather-or-equal to 0.
Because of there is the concept of "empty set" or "zero set", Set adds the <strong>empty()</strong> method, which just checks if the size is zero.

```
Set<int> A{1,1,2,2,3,4};
size_t s = A.size(); // s = 6
bool f = A.empty();  // f = false
A.clear();           // Remove ALL items from A
```

### Comparing sets
Two sets are equals if they contains the same items, it is not important if they are repeated.
As opposite, two sets are not equals if they does not contain the same items.

```
Set<int> A{1,2,3}, B = A+1, C{2,3};
bool f1 = A == B; // f1 = true
bool f2 = A == C; // f2 = false
bool f3 = A != C; // f3 = true
```

### Inclusion
`"The set B is contained in the set A if all elements of B are present in A."` (<i>any math teacher</i>)<br/>
Set allows you to check for inclusion through the <strong>contains(Set, bool strict)</strong> method:

```
Set<int> A{1,2,3}, B{1,2}, C{1,1,2,3};
bool f1 = A.contains(B, false); // Not a strict check, returns true
bool f2 = A.contains(B);        // Same as above
bool f3 = B.contains(A);        // returns false
bool f3 = A.contains(C, true);  // true, A contains C and C contains A
```

### Unique values
You can need to take all single values from a Set (of any kind), discarding multiple values. It is possible, but it will remove items from your Set (it is not possible to remove unique values leaving the Set intact).

```
Set<int> A{1,2,1,3,4,3};
A.unique();                  // A = {1,2,3,4}
Set<int> B{3,4,5};
Set<int> C = (A+B).unique(); // C = {1,2,3,4,5}, A and B won't change
```

### Intersection
Intersection is possible, but will use unique values from both the Sets:

```
Set<int> A{1,2,3}, B{2,3,4};
Set<int> C = A.intersectionWith(B); // C = {2,3}

```

### Not allowed

- You cannot have Set containing different types, they are for uniform.<br />
So you cannot combine Set&lt;int&gt; with Set&lt;float&gt; or Set&lt;string&gt; or Set&lt;Set&lt;...&gt;&gt;, but you can write your own TypeWrapper to use your custom Set:

```
class MyTypeWrapper { ... };
Set<MyTypeWrapper> A{MyTypeWrapper(...), MyTypeWrapper(...), ...};

```

- Set of pointers will not sort/store values properly, because comparing pointers will sort items by memory address and not by value. You have to create your own object to compare pointers.

```
template<class T>
struct PointersCompare {
  bool operator()(const T *a, const T *b) const {
    return *a < *b;
  }
};

int main(int argc, const char *argv[]) {
  Set<int*, PointersCompare<int>> A{}; // an empty set

  for (int i=10; i>=1; i--) {
    A.insert(new int{i});
  }

  // A = {*1, *2, *3, ..., *10}
  for (const auto& p : A) {
    std::cout << *p << std::endl;
  }
  
  // Output:
  // 1
  // 2
  // 3
  // ...
  // 10
  
  // Release memory
  for (auto& p : A) {
    delete p;
  }
  
  return 0;
}
```

