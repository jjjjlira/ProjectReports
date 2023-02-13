/*

THIS WORKS!!
Good job! (Max time used: 0.15/3.00) map
Good job! (Max time used: 0.41/3.00) unordered map


Course: Data Structures
Week: 3
Problem: 1 Phone book

Problem Introduction
In this problem you will implement a simple phone book manager.
Problem Description
Task. In this task your goal is to implement a simple phone book manager. It should be able to process the
following types of user’s queries:
∙ add number name. It means that the user adds a person with name name and phone number
number to the phone book. If there exists a user with such number already, then your manager
has to overwrite the corresponding name.
∙ del number. It means that the manager should erase a person with number number from the phone
book. If there is no such person, then it should just ignore the query.
∙ find number. It means that the user looks for a person with phone number number. The manager
should reply with the appropriate name, or with string “not found" (without quotes) if there is
no such person in the book.
Input Format. There is a single integer 𝑁 in the first line — the number of queries. It’s followed by 𝑁
lines, each of them contains one query in the format described above.
Constraints. 1 ≤ 𝑁 ≤ 105. All phone numbers consist of decimal digits, they don’t have leading zeros, and
each of them has no more than 7 digits. All names are non-empty strings of latin letters, and each of
them has length at most 15. It’s guaranteed that there is no person with name “not found".
Output Format. Print the result of each find query — the name corresponding to the phone number or
“not found" (without quotes) if there is no person in the phone book with such phone number. Output
one result per line in the same order as the find queries are given in the input.
Time Limits. C: 3 sec, C++: 3 sec, Java: 6 sec, Python: 6 sec. C#: 4.5 sec, Haskell: 6 sec, JavaScript: 9
sec, Ruby: 9 sec, Scala: 9 sec.
Memory Limit. 512MB.
2
Sample 1.
Input:
12
add 911 police
add 76213 Mom
add 17239 Bob
find 76213
find 910
find 911
del 910
del 911
find 911
find 76213
add 76213 daddy
find 76213
Output:
Mom
not found
police
not found
Mom
daddy
76213 is Mom’s number, 910 is not a number in the phone book, 911 is the number of police, but then
it was deleted from the phone book, so the second search for 911 returned “not found". Also, note that
when the daddy was added with the same phone number 76213 as Mom’s phone number, the contact’s
name was rewritten, and now search for 76213 returns “daddy" instead of “Mom".
Sample 2.
Input:
8
find 3839442
add 123456 me
add 0 granny
find 0
find 123456
del 0
del 0
find 0
Output:
not found
granny
me
not found
Recall that deleting a number that doesn’t exist in the phone book doesn’t change anything.
Starter Files
The starter solutions for C++, Java and Python3 in this problem read the input, implement a naive algorithm
to look up names by phone numbers and write the output. You need to use a fast data structure to implement
3
a better algorithm. If you use other languages, you need to implement the solution from scratch.
What to Do
Use the direct addressing scheme.
Need Help?

*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
using std::map;
using std::iterator;

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, name;
    int number;
};


vector<Query> read_queries() {
    int n;
    cin >> n;
    vector<Query> queries(n);
    for (int i = 0; i < n; ++i) {
        cin >> queries[i].type;
        if (queries[i].type == "add")
            cin >> queries[i].number >> queries[i].name;
        else
            cin >> queries[i].number;
    }
    return queries;
}

void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}


vector<string> process_queries( const vector<Query>& queries ) {
    vector<string> result;
    map<int, string> contacts;
    
    for (size_t i = 0; i < queries.size(); ++i){
        if ( queries[i].type == "add" ) {
            contacts[queries[i].number] = queries[i].name;
        } 
        else if (queries[i].type == "del") {
            contacts.erase(queries[i].number);
        } 
        else {
            string response = "not found";
            map<int, string>::iterator it = contacts.find( queries[i].number );
            if ( it != contacts.end() ) {
                response = it->second;
            }
            result.push_back(response);
        }
    }
    return result;
}


int main() {
    write_responses(process_queries(read_queries()));
    return 0;
}

