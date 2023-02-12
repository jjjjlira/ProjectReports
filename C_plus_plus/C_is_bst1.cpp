
// in order and then ccheck if it is ordered

// very clever and very simple!!!!!!!!!!!!!!!!!!!

// but the is still a better solution!!! Propagating lower and upper limits from top to bottom
//
/*

Good job! (Max time used: 0.07/2.00, max memory used: 21438464/536870912.)

Course: Data Structures
Week: 6
Problem: 2 Is it a binary search tree?

Problem Introduction

In this problem you are going to test whether a binary search tree data structure from some programming
language library was implemented correctly. There is already a program that plays with this data structure
by inserting, removing, searching integers in the data structure and outputs the state of the internal binary
tree after each operation. Now you need to test whether the given binary tree is indeed a correct binary
search tree. In other words, you want to ensure that you can search for integers in this binary tree using
binary search through the tree, and you will always get correct result: if the integer is in the tree, you will
find it, otherwise you will not.

Problem Description

Task. You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. The definition of the binary search tree is the following: for any node of the tree, if its
key is 𝑥, then for any node in its left subtree its key must be strictly less than 𝑥, and for any node in
its right subtree its key must be strictly greater than 𝑥. In other words, smaller elements are to the
left, and bigger elements are to the right. You need to check whether the given binary tree structure
satisfies this condition. You are guaranteed that the input contains a valid binary tree. That is, it is a
tree, and each node has at most two children.

Input Format. The first line contains the number of vertices 𝑛. The vertices of the tree are numbered
from 0 to 𝑛 − 1. Vertex 0 is the root.
The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order. Each of these lines contains
three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖 and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖-th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
child of the 𝑖-th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖-th vertex. If 𝑖 doesn’t have
left or right child (or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 (or both) will be equal to −1.

Constraints. 0 ≤ 𝑛 ≤ 105; −231 < 𝑘𝑒𝑦𝑖 < 231 − 1; −1 ≤ 𝑙𝑒𝑓𝑡𝑖, 𝑟𝑖𝑔ℎ𝑡𝑖 ≤ 𝑛 − 1. It is guaranteed that the
input represents a valid binary tree. In particular, if 𝑙𝑒𝑓𝑡𝑖 ̸= −1 and 𝑟𝑖𝑔ℎ𝑡𝑖 ̸= −1, then 𝑙𝑒𝑓𝑡𝑖 ̸= 𝑟𝑖𝑔ℎ𝑡𝑖.
Also, a vertex cannot be a child of two different vertices. Also, each vertex is a descendant of the root
vertex. All keys in the input will be different.

Output Format. If the given binary tree is a correct binary search tree (see the definition in the problem
description), output one word “CORRECT” (without quotes). Otherwise, output one word “INCORRECT”
(without quotes).

Time Limits.
language   C C++ Java Python C# Haskell JavaScript Ruby Scala
time (sec) 2 2   3    10     3  4       10         10   6

Memory Limit. 512MB.

Sample 1.
Input:
3
2 1 2
1 -1 -1
3 -1 -1

Output:
CORRECT
2
1 3
Left child of the root has key 1, right child of the root has key 3, root has key 2, so everything to the
left is smaller, everything to the right is bigger.

Sample 2.

Input:
3
1 1 2
2 -1 -1
3 -1 -1

Output:
INCORRECT
1
2 3
The left child of the root must have smaller key than the root.

Sample 3.

Input:
0

Output:
CORRECT
Empty tree is considered correct.

Sample 4.
Input:
5
1 -1 1
2 -1 2
3 -1 3
4 -1 4
5 -1 -1
Output:
CORRECT
Explanation:
1
2
3
4
5
The tree doesn’t have to be balanced. We only need to test whether it is a correct binary search tree,
which the tree in this example is.

Sample 5.

Input:
7
4 1 2
2 3 4
6 5 6
1 -1 -1
3 -1 -1
5 -1 -1
7 -1 -1

Output:
CORRECT

Explanation:
4
2
1 3
6
5 7

This is a full binary tree, and the property of the binary search tree is satisfied in every node.

Sample 6.

Input:
4
4 1 -1
2 2 3
1 -1 -1
5 -1 -1

Output:
INCORRECT

Explanation:
4
2
1 5
Node 5 is in the left subtree of the root, but it is bigger than the key 4 in the root.

Starter Files
The starter solutions for this problem read the input data from the standard input, pass it to a blank
procedure, and then write the result to the standard output. You are supposed to implement your algorithm
in this blank procedure if you are using C++, Java, or Python3. For other programming languages, you need
to implement a solution from scratch. Filename: is_bst

What to Do
Testing the binary search tree condition for each node and every other node in its subtree will be too slow.
You should come up with a faster algorithm.

*/

#include <algorithm>  // for sort function
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

vector<int> ordered_vector;

struct Node {
  int key;
  int left;
  int right;

  
  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
  
  void print( vector <int> a ) {
    for ( size_t i = 0; i < a.size(); i++ ) {
      if ( i > 0 ) {
        cout << ' ';
      }
      cout << a[i];
    }
    cout << '\n';
  }

};



void in_order_traversal( vector<Node>& tree, int index ){ 
  
  if ( index < 0 ){
     return;
  }
  
  in_order_traversal( tree, tree[index].left  );
  ordered_vector.push_back( tree[index].key );
  in_order_traversal( tree, tree[index].right ); 
  
}


bool IsBinarySearchTree( vector<Node>& tree ) {
  
  if ( tree.empty() ){
    return true;
  }
  in_order_traversal( tree, 0 );
  
  for (int i = 1; i < tree.size(); ++i) {
    if ( ordered_vector[i] <= ordered_vector[i-1] ) {
      return false;
    }
  }
  
  return true;
}


int main() {
  int nodes;
  cin >> nodes;
  
  vector<Node> tree;
  
  for ( int i = 0; i < nodes; ++i ) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back( Node( key, left, right ) );
  }
  
  if ( nodes == 0 ){
    cout << "CORRECT" << endl;
    return 0;
  }
  
  if ( IsBinarySearchTree( tree ) ) {
    cout << "CORRECT" << endl;
  } 
  else {
    cout << "INCORRECT" << endl;
  }
  
  return 0;
}

