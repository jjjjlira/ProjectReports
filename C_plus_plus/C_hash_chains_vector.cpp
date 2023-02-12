/*

THIS WORKS!!
//Good job! (Max time used: 0.15/3.00) map

// using chaining ( the hash map is a VECTOR OF VECTORS in this case, INSEAD of LINKED LIST) 


Course: Data Structures
Week: 3 
Problem: 2 Hashing with chains

Problem Introduction
In this problem you will implement a hash table using the chaining scheme. Chaining is one of the most
popular ways of implementing hash tables in practice. The hash table you will implement can be used to
implement a phone book on your phone or to store the password table of your computer or web service (but
don’t forget to store hashes of passwords instead of the passwords themselves, or you will get hacked!).

Problem Description

Task. In this task your goal is to implement a hash table with lists chaining. You are already given the
number of buckets 𝑚 and the hash function. It is a polynomial hash function

    ℎ(𝑆) =
⎛
⎝
    |𝑆Σ︁|−1
    𝑖=0
    𝑆[𝑖]𝑥𝑖 mod 𝑝
⎞
⎠ mod 𝑚,
where 𝑆[𝑖] is the ASCII code of the 𝑖-th symbol of 𝑆, 𝑝 = 1 000 000 007 and 𝑥 = 263. Your program
should support the following kinds of queries:

∙ add string — insert string into the table. If there is already such string in the hash table, then
just ignore the query.

∙ del string — remove string from the table. If there is no such string in the hash table, then
just ignore the query.

∙ find string — output “yes" or “no" (without quotes) depending on whether the table contains
string or not.

∙ check 𝑖 — output the content of the 𝑖-th list in the table. Use spaces to separate the elements of
the list. If 𝑖-th list is empty, output a blank line.
When inserting a new string into a hash chain, you must insert it in the beginning of the chain.

Input Format. There is a single integer 𝑚 in the first line — the number of buckets you should have. The
next line contains the number of queries 𝑁. It’s followed by 𝑁 lines, each of them contains one query
in the format described above.

Constraints. 1 ≤ 𝑁 ≤ 105; 𝑁
5 ≤ 𝑚 ≤ 𝑁. All the strings consist of latin letters. Each of them is non-empty
and has length at most 15.

Output Format. Print the result of each of the find and check queries, one result per line, in the same
order as these queries are given in the input.

Time Limits. C: 1 sec, C++: 1 sec, Java: 5 sec, Python: 7 sec. C#: 1.5 sec, Haskell: 2 sec, JavaScript: 7
sec, Ruby: 7 sec, Scala: 7 sec.

Memory Limit. 512MB.
5

Sample 1.
Input:
5
12
add world
add HellO
check 4
find World
find world
del world
check 4
del HellO
add luck
add GooD
check 2
del good
Output:
HellO world
no
yes
HellO
GooD luck
The ASCII code of ’w’ is 119, for ’o’ it is 111, for ’r’ it is 114, for ’l’ it is 108, and for ’d’
it is 100. Thus, ℎ(“world") = (119 + 111 × 263 + 114 × 2632 + 108 × 2633 + 100 × 2634 mod
1 000 000 007) mod 5 = 4. It turns out that the hash value of 𝐻𝑒𝑙𝑙𝑂 is also 4. Recall that we always
insert in the beginning of the chain, so after adding “world" and then “HellO" in the same
chain index 4, first goes “HellO" and then goes “world". Of course, “World" is not found, and
“world" is found, because the strings are case-sensitive, and the codes of ’W’ and ’w’ are different.
After deleting “world", only “HellO" is found in the chain 4. Similarly to “world" and “HellO",
after adding “luck" and “GooD" to the same chain 2, first goes “GooD" and then “luck".

Sample 2.
Input:
4
8
add test
add test
find test
del test
find test
find Test
add Test
find Test
Output:
yes
no
no
yes
Adding “test" twice is the same as adding “test" once, so first find returns “yes". After del, “test" is
6
no longer in the hash table. First time find doesn’t find “Test” because it was not added before, and
strings are case-sensitive in this problem. Second time “Test” can be found, because it has just been
added.

Sample 3.
Input:
3
12
check 0
find help
add help
add del
add add
find add
find del
del del
find del
check 0
check 1
check 2
Output:
no
yes
yes
no
add help
Explanation:
Note that you need to output a blank line when you handle an empty chain. Note that the strings
stored in the hash table can coincide with the commands used to work with the hash table.

Starter Files
There are starter solutions only for C++, Java and Python3, and if you use other languages, you need
to implement solution from scratch. Starter solutions read the input, do a full scan of the whole table to
simulate each find operation and write the output. This naive simulation algorithm is too slow, so you need
to implement the real hash table.

What to Do
Follow the explanations about the chaining scheme from the lectures. Remember to always insert new strings
in the beginning of the chain. Remember to output a blank line when check operation is called on an empty
chain.
Some hints based on the problems encountered by learners:
∙ Beware of integer overflow. Use long long type in C++ and long type in Java where appropriate. Take
everything (mod 𝑝) as soon as possible while computing something (mod 𝑝), so that the numbers are
always between 0 and 𝑝 − 1.
7
∙ Beware of taking negative numbers (mod 𝑝). In many programming languages, (−2)%5 ̸= 3%5. Thus
you can compute the same hash values for two strings, but when you compare them, they appear to
be different. To avoid this issue, you can use such construct in the code: 𝑥 ← ((𝑎%𝑝) + 𝑝)%𝑝 instead
of just 𝑥 ← 𝑎%𝑝.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

struct Query {
    string type, s;
    size_t ind;
};

class QueryProcessor {
private:
    int bucket_count;
    // using chaining ( the hash map is a vector of vectors in this case, instead of linked list) 
    vector<vector<string>> Hashmap = vector<vector<string>>( bucket_count );
    
    size_t hash_func( const string& s ) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        
        for ( int i = static_cast<int> ( s.size()) - 1; i >= 0; --i ){
            hash = ( hash * multiplier + s[i] ) % prime;
        }
        return hash % bucket_count;
    }
    
public:
    explicit QueryProcessor( int bucket_count ): bucket_count( bucket_count ) {}
    // explicit contructor, are only considered during direct initialization 
    // (which includes explicit conversions such as static_cast).
    Query readQuery() const {
        Query query;
        cin >> query.type;
        if ( query.type != "check" )
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }
    
    void writeSearchResult( bool was_found ) const {
        std::cout << ( was_found ? "yes\n" : "no\n" );
    }
    
    void processQuery(const Query& query) {
        if ( query.type == "check" ) {
            if ( Hashmap[query.ind].size() != 0 ) {
                // use reverse order, because we append strings to the end
                // static_cast<new_type>(expression) returns the imaginary 
                // variable Temp initialized as if by new_type Temp(expression);
                for ( int i = static_cast<int>( Hashmap[query.ind].size() ) - 1; i >= 0; --i ){
                    cout << Hashmap[query.ind][i] << " ";
                }
            }
            cout << "\n";
        } 
        else {
            size_t ind = hash_func( query.s ); // index of has table is the calculated hash of the query
            
            // iterate on the linked list chain ( in this case is a vector inside a vector )
            vector<string>::iterator it = std::find( Hashmap[ind].begin(), Hashmap[ind].end(), query.s );
            
            if ( query.type == "find" ){
                writeSearchResult( it != Hashmap[ind].end() );
            }
            else if ( query.type == "add" ) {
                if ( it == Hashmap[ind].end() )
                    Hashmap[ind].push_back( query.s );
            } 
            else if ( query.type == "del" ) {
                if ( it != Hashmap[ind].end() ){
                    Hashmap[ind].erase( it );
                }
            }
        }
    }
    
    void processQueries() {
        int n;
        cin >> n;
        for ( int i = 0; i < n; ++i ){
            processQuery( readQuery() );
        }
    }
};

int main() {
    
    std::ios_base::sync_with_stdio( false );
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor my_Queries( bucket_count );// direct initialization of class (for explicit constructor)
    my_Queries.processQueries();
    return 0;
}

