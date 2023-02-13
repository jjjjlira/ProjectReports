
/*
Course: Data Structures
Week: 3 
Problem: 3 Find pattern in text

"Rabin–Karp’s algorithm" implementation 


Problem Introduction
In this problem, your goal is to implement the Rabin–Karp’s algorithm.

Problem Description

Task. In this problem your goal is to implement the Rabin–Karp’s algorithm for searching the given pattern
in the given text.

Input Format. There are two strings in the input: the pattern 𝑃 and the text 𝑇.

Constraints. 1 ≤ |𝑃| ≤ |𝑇| ≤ 5 · 105. The total length of all occurrences of 𝑃 in 𝑇 doesn’t exceed 108. The
pattern and the text contain only latin letters.

Output Format. Print all the positions of the occurrences of 𝑃 in 𝑇 in the ascending order. Use 0-based
indexing of positions in the the text 𝑇.

Time Limits. C: 1 sec, C++: 1 sec, Java: 5 sec, Python: 5 sec. C#: 1.5 sec, Haskell: 2 sec, JavaScript: 3
sec, Ruby: 3 sec, Scala: 3 sec.

Memory Limit. 512MB.

Sample 1.
Input:
aba
abacaba
Output:
0 4
Explanation:
The pattern 𝑎𝑏𝑎 can be found in positions 0 (abacaba) and 4 (abacaba) of the text 𝑎𝑏𝑎𝑐𝑎𝑏𝑎.

Sample 2.
Input:
Test
testTesttesT
Output:
4
Explanation:
Pattern and text are case-sensitive in this problem. Pattern 𝑇𝑒𝑠𝑡 can only be found in position 4 in
the text 𝑡𝑒𝑠𝑡𝑇 𝑒𝑠𝑡𝑡𝑒𝑠𝑇 .

Sample 3.
Input:
aaaaa
baaaaaaa
Output:
1 2 3
Note that the occurrences of the pattern in the text can be overlapping, and that’s ok, you still need
to output all of them.
9

Starter Files
The starter solutions in C++, Java and Python3 read the input, apply the naive 𝑂(|𝑇||𝑃|) algorithm to
this problem and write the output. You need to implement the Rabin–Karp’s algorithm instead of the naive
algorithm and thus significantly speed up the solution. If you use other languages, you need to implement a
solution from scratch.

What to Do
Implement the fast version of the Rabin–Karp’s algorithm from the lectures.
Some hints based on the problems encountered by learners:

∙ Beware of integer overflow. Use long long type in C++ and long type in Java where appropriate. Take
everything (mod 𝑝) as soon as possible while computing something (mod 𝑝), so that the numbers are
always between 0 and 𝑝 − 1.

∙ Beware of taking negative numbers (mod 𝑝). In many programming languages, (−2)%5 ̸= 3%5. Thus
you can compute the same hash values for two strings, but when you compare them, they appear to
be different. To avoid this issue, you can use such construct in the code: 𝑥 ← ((𝑎%𝑝) + 𝑝)%𝑝 instead
of just 𝑥 ← 𝑎%𝑝.

∙ Use operator == in Python instead of implementing your own function AreEqual for strings, because
built-in operator == will work much faster.

∙ In C++, method substr of string creates a new string, uses additional memory and time for that,
so use it carefully and avoid creating lots of new strings. When you need to compare pattern with
a substring of text, do it without calling substr.

∙ In Java, however, method substring does NOT create a new String. Avoid using new String where
it is not needed, just use substring.

*/

#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;


size_t poly_hash_func( const string& s, const size_t p, const size_t x ) {
    // static const size_t x = 3;
    //static const size_t prime = 100000000019;
    unsigned long long hash = 0;
    // polynomial hash function
    for ( int i = static_cast<int> ( s.size() ) - 1; i >= 0; --i )
        hash = ( hash * x + s[i] ) % p;
    return ( hash % p + p ) % p;
}

std::vector<size_t> compute_hashes( const string &text, const size_t psize,
                                      const size_t p, const size_t x ) {
    // Dynamically compute hashes to save time.
    size_t size = text.size() - psize + 1;
    std::vector<size_t> hashes( size );
    // Initialize last hash
    auto begin = text.begin() + size - 1;
    auto end = text.end();
    std::string last( begin, end );
    hashes[size - 1] = poly_hash_func( last, p, x );
    
    // Dynamically compute hashes: h_{k-1} = x*h_k + text_{k-1} - text_{k+p-1}*x^p mod p
    // Precoumpute x^psize
    long long x_to_psize = 1;
    
    for ( int i = 1; i <= psize; ++i ) {
        x_to_psize = ( x_to_psize * x ) % p;
    }
    for ( int k = (int)size - 1; k > 0; --k ) {
        hashes[k - 1] = ( x * hashes[k] + text[k - 1] - text[k + psize - 1] * x_to_psize ) % p;
        // Normalize mod p value to positive representative.
        hashes[k - 1] = ( hashes[k - 1] + p ) % p;
    }
    return hashes;
}

struct Data {
    string pattern, text;
};


Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}


void print_occurrences( const std::vector<int>& output ) {
    for ( size_t i = 0; i < output.size(); ++i ){
        std::cout << output[i] << " ";
    }
    std::cout << "\n";
}


std::vector<int> get_occurrences( const Data& input ) {
    const   string& s = input.pattern;
    const   string& t = input.text;
    size_t  size_of_s = s.size();
    size_t  size_of_t = t.size();
    size_t  p_hash    = poly_hash_func( s, 100000000019, 3 );
    size_t  t_hash;
    std::vector<size_t> text_hashes_precomputed = compute_hashes( input.text, size_of_s, 100000000019, 3 );
    
    //string  t_substr;
    
    std::vector<int> ans;
    
    for ( size_t i = 0; i <= ( size_of_t - size_of_s ) ; ++i ){
        
        //t_substr = t.substr( i,  size_of_s );
        auto first = t.begin() + i;
        auto last  = t.begin() + i + size_of_s;
        std::string t_substr( first, last );            // this is faster than std::string::substr method 
        //t_hash = poly_hash_func( t_substr, 100000000019, 3  );
        
        if ( text_hashes_precomputed[i] == p_hash ){
            if ( t_substr == s ){
                ans.push_back( i );
            }
        }
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio( false );
    print_occurrences( get_occurrences( read_input() ) );
    return 0;
}

