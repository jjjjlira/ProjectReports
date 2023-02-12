/*

WORKED GOOD IN FIRST SUBMISSION!!!!

Course: Data Structures

Week: 3
Problem: 1 Convert array into heap

Problem Introduction
In this problem you will convert an array of integers into a heap. This is the crucial step of the sorting
algorithm called HeapSort. It has guaranteed worst-case running time of 𝑂(𝑛 log 𝑛) as opposed to QuickSort’s
average running time of 𝑂(𝑛 log 𝑛). QuickSort is usually used in practice, because typically it is faster, but
HeapSort is used for external sort when you need to sort huge files that don’t fit into memory of your
computer.

Problem Description

Task. The first step of the HeapSort algorithm is to create a heap from the array you want to sort. By the
way, did you know that algorithms based on Heaps are widely used for external sort, when you need
to sort huge files that don’t fit into memory of a computer?
Your task is to implement this first step and convert a given array of integers into a heap. You will
do that by applying a certain number of swaps to the array. Swap is an operation which exchanges
elements 𝑎𝑖 and 𝑎𝑗 of the array 𝑎 for some 𝑖 and 𝑗. You will need to convert the array into a heap using
only 𝑂(𝑛) swaps, as was described in the lectures. Note that you will need to use a min-heap instead
of a max-heap in this problem.

Input Format. The first line of the input contains single integer 𝑛. The next line contains 𝑛 space-separated
integers 𝑎𝑖.

Constraints. 1 ≤ 𝑛 ≤ 100 000; 0 ≤ 𝑖, 𝑗 ≤ 𝑛 − 1; 0 ≤ 𝑎0, 𝑎1, . . . , 𝑎𝑛−1 ≤ 109. All 𝑎𝑖 are distinct.

Output Format. The first line of the output should contain single integer 𝑚 — the total number of swaps.
𝑚 must satisfy conditions 0 ≤ 𝑚 ≤ 4𝑛. The next 𝑚 lines should contain the swap operations used
to convert the array 𝑎 into a heap. Each swap is described by a pair of integers 𝑖, 𝑗 — the 0-based
indices of the elements to be swapped. After applying all the swaps in the specified order the array
must become a heap, that is, for each 𝑖 where 0 ≤ 𝑖 ≤ 𝑛 − 1 the following conditions must be true:

1. If 2𝑖 + 1 ≤ 𝑛 − 1, then 𝑎𝑖 < 𝑎2𝑖+1.
2. If 2𝑖 + 2 ≤ 𝑛 − 1, then 𝑎𝑖 < 𝑎2𝑖+2.

Note that all the elements of the input array are distinct. Note that any sequence of swaps that has
length at most 4𝑛 and after which your initial array becomes a correct heap will be graded as correct.

Time Limits. C: 1 sec, C++: 1 sec, Java: 3 sec, Python: 3 sec. C#: 1.5 sec, Haskell: 2 sec, JavaScript: 3
sec, Ruby: 3 sec, Scala: 3 sec.

Memory Limit. 512MB.

Sample 1.
Input:
5
5 4 3 2 1
Output:
3
1 4
0 1
1 3
After swapping elements 4 in position 1 and 1 in position 4 the array becomes 5 1 3 2 4.
2
After swapping elements 5 in position 0 and 1 in position 1 the array becomes 1 5 3 2 4.
After swapping elements 5 in position 1 and 2 in position 3 the array becomes 1 2 3 5 4, which is
already a heap, because 𝑎0 = 1 < 2 = 𝑎1, 𝑎0 = 1 < 3 = 𝑎2, 𝑎1 = 2 < 5 = 𝑎3, 𝑎1 = 2 < 4 = 𝑎4.

Sample 2.
Input:
5
1 2 3 4 5
Output:
0
The input array is already a heap, because it is sorted in increasing order.

Starter Files
There are starter solutions only for C++, Java and Python3, and if you use other languages, you need
to implement solution from scratch. Starter solutions read the array from the input, use a quadratic time
algorithm to convert it to a heap and use (𝑛2) swaps to do that, then write the output. You need to replace
the (𝑛2) implementation with an 𝑂(𝑛) implementation using no more than 4𝑛 swaps to convert the array
into heap.

What to Do
Change the BuildHeap algorithm from the lecture to account for min-heap instead of max-heap and for
0-based indexing.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  int parent (int i){
    return floor ( ( i -1 ) / 2 ); 
  }
  
  int leftChild (int i){
    return ( 2 * i + 1 ); 
  }
  
  int rightChild (int i){
    return ( 2 * i + 2 ); 
  }
  
  void siftUp( int i ){
    while ( ( i > 1 ) && ( data_[parent(i)] > data_[i] ) ){
      swap( data_[parent(i)], data_[i] );
      swaps_.push_back( make_pair( data_[parent(i)], data_[i] ) );
    }
  }
  
  void sift_down( int i ){
    int minIndex = i;
    int l = leftChild(i);
    
    if ( ( l < data_.size() ) && ( data_[l] < data_[minIndex] ) ){
      minIndex = l;
    }
    
    int r = rightChild(i);
    if ( ( r < data_.size() ) && ( data_[r] < data_[minIndex] ) ){
      minIndex = r;
    } 
    
    if ( i != minIndex){
      swap(data_[i], data_[minIndex]);
      swaps_.push_back(make_pair(i, minIndex));
      sift_down(minIndex);
    }
  }
  
  int extractMin(){
    int result = data_[0];
    data_[0] =  data_[data_.size()-1];
    data_.resize(data_.size()-1);
    sift_down(0);
    return result;
  }
  
  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    for ( int i = floor( data_.size()/2 ); i >= 0 ; i-- )
    {
      sift_down(i);
    }
    /*
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }*/
  }
  
  void WriteSortedArray() {
    int d_size = data_.size();
    for (int i = 0; i < d_size; ++i) {
      cout << extractMin() << "\n";
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
    //WriteSortedArray();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}

