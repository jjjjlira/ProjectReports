#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using namespace std;

typedef long long ll;

/*
class Solver {
	string s;
public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
	}
	bool ask(int a, int b, int l) {
		return s.substr(a, l) == s.substr(b, l);
	}
};*/

void  Precompute_Hash_Tables( vector<ll> &hashTable1, vector<ll> &hashTable2, 
							  const string &s, const ll prime1, const ll prime2, vector<ll> &x_power, const ll x ) {
	//vector<ll>hashtable( s.size() + 1 );
    hashTable1[0] = 0;
    hashTable2[0] = 0;
    x_power[0] = 1;
    // polynomial hash function calculated in O(1) each item in the table
    // also calculating x^1, x^2, ... x^length -all x powers-  in O(length)
    for ( ll i = 1; i <= s.size(); ++i ){
        hashTable1[i] = ( x * hashTable1[i - 1] + s[i - 1]  ) % prime1;
        hashTable2[i] = ( x * hashTable2[i - 1] + s[i - 1]  ) % prime2;
        
        // takes advantage of "for" loop to pre calculate powers of x as they will be used later
        x_power[i] = (  ( x_power[i - 1] % prime1 ) * ( x % prime1 ) + prime1  ) %  prime1;
    }
    return;
}


ll HashValue(vector<ll>& hash_table, ll prime, vector<ll>& x, ll start, ll length){
    ll y = x[length];
    ll hash_value = ( hash_table[start + length] - y * hash_table[start] ) % prime;
    // calculates hash value:  𝐻(S𝑎S𝑎+1 ... S𝑎+𝑙−1) =   ℎ[𝑎 + 𝑙]  −  𝑥^𝑙 * ℎ[𝑎]
    return hash_value;
}
    
bool AreEqual( vector<ll>&table1, vector<ll>&table2, ll prime1, ll prime2, vector<ll>&x_power, ll x, ll a, ll b, ll l ){
    ll a_hash1, a_hash2, b_hash1, b_hash2;
    
    a_hash1 = HashValue( table1, prime1, x_power, x, a, l );
    a_hash2 = HashValue( table2, prime2, x_power, x, a, l );
    
    b_hash1 = HashValue( table1, prime1, x_power, x, b, l );
    b_hash2 = HashValue( table2, prime2, x_power, x, b, l );
    
    if ( (a_hash1 == b_hash1 )  && ( a_hash2 == b_hash2 ) ){
        return true;
    }
    else{
        return false;
    }
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	const long long m1 = 1000000007;
    const long long m2 = 1000000009;
    const long long x = 263;
    
	string s;
	int num_queries;
	cin >> s >> num_queries;
	
	vector<long long> hashTable1;
	vector<long long> hashTable2;
	vector<long long> x_power;
	
	Precompute_Hash_Tables( hashTable1, hashTable2, s, m1, x_power, x );
	//print( hash_table1, hash_table2 )

	for ( int i = 0; i < num_queries; i++ ) {
		int a, b, l;
		cin >> a >> b >> l;
		
		cout << ( AreEqual( hashTable1, hashTable2, m1, m2, x_power, x, a, b, l )  ?  "Yes\n"  :  "No\n" );
	}
}
