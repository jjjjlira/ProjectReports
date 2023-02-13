/*

Course: Data Structures
Week: 3 
Problem: 5 Longest common substring

Good job! (Max time used: 0.92/2.00, max memory used: 162131968/536870912.)


Problem Introduction
In the longest common substring problem one is given two strings 𝑠 and 𝑡 and the goal is to find a string 𝑤
of maximal length that is a substring of both 𝑠 and 𝑡. This is a natural measure of similarity between two
strings. The problem has applications in text comparison and compression as well as in bioinformatics.

The problem can be seen as a special case of the edit distance problem (where only insertions and
deletions are allowed). Hence, it can be solved in time 𝑂(|𝑠| · |𝑡|) using dynamic programming. Later in
this specialization, we will learn highly non-trivial data structures for solving this problem in linear time
𝑂(|𝑠| + |𝑡|). In this problem, your goal is to use hashing to solve it in almost linear time.

Problem Description

Input Format. Every line of the input contains two strings 𝑠 and 𝑡 consisting of lower case Latin letters.

Constraints. The total length of all 𝑠’s as well as the total length of all 𝑡’s does not exceed 100 000.

Output Format. For each pair of strings 𝑠 and 𝑡𝑖, find its longest common substring and specify it by
outputting three integers: its starting position in 𝑠, its starting position in 𝑡 (both 0-based), and its
length. More formally, output integers 0 ≤ 𝑖 < |𝑠|, 0 ≤ 𝑗 < |𝑡|, and 𝑙 ≥ 0 such that 𝑠𝑖𝑠𝑖+1 · · · 𝑠𝑖+𝑙−1 =
𝑡𝑗 𝑡𝑗+1 · · · 𝑡𝑗+𝑙−1 and 𝑙 is maximal. (As usual, if there are many such triples with maximal 𝑙, output any
of them.)

Time Limits. C: 2 sec, C++: 2 sec, Java: 5 sec, Python: 15 sec. C#: 3 sec, Haskell: 4 sec, JavaScript: 10
sec, Ruby: 10 sec, Scala: 10 sec.

Memory Limit. 512MB.

Sample 1.
Input:
cool toolbox
aaa bb
aabaa babbaab
Output:
1 1 3
0 1 0
0 4 3

Explanation:
The longest common substring of the first pair of strings is ool, it starts at the first position in toolbox
and at the first position in cool. The strings from the second line do not share any non-empty common
substrings (in this case, 𝑙 = 0 and one may output any indices 𝑖 and 𝑗). Finally, the last two strings
share a substring aab that has length 3 and starts at position 0 in the first string and at position 4 in
the second one. Note that for this pair of string one may output 2 3 3 as well.

Sample 2.
voteforthegreatalbaniaforyou choosethegreatalbanianfuture
aaa bb
aabaa babbaab


Your output:
7 6 15
3 0 0
0 4 3

What to Do
For every pair of strings 𝑠 and 𝑡, use binary search to find the length of the longest common substring. To
check whether two strings have a common substring of length 𝑘,

∙ precompute hash values of all substrings of length 𝑘 of 𝑠 and 𝑡;

∙ make sure to use a few hash functions (but not just one) to reduce the probability of a collision;

∙ store hash values of all substrings of length 𝑘 of the string 𝑠 in a hash table; then, go through all
substrings of length 𝑘 of the string 𝑡 and check whether the hash value of this substring is present in
the hash table.

*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>    // std::min
#include <vector>

using namespace std;

typedef long long ll;


struct Answer {
	size_t i, j, len;
};


void print_table( const string title, const vector<ll>& Table ){ 
    // Auxiliary function for debugging
    cout <<"\n" << title << " :\n";
    for (size_t i = 0; i < Table.size(); ++i){
        cout << Table[i] << "  ";
    }
    cout << "\n";
}

void print_unordered_map( const string title, const unordered_map<ll,ll>& Table ){ 
    // Auxiliary function for debugging
    cout <<"\n Unordered Map " << title << " :\n";
    for ( auto it = Table.begin(); it != Table.end(); ++it )
        std::cout << " " << it->first << ":" << it->second;
    cout << "\n";
}


ll poly_hash_func( const string& s, const ll p, const ll x ) {
    // Polynomial hash calculation
    ll hash = 0;
    
    for ( ll i = static_cast<ll> ( s.size() ) - 1; i >= 0; --i ) {// polynomial hash function
        hash = ( hash * x + s[i] ) % p;
    }
    return ( hash + p ) % p;
}


void PreCalculate_HashTable ( vector<ll>& H, string full_str, ll sub_str_length, ll p, ll x){
    // Precalculates hashes of a string for all substrings of lenght sub_str_len
    string sub_string( full_str.end() - sub_str_length, full_str.end() );
    vector<ll>X;
    
    H.resize ( full_str.size() -  sub_str_length + 1 );
    X.resize  ( sub_str_length + 1 );
    
    X[0] = 1; // Calculates table of powers of X *** MEMOIZE ******* later for efficiency
    for ( ll i = 1; i <= sub_str_length; ++i){
        X[i] = ( X[i-1] % p ) * x;
    }
    // Initilize last element of the hash table
    H[full_str.size() - sub_str_length] = poly_hash_func( sub_string, p, x );
    
    // Calculates all other elements of the table iteratively in O(1) each
    for  ( ll i = full_str.size() - sub_str_length -1 ; i >=0 ; --i ){
        // recurrence as in improving Ravin-Karp lecture
        // H[i] = xH[i + 1] + (T[i ] − T[i + |P|]x|P|) mod p
        H[i] =  ( ( ( x * H[i+1] + full_str[i] ) - X[sub_str_length] * full_str[i + sub_str_length] ) % p + p ) % p;
    }
    //print_table ( "X[]", X ); // for debugging
}


void PreCalculate_Hash_Unordered_Map ( unordered_map<ll,ll>& H, string full_str, ll sub_str_length, ll p, ll x){
    // Precalculates hashes of a string for all substrings of length sub_str_len in an unordered map
    H.clear();     // clearing the previous unordered_map
    string sub_string( full_str.end() - sub_str_length, full_str.end() );
    vector<ll>X;
    
    X.resize  ( sub_str_length + 1 );
    
    X[0] = 1; // Calculates table of powers of X *** MEMOIZE later for efficiency
    for ( ll i = 1; i <= sub_str_length; ++i){
        X[i] = ( X[i-1] % p ) * x;
    }
    // Initilize last element of the hash table
    ll current;
    ll last = poly_hash_func( sub_string, p, x );
    H[last] = full_str.size() - sub_str_length;
    
    // Calculates all other elements of the table iteratively in O(1) each
    for  ( ll i = full_str.size() - sub_str_length -1 ; i >=0 ; --i ){
        // recurrence as in improving Ravin-Karp lecture
        // H[i] = xH[i + 1] + (T[i ] − T[i + |P|]x|P|) mod p
        current =  ( ( ( x * last + full_str[i] ) - X[sub_str_length] * full_str[i + sub_str_length] ) % p + p ) % p;

        H[current] = i; 
        last = current;
        // beware that dictionaries does not allow duplicates, so if there are repeated substrings inside a string
        // the dictionary will keep ony the latest one calculated
    }
}


struct check_answer {
    bool check;
    unordered_map<ll,ll> matches;
};


check_answer SearchSubstring ( const vector<ll>& hash_table, const unordered_map<ll,ll>& hash_dict ){
    check_answer my_check;
    my_check.check = false;
    // the boolean "my_check.check" returns tru if one or more matches are found
    // the dictionary "my_check.matches" has "key = aStart"  and "value = bStart" for all matches
    for ( ll i = 0;  i< hash_table.size(); ++i){
        if ( hash_dict.count( hash_table[i] ) != 0 ) {
            // first uses "count" method as to check if the item exists as
            // finds method returns "end()" iterator if it doesn't find it in the dictionary
            auto bStart = hash_dict.find( hash_table[i] );
            my_check.check = true;
            my_check.matches[i] = bStart->second;
        }
    }
    return my_check;
}


Answer Get_Max_Length( string s1, string s2, ll low_idx, ll high_idx, ll max_length, ll aStart, ll bStart ){
    // a is long string --> hash table, b is short string --> hash dict
    Answer answer;
    
    ll mid = ( low_idx + high_idx ) / 2 ; // # mid is the length of the tested common substring
    
    if ( low_idx > high_idx ) {
        answer.i   = aStart; 
        answer.j   = bStart;
        answer.len = max_length;
        return answer;
    }
    
    const ll m1 = 1000000007;
    const ll m2 = 100000000019;
    const ll x1 = 263;
    const ll x2 = 31;
    
	vector<ll> Hash_Table_S1m1;
	vector<ll> Hash_Table_S1m2;
	unordered_map<ll, ll> Hash_Unordered_Map_S2m1;
	unordered_map<ll, ll> Hash_Unordered_Map_S2m2;
	check_answer my_check1;
	check_answer my_check2;
	
	PreCalculate_HashTable ( Hash_Table_S1m1, s1, mid, m1, x1 );
    PreCalculate_HashTable ( Hash_Table_S1m2, s1, mid, m2, x2 );
    
    PreCalculate_Hash_Unordered_Map ( Hash_Unordered_Map_S2m1, s2, mid, m1, x1 );
    PreCalculate_Hash_Unordered_Map ( Hash_Unordered_Map_S2m2, s2, mid, m2, x2 );
    
    my_check1 = SearchSubstring( Hash_Table_S1m1, Hash_Unordered_Map_S2m1 );
    my_check2 = SearchSubstring( Hash_Table_S1m2, Hash_Unordered_Map_S2m2 );
    
    if ( my_check1.check ){
        for ( auto my_search : my_check1.matches ){
            if ( my_check2.matches.count( my_search.first ) ){
                //  checks that the same match is found using th second polyhash function in my_check2.matches
                max_length = mid;
                aStart = my_search.first;
                bStart = my_search.second;
                //del aHash1, aHash2, bHash1, bHash2, matches1, matches2
                return Get_Max_Length( s1, s2, mid + 1, high_idx, max_length, aStart, bStart );
            }   //unordered_map<ll,ll>::iterator
        }
    }
    return Get_Max_Length( s1, s2, low_idx, mid - 1, max_length, aStart, bStart );

}

int main() {
	//ios_base::sync_with_stdio(false), cin.tie(0);
	string s1, s2;
	
    while(cin >> s1 >> s2){
        
        ll init_max_len = min ( s1.length(), s2.length() );
        
        string short_str, long_str;
        
        if ( s1.length() <= s2.length() ){
            short_str = s1;
            long_str  = s2;
        }
        else{
            short_str = s2;
            long_str  = s1;
        }
        
        Answer my_answer = Get_Max_Length( long_str, short_str, 0, init_max_len, 0, 0, 0 );
        
        if ( s1.length() > s2.length() ){
            cout << my_answer.i <<  " " << my_answer.j << " " << my_answer.len << "\n"; 
        }
        else{
            cout << my_answer.j <<  " " << my_answer.i << " " << my_answer.len << "\n"; 
        }
    }
}

