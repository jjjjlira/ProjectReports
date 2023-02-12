/*

WORKS GOOD!!!!

Course Data Structures

Week: 1
Problem: 2 Compute tree height


Problem Introduction
Trees are used to manipulate hierarchical data such as hierarchy of categories of a retailer or the directory
structure on your computer. They are also used in data analysis and machine learning both for hierarchical
clustering and building complex predictive models, including some of the best-performing in practice
algorithms like Gradient Boosting over Decision Trees and Random Forests. In the later modules of this
course, we will introduce balanced binary search trees (BST) — a special kind of trees that allows to very
efficiently store, manipulate and retrieve data. Balanced BSTs are thus used in databases for efficient storage
and actually in virtually any non-trivial programs, typically via built-in data structures of the programming
language at hand.
In this problem, your goal is to get used to trees. You will need to read a description of a tree from the
input, implement the tree data structure, store the tree and compute its height.

Problem Description

Task. You are given a description of a rooted tree. Your task is to compute and output its height. Recall
that the height of a (rooted) tree is the maximum depth of a node, or the maximum distance from a
leaf to the root. You are given an arbitrary tree, not necessarily a binary tree.

Input Format. The first line contains the number of nodes 𝑛. The second line contains 𝑛 integer numbers
from −1 to 𝑛 − 1 — parents of nodes. If the 𝑖-th one of them (0 ≤ 𝑖 ≤ 𝑛 − 1) is −1, node 𝑖 is the root,
otherwise it’s 0-based index of the parent of 𝑖-th node. It is guaranteed that there is exactly one root.
It is guaranteed that the input represents a tree.

Constraints. 1 ≤ 𝑛 ≤ 105.

Output Format. Output the height of the tree.

Time Limits.
language C C++ Java Python C# Haskell JavaScript Ruby Scala
time (sec) 1 1 6 3 1.5 2 5 5 3

Memory Limit. 512MB.

Sample 1.
Input:
5
4 -1 4 1 1
Output:
3
The input means that there are 5 nodes with numbers from 0 to 4, node 0 is a child of node 4, node 1
is the root, node 2 is a child of node 4, node 3 is a child of node 1 and node 4 is a child of node 1. To
see this, let us write numbers of nodes from 0 to 4 in one line and the numbers given in the input in
the second line underneath:
0 1 2 3 4
4 -1 4 1 1
Now we can see that the node number 1 is the root, because −1 corresponds to it in the second line.
Also, we know that the nodes number 3 and number 4 are children of the root node 1. Also, we know
that the nodes number 0 and number 2 are children of the node 4.
6
root 1
3 4
0 2
The height of this tree is 3, because the number of vertices on the path from root 1 to leaf 2 is 3.

Sample 2.
Input:
5
-1 0 4 0 3
Output:
4
Explanation:
The input means that there are 5 nodes with numbers from 0 to 4, node 0 is the root, node 1 is a child
of node 0, node 2 is a child of node 4, node 3 is a child of node 0 and node 4 is a child of node 3. The
height of this tree is 4, because the number of nodes on the path from root 0 to leaf 2 is 4.
root 0
1 3
4
2

Starter Files
The starter solutions in this problem read the description of a tree, store it in memory, compute the height
in a naive way and write the output. You need to implement faster height computation. Starter solutions
are available for C++, Java and Python3, and if you use other languages, you need to implement a solution
from scratch.

What to Do
To solve this problem, change the height function described in the lectures with an implementation which
will work for an arbitrary tree. Note that the tree can be very deep in this problem, so you should be careful
to avoid stack overflow problems if you’re using recursion, and definitely test your solution on a tree with
the maximum possible height.

Suggestion: Take advantage of the fact that the labels for each tree node are integers in the range 0..𝑛−1:
you can store each node in an array whose index is the label of the node. By storing the nodes in an array,
you have 𝑂(1) access to any node given its label.

Create an array of 𝑛 nodes:
7
allocate 𝑛𝑜𝑑𝑒𝑠[𝑛]
for 𝑖 ← 0 to 𝑛 − 1:
𝑛𝑜𝑑𝑒𝑠[𝑖] =new 𝑁𝑜𝑑𝑒
Then, read each parent index:
for 𝑐ℎ𝑖𝑙𝑑_𝑖𝑛𝑑𝑒𝑥 ← 0 to 𝑛 − 1:
read 𝑝𝑎𝑟𝑒𝑛𝑡_𝑖𝑛𝑑𝑒𝑥
if 𝑝𝑎𝑟𝑒𝑛𝑡_𝑖𝑛𝑑𝑒𝑥 == −1:
𝑟𝑜𝑜𝑡 ← 𝑐ℎ𝑖𝑙𝑑_𝑖𝑛𝑑𝑒𝑥
else:
𝑛𝑜𝑑𝑒𝑠[𝑝𝑎𝑟𝑒𝑛𝑡_𝑖𝑛𝑑𝑒𝑥].𝑎𝑑𝑑𝐶ℎ𝑖𝑙𝑑(𝑛𝑜𝑑𝑒𝑠[𝑐ℎ𝑖𝑙𝑑_𝑖𝑛𝑑𝑒𝑥])

Once you’ve built the tree, you’ll then need to compute its height. If you don’t use recursion, you needn’t
worry about stack overflow problems. Without recursion, you’ll need some auxiliary data structure to keep

*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

#define MAX(x,y) ((x)>(y)?(x):(y))

using namespace std;

const long long maxn = (long long) 1e5+9;

// Each row of the vector contains all the children of each node
vector<vector<int>> children( maxn );


int get_height( int my_root ){
    if( children[my_root].size() == 0 ) {   // no children; so, size of the node  = 1
      return 1; 
    }
    else{                                   // if there are children in the node
      int my_max = 0;
      for( int i = 0;  i < children[my_root].size();  i++ ){
          int child = children[my_root][i];
          my_max  = MAX( my_max, get_height( child ) );
        }
      return 1 + my_max;
    }
}

int main()
{
	std::ios::sync_with_stdio(0);
	int n; 
	
  cin >> n;
  
  int nodes[n];
  int root;
  
  for( int i = 0; i < n; i++){
      cin >> nodes[i];
      if( nodes[i] == -1 ) {
        root = i;
      }
      else {
        children[nodes[i]].push_back(i);
      }
  }
  cout << get_height( root ) << "\n";
}

