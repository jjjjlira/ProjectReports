/*

Good job! (Max time used: 0.56/2.00, max memory used: 11309056/536870912.)
Good job! (Max time used: 0.57/2.00, max memory used: 11304960/536870912.)

Course: Data Structures
Week: 3 
Problem: 6 Pattern matching with mismatches


Problem Introduction
A natural generalization of the pattern matching problem is the following: find all text locations where distance
from pattern is sufficiently small. This problems has applications in text searching (where mismatches
correspond to typos) and bioinformatics (where mismatches correspond to mutations).

Problem Description

Task. For an integer parameter 𝑘 and two strings 𝑡 = 𝑡0𝑡1 · · · 𝑡𝑚−1 and 𝑝 = 𝑝0𝑝1 · · · 𝑝𝑛−1, we say that
𝑝 occurs in 𝑡 at position 𝑖 with at most 𝑘 mismatches if the strings 𝑝 and 𝑡[𝑖 : 𝑖 + 𝑝) = 𝑡𝑖𝑡𝑖+1 · · · 𝑡𝑖+𝑛−1
differ in at most 𝑘 positions.

Input Format. Every line of the input contains an integer 𝑘 and two strings 𝑡 and 𝑝 consisting of lower
case Latin letters.

Constraints. 0 ≤ 𝑘 ≤ 5, 1 ≤ |𝑡| ≤ 200 000, 1 ≤ |𝑝| ≤ min{|𝑡|, 100 000}. The total length of all 𝑡’s does not
exceed 200 000, the total length of all 𝑝’s does not exceed 100 000.

Output Format. For each triple (𝑘, 𝑡, 𝑝), find all positions 0 ≤ 𝑖1 < 𝑖2 < · · · < 𝑖𝑙 < |𝑡| where 𝑝 occurs in 𝑡
with at most 𝑘 mismatches. Output 𝑙 and 𝑖1, 𝑖2, . . . , 𝑖𝑙.

Time Limits. C: 2 sec, C++: 2 sec, Java: 5 sec, Python: 40 sec. C#: 3 sec, Haskell: 4 sec, JavaScript: 10
sec, Ruby: 10 sec, Scala: 10 sec.

Memory Limit. 512MB.

Sample 1.

Input:
0 ababab baaa
1 ababab baaa
1 xabcabc ccc
2 xabcabc ccc
3 aaa xxx

Output:
0
1 1
0
4 1 2 3 4
1 0

Explanation:
For the first triple, there are no exact matches. For the second triple, baaa has distance one from the
pattern. For the third triple, there are no occurrences with at most one mismatch. For the fourth triple,
any (length three) substring of 𝑝 containing at least one c has distance at most two from 𝑡. For the
fifth triple, 𝑡 and 𝑝 differ in three positions.

What to Do
Start by computing hash values of prefixes of 𝑡 and 𝑝 and their partial sums. This allows you to compare any
two substrings of 𝑡 and 𝑝 in expected constant time. For each candidate position 𝑖, perform 𝑘 steps of the
form “find the next mismatch”. Each such mismatch can be found using binary search. Overall, this gives an
algorithm running in time 𝑂(𝑛𝑘 log 𝑛).

*/

#include <iostream> // std::cout
#include <math.h>   // floor
#include <string>   // std::string
#include <vector>   // std::vector

using std::string;
using std::vector;
using namespace std;

typedef long long ll;


class Solver {
    int k;
	string s, p;
	const long long m1 = 1000000007;
	const long long m2 = 1000000007;
    //const long long m2 = 1000000009;
    const long long x = 263;
    //long long x = rand() % 10000000 ;
	vector<long long> hashTable1;
	vector<long long> hashTable2;
	vector<long long> x_power1;
	vector<long long> x_power2;
	//pair<ll,vector<ll>> results; // pair<number of mismatches, vector of starting positions of mismatches>
	vector<ll> results;
	int coincidences = 0;


public:	
	Solver( int k, string s, string p ) : k(k), s(s), p(p) {	// constructor also initializse and precomputes hashes
		
		Precompute_Hash_Tables();
		get_Results();
	}

    void Precompute_Hash_Tables() {

        hashTable1.resize( s.size() + 1 );
        hashTable2.resize( p.size() + 1 );
        x_power1.resize  ( s.size() + 1 );
        x_power2.resize  ( p.size() + 1 );
        hashTable1[0] = hashTable2[0] = 0;
        x_power1[0] = x_power2[0] = 1;
        
        // polynomial hash function calculated in O(1) each item in the table: polyhash function for each substring 
        // ℎ1[𝑖] = 𝐻(𝑠0 · · · 𝑠𝑖−1)
        // ℎ1[𝑖] ← (𝑥 · ℎ1[𝑖 − 1] + 𝑠𝑖) mod 𝑚1
        // also calculating x^1, x^2, ... x^length -all x powers-  in O(length)
        for ( size_t i = 1; i <= s.size(); ++i ){   // calculates hash table for for text "s"
            
            hashTable1[i] = ( x * hashTable1[i - 1] + s[i - 1]  ) % m1;

            // takes advantage of "for" loop to pre calculate powers of x as they will be used later
            x_power1[i] = (  ( x_power1[i - 1] % m1 ) * ( x % m1 ) + m1  ) %  m1;
        }
        
        for ( size_t i = 1; i <= p.size(); ++i ){// calculates hash table for for pattern "p"
            
             hashTable2[i] = ( x * hashTable2[i - 1] + p[i - 1]  ) % m2;
 
            // takes advantage of "for" loop to pre calculate powers of x as they will be used later
                        x_power2[i] = (  ( x_power2[i - 1] % m2 ) * ( x % m2 ) + m2  ) %  m2;
        }
        return;
    }
    
    long long HashValue( int table_ID , ll start, ll length){
        ll hash_value, y;
        
        if (table_ID == 1){
            y = x_power1[length];
            hash_value = ( ( ( hashTable1[start + length] - y * hashTable1[start] ) % m1 ) + m1 ) % m1;
            // calculates hash value:  𝐻(S𝑎S𝑎+1 ... S𝑎+𝑙−1) =   ℎ[𝑎 + 𝑙]  −  𝑥^𝑙 * ℎ[𝑎]
        }
        else if (table_ID == 2){
            y = x_power2[length];
            hash_value = ( ( ( hashTable2[start + length] - y * hashTable2[start] ) % m2 ) + m2 ) % m2;
            // calculates hash value:  𝐻(S𝑎S𝑎+1 ... S𝑎+𝑙−1) =   ℎ[𝑎 + 𝑙]  −  𝑥^𝑙 * ℎ[𝑎]
        }
        return hash_value;
    }
    

    bool AreEqual( ll a, ll b, ll l ){
        ll sub_str_a_hash1, sub_str_a_hash2, sub_str_b_hash1, sub_str_b_hash2;
    
        sub_str_a_hash1 = HashValue( 1, a, l ); //Table_ID = 1; so it uses HAsTable 1 m1 and X_power1
        sub_str_b_hash1 = HashValue( 2, b, l ); //Table_ID = 1; so it uses HAsTable 1 m1 and X_power1

        if ( sub_str_a_hash1 == sub_str_b_hash1 )  {
            return true;
        }
        else{
            return false;
        }
    }
    
    bool AreEqual_2( ll a, ll b, ll l ){
        ll sub_str_a_hash1, sub_str_a_hash2, sub_str_b_hash1, sub_str_b_hash2;
    
        sub_str_a_hash1 = HashValue( 1, a, l ); //
        sub_str_b_hash1 = HashValue( 2, b, l ); //

        if ( sub_str_a_hash1 == sub_str_b_hash1 )  {
            return true;
        }
        else{
            return false;
        }
    }
    

    int how_many_coincidences_optimized( ll index, ll left, int right  ) {
        // 1st call index = i; left = 0, right = p.lenght()-1
        ll mid;                                        
        int mismatches = 0;

        if ( left > right )
            return 0;
        
        else if ( left == right ){
            if ( s.at( index + left ) == p.at( left ) ) { 
                return 0;           // if both text and pattern have only one character and are equal
            }
            else{ 
                return 1;           // if both text and pattern have only one character and are equal       
            }
        }
        
        else if ( HashValue( 1, index + left, right - left + 1) == HashValue( 2, left, right - left + 1 ) ) { 
            return 0;               // if both text and pattern are equal
        }

        else {

            mid = left + floor( ( right - left ) / 2 ); 

            if ( s.at( index + mid ) != p.at( mid ) ){
                
                ++mismatches;
                if ( mismatches > k ){
                    return mismatches;
                }
            }
            
            if ( mismatches > k ){
                return mismatches;
            }
            
            mismatches = mismatches + how_many_coincidences_optimized( index,  left    ,  mid - 1 );
            
            if (mismatches > k){
                return mismatches;
            }

            mismatches = mismatches + how_many_coincidences_optimized( index,  mid + 1 ,  right   );
            return mismatches;
        }
        
    }

     
    void get_Results() {
  
        for ( ll i = 0;  i <= s.length() - p.length() ;  ++i ){ 
            if ( how_many_coincidences_optimized( i, 0, p.length() -1 ) <= k ){
                results.push_back( i ); 
            }
        }
    }
    
    void print_results(){
        cout << results.size() << " ";
        for (size_t i = 0; i < results.size(); ++i){
            cout << results[i] << " ";
        }
    }

};

int main() {
	//ios_base::sync_with_stdio(false), cin.tie(0);
	int k;          // number of mismatches allwed
	string t;       // text
	string p;       // pattern
	
	while ( cin >> k >> t >> p ) {
	    
	    Solver solution( k, t, p );

		solution.print_results();
		cout << "\n";
	}
}
