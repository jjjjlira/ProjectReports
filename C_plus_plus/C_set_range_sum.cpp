/*

Good job! (Max time used: 0.09/1.00, max memory used: 37634048/536870912.)

Course: Data Structures
Week: 6
Problem: 4 Set with range sums

Problem Introduction
In this problem, your goal is to implement a data structure to store a set of integers and quickly compute
range sums.

Problem Description

Task. Implement a data structure that stores a set 𝑆 of integers with the following allowed operations:

∙ add(𝑖) — add integer 𝑖 into the set 𝑆 (if it was there already, the set doesn’t change).
∙ del(𝑖) — remove integer 𝑖 from the set 𝑆 (if there was no such element, nothing happens).
∙ find(𝑖) — check whether 𝑖 is in the set 𝑆 or not.
∙ sum(𝑙, 𝑟) — output the sum of all elements 𝑣 in 𝑆 such that 𝑙 ≤ 𝑣 ≤ 𝑟.

Input Format. Initially the set 𝑆 is empty. The first line contains 𝑛 — the number of operations. The next
𝑛 lines contain operations. Each operation is one of the following:

∙ “+ i" — which means add some integer (not 𝑖, see below) to 𝑆,
∙ “- i" — which means del some integer (not 𝑖, see below)from 𝑆,
∙ “? i" — which means find some integer (not 𝑖, see below)in 𝑆,
∙ “s l r" — which means compute the sum of all elements of 𝑆 within some range of values (not
from 𝑙 to 𝑟, see below).

However, to make sure that your solution can work in an online fashion, each request will actually
depend on the result of the last sum request. Denote 𝑀 = 1 000 000 001. At any moment, let 𝑥 be
the result of the last sum operation, or just 0 if there were no sum operations before. Then

∙ “+ i" means add((𝑖 + 𝑥) mod 𝑀),
∙ “- i" means del((𝑖 + 𝑥) mod 𝑀),
∙ “? i" means find((𝑖 + 𝑥) mod 𝑀),
∙ “s l r" means sum((𝑙 + 𝑥) mod 𝑀, (𝑟 + 𝑥) mod 𝑀).

Constraints. 1 ≤ 𝑛 ≤ 100 000; 0 ≤ 𝑖 ≤ 109.

Output Format. For each find request, just output “Found" or “Not found" (without quotes; note that the
first letter is capital) depending on whether (𝑖+𝑥) mod 𝑀 is in 𝑆 or not. For each sum query, output
the sum of all the values 𝑣 in 𝑆 such that ((𝑙+𝑥) mod 𝑀) ≤ 𝑣 ≤ ((𝑟+𝑥) mod 𝑀) (it is guaranteed that
in all the tests ((𝑙 + 𝑥) mod 𝑀) ≤ ((𝑟 + 𝑥) mod 𝑀)), where 𝑥 is the result of the last sum operation
or 0 if there was no previous sum operation.

Time Limits.
language   C  C++ Java Python C#   Haskell JavaScript Ruby Scala
time (sec) 1  1   4    120    1.5  2       120        120  4

Memory Limit. 512MB.


Sample 1.
Input:
15
? 1
+ 1
? 1
+ 2
s 1 2
+ 1000000000
? 1000000000
- 1000000000
? 1000000000
s 999999999 1000000000
- 2
? 2
- 0
+ 9
s 0 9

Output:

Not found
Found
3
Found
Not found
1
Not found
10

Explanation:
For the first 5 queries, 𝑥 = 0. For the next 5 queries, 𝑥 = 3. For the next 5 queries, 𝑥 = 1. The actual
list of operations is:

find(1)
add(1)
find(1)
add(2)
sum(1, 2) → 3
add(2)
find(2) → Found
del(2)
find(2) → Not found
sum(1, 2) → 1
del(3)
find(3) → Not found
del(1)
add(10)
sum(1, 10) → 10
Adding the same element twice doesn’t change the set. Attempts to remove an element which is not
in the set are ignored.

Sample 2.
Input:
5
? 0
+ 0
? 0
- 0
? 0

Output:
Not found
Found
Not found
First, 0 is not in the set. Then it is added to the set. Then it is removed from the set.

Sample 3.
Input:
5
+ 491572259
? 491572259
? 899375874
s 310971296 877523306
+ 352411209
Output:
Found
Not found
491572259

Explanation:
First, 491572259 is added to the set, then it is found there. Number 899375874 is not in the set. The
only number in the set is now 491572259, and it is in the range between 310971296 and 877523306, so
the sum of all numbers in this range is equal to 491572259.

Starter Files
The starter solutions in C++, Java and Python3 read the input, write the output, fully implement splay
tree and show how to use its methods to solve this problem, but don’t solve the whole problem. You need
to finish the implementation. If you use other languages, you need to implement a solution from scratch.
Note that we strongly encourage you to use stress testing, max tests, testing for min and max values of
each parameter according to the restrictions section and other testing techniques and advanced advice from
this reading. If you’re stuck for a long time, you can read ths forum thread to find out what other learners
struggled with, how did they overcome their troubles and what tests did they come up with. If you’re still
stuck, you can read the hints in the next What to Do section mentioning some of the common problems and
how to test for them, resolve some of them. Finally, if none of this worked, we included some of the trickier
test cases in the starter files for this problem, so you can use them to debug your program if it fails on one
of those tests in the grader. However, you will learn more if you pass this problem without looking at those
test cases in the starter files.

What to Do
Use splay tree to efficiently store the set, add, delete and find elements. For each node in the tree, store
additionally the sum of all the elements in the subtree of this node. Don’t forget to update this sum each
time the tree changes. Use split operation to cut ranges from the tree. To get the sum of all the needed
elements after split, just look at the sum stored in the root of the splitted tree. Don’t forget to merge the
trees back after the sum operation.

Some hints based on the problems some learners encountered with their solutions:

∙ Use the sum attribute to keep updated the sum in the subtree, don’t compute the sum from scratch
each time, otherwise it will work too slow.
∙ Don’t forget to do splay after each operation with a splay tree.
∙ Don’t forget to splay the node which was accessed last during the find operation.
∙ Don’t forget to update the root variable after each operation with the tree, because splay operation
changes root, but it doesn’t change where your root variable is pointing in some of the starters.
∙ Don’t forget to merge back after splitting the tree.
∙ When you detach a node from its parent, don’t forget to detach pointers from both ends.
∙ Don’t forget to update all the pointers correctly when merging the trees together.
∙ Test sum operation when there are no elements within the range.
∙ Test sum operation when all the elements are within the range.
∙ Beware of integer overflow.
∙ Don’t forget to check for null when erasing.
∙ Test: Try adding nodes in the tree in such an order that the tree becomes very unbalanced. Play with
this visualization to find out how to do it. Create a very big unbalanced tree. Then try searching for
an element that is not in the tree many times.
∙ Test: add some elements and then remove all the elements from the tree.

*/


#include <cstdio>

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
  int key;
  // Sum of all the keys in the subtree - remember to update
  // it after each operation that changes the tree.
  long long sum;
  Vertex* left;
  Vertex* right;
  Vertex* parent;

  Vertex( int key, long long sum, Vertex* left, Vertex* right, Vertex* parent ) 
  : key( key ), sum( sum ), left( left ), right( right ), parent( parent ) {}
};

void update( Vertex* v ) {
  if ( v == NULL ) return;
  // 0ll means "0 long long"
  v->sum = v->key + ( v->left != NULL ? v->left->sum : 0ll ) + ( v->right != NULL ? v->right->sum : 0ll );
  
  if ( v->left != NULL ) {
    v->left->parent = v;
  }
  
  if ( v->right != NULL ) {
    v->right->parent = v;
  }
}

void small_rotation( Vertex* v ) {
  Vertex* parent = v->parent;
  if ( parent == NULL ) {
    return;
  }
  Vertex* grandparent = v->parent->parent;
  if ( parent->left == v ) {
    Vertex* m = v->right;
    v->right = parent;
    parent->left = m;
  } 
  else {
    Vertex* m = v->left;
    v->left = parent;
    parent->right = m;
  }
  update( parent );
  update( v );
  v->parent = grandparent;
  if ( grandparent != NULL ) {
    if ( grandparent->left == parent ) {
      grandparent->left = v;
    } else {
      grandparent->right = v;
    }
  }
}

void big_rotation( Vertex* v ) {
  if ( v->parent->left == v && v->parent->parent->left == v->parent ) {
    // Zig-zig
    small_rotation( v->parent );
    small_rotation(v);
  } else if ( v->parent->right == v && v->parent->parent->right == v->parent ) {
    // Zig-zig
    small_rotation( v->parent );
    small_rotation( v );
  } else {
    // Zig-zag
    small_rotation( v );
    small_rotation( v );
  }  
}

// Makes splay of the given vertex and makes
// it the new root.
void splay( Vertex*& root, Vertex* v ) {
  if ( v == NULL ) return;
  while ( v->parent != NULL ) {
    if ( v->parent->parent == NULL ) {
      small_rotation( v );
      break;
    }
    big_rotation( v );
  }
  root = v;
}

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find( Vertex*& root, int key ) {
  Vertex* v    = root;
  Vertex* last = root;
  Vertex* next = NULL;
  
  while ( v != NULL ) {
    if ( v->key >= key  &&  ( next == NULL || v->key < next->key ) ) {
      next = v;
    }
    last = v;
    if ( v->key == key ) {
      break;      
    }
    if ( v->key < key ) {
      v = v->right;
    } 
    else {
      v = v->left;
    }
  }
  splay( root, last );
  return next;
}

void split( Vertex* root, int key, Vertex*& left, Vertex*& right ) {
  right = find( root, key );
  splay( root, right );
  
  if ( right == NULL ) {
    left = root;
    return;
  }
  left = right->left;
  right->left = NULL;
  if ( left != NULL ) {
    left->parent = NULL;
  }
  update( left );
  update( right );
}

Vertex* merge( Vertex* left, Vertex* right ) {
  if ( left ==  NULL ) return right;
  if ( right == NULL ) return left;
  Vertex* min_right = right;
  while ( min_right->left != NULL ) {
    min_right = min_right->left;
  }
  splay( right, min_right );
  right->left = left;
  update( right );
  return right;
}


// Code that uses splay tree to solve the problem

Vertex* root = NULL;

void insert( int x ) {
  Vertex* left       = NULL;
  Vertex* right      = NULL;
  Vertex* new_vertex = NULL;
  
  split( root, x, left, right );
  if ( right == NULL || right->key != x ) {
    new_vertex = new Vertex( x, x, NULL, NULL, NULL );
  }
  root = merge( merge( left, new_vertex ), right );
}

void erase( int x ) {                   
  // Implement erase yourself
  auto res = find( root, x );
  if ( res != nullptr and res->key == x ) {
      // res points to node with key x
      Vertex *left   = nullptr;
      Vertex *middle = nullptr;
      Vertex *right  = nullptr;
      split( root, x, left, middle );
      split( middle, x + 1, middle, right );
      root = merge( left, right );
      middle = nullptr;
  }
}

bool find( int x ) {  
  // Implement find yourself
  auto res = find( root, x );
  return ( res != nullptr and res->key == x );
  //return false;
}

long long sum( int from, int to ) {
  Vertex* left   = NULL;
  Vertex* middle = NULL;
  Vertex* right  = NULL;
  split( root, from, left, middle );
  split( middle, to + 1, middle, right );
  long long ans = 0;
  // Complete the implementation of sum

  if ( middle != nullptr )
      ans = middle->sum;
  root = merge( left, merge( middle, right ) );
  return ans;  
}

const int MODULO = 1000000001;

int main() {
  int n;
  scanf("%d", &n);
  
  int last_sum_result = 0;
  
  for ( int i = 0; i < n; i++ ) {
    char buffer[10];
    scanf( "%s", buffer );
    char type = buffer[0];
    
    switch ( type ) {
      case '+' : {
        int x;
        scanf( "%d", &x );
        insert( ( x + last_sum_result ) % MODULO );
      } break;
      case '-' : {
        int x;
        scanf( "%d", &x );
        erase( ( x + last_sum_result ) % MODULO );
      } break;            
      case '?' : {
        int x;
        scanf( "%d", &x );
        printf( find( ( x + last_sum_result ) % MODULO ) ? "Found\n" : "Not found\n" );
      } break;
      case 's' : {
        int l, r;
        scanf( "%d %d", &l, &r );
        long long res = sum( ( l + last_sum_result ) % MODULO, ( r + last_sum_result ) % MODULO );
        printf( "%lld\n", res );
        last_sum_result = int( res % MODULO );
      }
    }
  }
  return 0;
}
