/*
Good job! (Max time used: 0.05/1.00, max memory used: 29892608/536870912.)

Course: Data Structures
Week: 6
Problem: 1 Binary tree traversals


Problem Introduction

In this problem you will implement in-order, pre-order and post-order traversals of a binary tree. These
traversals were defined in the week 1 lecture on tree traversals, but it is very useful to practice implementing
them to understand binary search trees better.

Problem Description

Task. You are given a rooted binary tree. Build and output its in-order, pre-order and post-order traversals.

Input Format. The first line contains the number of vertices 𝑛. The vertices of the tree are numbered
from 0 to 𝑛 − 1. Vertex 0 is the root.
The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order. Each of these lines contains
three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖 and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖-th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
child of the 𝑖-th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖-th vertex. If 𝑖 doesn’t have
left or right child (or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 (or both) will be equal to −1.

Constraints. 1 ≤ 𝑛 ≤ 105; 0 ≤ 𝑘𝑒𝑦𝑖 ≤ 109; −1 ≤ 𝑙𝑒𝑓𝑡𝑖, 𝑟𝑖𝑔ℎ𝑡𝑖 ≤ 𝑛 − 1. It is guaranteed that the input
represents a valid binary tree. In particular, if 𝑙𝑒𝑓𝑡𝑖 ̸= −1 and 𝑟𝑖𝑔ℎ𝑡𝑖 ̸= −1, then 𝑙𝑒𝑓𝑡𝑖 ̸= 𝑟𝑖𝑔ℎ𝑡𝑖. Also,
a vertex cannot be a child of two different vertices. Also, each vertex is a descendant of the root vertex.
Output Format. Print three lines. The first line should contain the keys of the vertices in the in-order
traversal of the tree. The second line should contain the keys of the vertices in the pre-order traversal
of the tree. The third line should contain the keys of the vertices in the post-order traversal of the tree.

Time Limits.
language   C C++ Java Python C#  Haskell JavaScript Ruby Scala
time (sec) 1 1   12   6      1.5 2      6          6    12

Memory Limit. 512MB.

Sample 1.
Input:
5
4 1 2
2 3 4
5 -1 -1
1 -1 -1
3 -1 -1
Output:
1 2 3 4 5
4 2 1 3 5
1 3 2 5 4
2
4
2
1 3
5

Sample 2.
Input:
10
0 7 2
10 -1 -1
20 -1 6
30 8 9
40 3 -1
50 -1 -1
60 1 -1
70 5 4
80 -1 -1
90 -1 -1

Output:
50 70 80 30 90 40 0 20 10 60
0 70 50 40 30 80 90 20 60 10
50 80 90 30 40 70 10 60 20 0
0
70
50 40
30
80 90
20
60
10

Starter Files

There are starter solutions only for C++, Java and Python3, and if you use other languages, you need to
implement solution from scratch. Starter solutions read the input, define the methods to compute different
traversals of the binary tree and write the output. You need to implement the traversal methods.

What to Do

Implement the traversal algorithms from the lectures. Note that the tree can be very deep in this problem,
so you should be careful to avoid stack overflow problems if you’re using recursion, and definitely test your
solution on a tree with the maximum possible height.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;
  vector <int> result;
  
public:

  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }
  
  void print( vector <int> a ) {
    for ( size_t i = 0; i < a.size(); i++ ) {
      if ( i > 0 ) {
        cout << ' ';
      }
      cout << a[i];
    }
    cout << '\n';
  }
  
  void print_in_order_traversal(){
    in_order_traversal( 0 );
    print( result );
    result.clear();
  }
  
  void in_order_traversal( int index ){
    if ( index < 0 ){
       return;
    }
    in_order_traversal( left[index] );
    result.push_back( key[index] );
    in_order_traversal( right[index] );  
  }
 
  void print_pre_order_traversal(){
    pre_order_traversal( 0 );
    print( result );
    result.clear();
  }
  
  void pre_order_traversal( int index ){
    if ( index < 0 ){
     return;
    }
    result.push_back( key[index] );
    pre_order_traversal( left[index] );
    pre_order_traversal( right[index] );  
  }

  void print_post_order_traversal(){
    post_order_traversal( 0 );
    print( result );
    result.clear();
  }
  
  void post_order_traversal( int index ){
    if ( index < 0 ){
     return;
    }
    post_order_traversal( left[index] );
    post_order_traversal( right[index] ); 
    result.push_back( key[index] );
  }
  
};


int main_with_large_stack_space() {
  ios_base::sync_with_stdio( 0 );
  TreeOrders t;
  t.read();
  
  t.print_in_order_traversal();
  t.print_pre_order_traversal();
  t.print_post_order_traversal();
    
  return 0;
}


int main ( int argc, char **argv )
{
#if defined( __unix__ ) || defined( __APPLE__ )
  // Allow larger stack space
  const  rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int    result;

  result = getrlimit( RLIMIT_STACK, &rl );
  if ( result == 0 ) {
      if ( rl.rlim_cur < kStackSize ) {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if ( result != 0 ) {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

