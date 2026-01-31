// code bby

#include <unordered_map>
#include <iostream>
#include <string>
#include <set>

using namespace std;

//low key unnecessary. We can just map<int,delta> since I'm not constructing
//with *.
//struct Node {
//    int n;
//    unordered_map<char,int> delta;
//};

int main() {
    unordered_map<int, unordered_map<string, int>> nfa;
    set<int> F;

    int n, m, f;

    cin >> n;
    cin >> m;

    int a, c;
    string b;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        //idx with a to map of nodes
        //add b -> c to transition function (delta) map
        if(!(nfa.insert({a, {b, c}}).second)){
            cout << "not inserted" << endl;
        }
    }

    cin >> f;
    int a;
    for(int i = 0; i < f; i++){
        cin >> a;
        //insert a to set of final states
    }
    

    

    return 0;
}

