
// Propagating lower and upper limits from top to bottom

// very clever!!!!!!!!!!!!!!!!!!!

// the best solution!!! Propagating lower and upper limits from top to bottom
//
// BEST IN TIME !!!    

/*

Good job! (Max time used: 0.06/2.00, max memory used: 48132096/536870912.)

Course: Data Structures
Week: 6
Problem: 3 Is it a binary search tree? Hard version.
Problem Introduction
In this problem you are going to solve the same problem as the previous one, but for a more general case,
when binary search tree may contain equal keys.
Problem Description
Task. You are given a binary tree with integers as its keys. You need to test whether it is a correct binary
search tree. Note that there can be duplicate integers in the tree, and this is allowed. The definition of
the binary search tree in such case is the following: for any node of the tree, if its key is 𝑥, then for any
node in its left subtree its key must be strictly less than 𝑥, and for any node in its right subtree its key
must be greater than or equal to 𝑥. In other words, smaller elements are to the left, bigger elements
are to the right, and duplicates are always to the right. You need to check whether the given binary
tree structure satisfies this condition. You are guaranteed that the input contains a valid binary tree.
That is, it is a tree, and each node has at most two children.
Input Format. The first line contains the number of vertices 𝑛. The vertices of the tree are numbered
from 0 to 𝑛 − 1. Vertex 0 is the root.
The next 𝑛 lines contain information about vertices 0, 1, ..., 𝑛−1 in order. Each of these lines contains
three integers 𝑘𝑒𝑦𝑖, 𝑙𝑒𝑓𝑡𝑖 and 𝑟𝑖𝑔ℎ𝑡𝑖 — 𝑘𝑒𝑦𝑖 is the key of the 𝑖-th vertex, 𝑙𝑒𝑓𝑡𝑖 is the index of the left
child of the 𝑖-th vertex, and 𝑟𝑖𝑔ℎ𝑡𝑖 is the index of the right child of the 𝑖-th vertex. If 𝑖 doesn’t have
left or right child (or both), the corresponding 𝑙𝑒𝑓𝑡𝑖 or 𝑟𝑖𝑔ℎ𝑡𝑖 (or both) will be equal to −1.
Constraints. 0 ≤ 𝑛 ≤ 105; −231 ≤ 𝑘𝑒𝑦𝑖 ≤ 231 − 1; −1 ≤ 𝑙𝑒𝑓𝑡𝑖, 𝑟𝑖𝑔ℎ𝑡𝑖 ≤ 𝑛 − 1. It is guaranteed that the
input represents a valid binary tree. In particular, if 𝑙𝑒𝑓𝑡𝑖 ̸= −1 and 𝑟𝑖𝑔ℎ𝑡𝑖 ̸= −1, then 𝑙𝑒𝑓𝑡𝑖 ̸= 𝑟𝑖𝑔ℎ𝑡𝑖.
Also, a vertex cannot be a child of two different vertices. Also, each vertex is a descendant of the root
vertex. Note that the minimum and the maximum possible values of the 32-bit integer type are allowed
to be keys in the tree — beware of integer overflow!
Output Format. If the given binary tree is a correct binary search tree (see the definition in the problem
description), output one word “CORRECT” (without quotes). Otherwise, output one word “INCORRECT”
(without quotes).
Time Limits.
language C C++ Java Python C# Haskell JavaScript Ruby Scala
time (sec) 2 2 3 10 3 4 10 10 6
Memory Limit. 512MB.
9
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
10
Sample 3.
Input:
3
2 1 2
1 -1 -1
2 -1 -1
Output:
CORRECT
2
1 2
Duplicate keys are allowed, and they should always be in the right subtree of the first duplicated
element.
Sample 4.
Input:
3
2 1 2
2 -1 -1
3 -1 -1
Output:
INCORRECT
2
2 3
The key of the left child of the root must be strictly smaller than the key of the root.
Sample 5.
Input:
0
Output:
CORRECT
Empty tree is considered correct.
11
Sample 6.
Input:
1
2147483647 -1 -1
Output:
CORRECT
Explanation:
2147483647
The maximum possible value of the 32-bit integer type is allowed as key in the tree.
Sample 7.
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
12
Sample 8.
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
Starter Files
The starter solutions for this problem read the input data from the standard input, pass it to a blank
procedure, and then write the result to the standard output. You are supposed to implement your algorithm
in this blank procedure if you are using C++, Java, or Python3. For other programming languages, you need
to implement a solution from scratch. Filename: is_bst_hard
What to Do
Try to adapt the algorithm from the previous problem to the case when duplicate keys are allowed, and
beware of integer overflow!

*/

#include <algorithm>  // for sort function
#include <iostream>
#include <limits>     // infinity, max of int type, etc.
#include <stack>      // for stack class
#include <vector>     // for vectro class

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::vector;


struct Node {
  int key;
  int left;
  int right;
  long long min;
  long long max;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
  
};


bool IsBinarySearchTree( vector<Node>& tree ) {
  
  stack <Node> Stack_of_Nodes;

  Node root = tree[0];
  root.min = std::numeric_limits<long long>::min(); // -INFINITE
  root.max = std::numeric_limits<long long>::max(); // +INFINITE
  
  Stack_of_Nodes.push ( root );
  
  while ( !Stack_of_Nodes.empty() ) {
    
    root = Stack_of_Nodes.top();
    Stack_of_Nodes.pop();
    
    if ( root.key < root.min || root.key >= root.max ) {
      return false;
    }
    
    if ( root.left != -1 ){
      Node temp = tree [root.left];
      temp.min = root.min;
      temp.max = root.key;
      Stack_of_Nodes.push( temp );
    }
    
    if ( root.right != -1 ){
      Node temp = tree [root.right];
      temp.min = root.key;
      temp.max = root.max;
      Stack_of_Nodes.push( temp );
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

  if ( nodes == 0 || IsBinarySearchTree( tree ) ) {
    cout << "CORRECT" << endl;
  } 
  else {
    cout << "INCORRECT" << endl;
  }
  
  return 0;
}

