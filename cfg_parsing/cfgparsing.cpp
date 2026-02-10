//code
#include <vector>
#include <iomanip>
#include <string>
#include <cstdint>
#include <iostream>
#include <map>

using namespace std;

void cyk(const char* s, int n, int start_state, const multimap<unsigned int, unsigned int> & inv_cfg){
    vector<int> table[n][n];

    //go through each row
    for(int i = 0; i < n; ++i){
        //each column in a row (upper left triangle)
        for(int j = 0; j < n - i; ++j){
            if (i == 0) {
                auto res = inv_cfg.equal_range(static_cast<uint16_t>(s[j])); 
                if (res.first == res.second) {table[i][j].push_back(-1);}
                else{
                    for (auto it = res.first; it != res.second; ++it) {
                        table[i][j].push_back(it->second);
                    }
                }
            } else {
                //check all substrings
                for(int k = 1, l = i - 1; k < (i - 1); --l, ++k){
                    if(table[i-k][j].front() == -1 || table[i-l][j+l].front() == -1){ table[i][j].push_back(-1); }
                    else{
                        for(int val1 : table[i-k][j]){
                            for(int val2 : table[i-l][j+l]){
                                auto res = inv_cfg.equal_range(
                                        static_cast<uint16_t>(val1) << 8 | static_cast<uint16_t>(val2)
                                );
                                for (auto it = res.first; it != res.second; ++it) {
                                    table[i][j].push_back(it->second);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (table[n-1][n-1].front() == start_state) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }
}

int main() {
    multimap<unsigned int, unsigned int> inv_cfg;
    int n;
    int start_state;

    cin >> n;

    for(int i = 0; i < n; ++i){
        char cstr[3];
        cin >> setw(3) >> cstr;
        unsigned int variable = static_cast<uint16_t>(cstr[0]);
        
        if (i == 0){
            start_state = variable;
        }
        
        cin >> setw(3) >> cstr;
        unsigned int production = cstr[1] != '\0' ?
            (static_cast<uint16_t>(cstr[0]) << 8 | static_cast<uint16_t>(cstr[1])) :
             static_cast<uint16_t>(cstr[0]);
        inv_cfg.insert({production, variable});
    }

    cin >> n;
    string input;
    for(int i = 0; i < n; ++i){
        cin >> input;
        cyk(input.c_str(), input.size(), start_state, inv_cfg);
    }

    return 0;
}

