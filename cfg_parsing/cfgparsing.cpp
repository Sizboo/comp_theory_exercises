//code
#include <vector>
#include <string>
#include <iostream>
#include <map>

using namespace std;

void cyk(string s, const map<unsigned int, unsigned int> & inv_cfg){
    int n = s.size();
    vector<int> table[n];

    //go through each row
    for(int i = 0; i < n; ++i){
        //each column in a row (upper left triangle)
        for(int j = 0; j < n - i; ++j){
            //check all substrings
            for(int k = 1, l = i - 1; k < (i - 1); --l, ++k){


            }
        }
    }
}

int main() {

    //this way I can build indexes to the inv_cfg
    unsigned int first = 'A';
    unsigned int second = 'B';

    unsigned int result = first << 8 | second;

    cout << "First: " << hex << first << endl;
    cout << "Second: " << hex << second << endl;
    cout << "Result: " << hex << result << endl;

    return 0;
}

