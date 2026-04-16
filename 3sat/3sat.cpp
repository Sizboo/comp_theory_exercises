#include <iostream>
#include <tuple>
#include <vector>
#include <string>

using namespace std;


typedef vector<tuple<unsigned int, unsigned int, unsigned int>> expression;

const unsigned int MAX_ASSIGN = (1 << 26);
const unsigned int NOT_BIT = 27;

unsigned int get_val(string &var) {
    unsigned int val = 0;
    if(var[0] == '!') {
        val = val | (1U << NOT_BIT);
        var[0] = var[1];
    }
    val = val | (1 << (static_cast<int>(var[0]) - 'a'));
    return val;
}

bool get_assign(unsigned int set, const unsigned int var ){
    bool assign = (set & (var & ~(1U << NOT_BIT))) != 0;
    return ((var >> NOT_BIT) & 1U)? !assign : assign;
}

bool eval_clause(int i, unsigned int set, const expression & exp){
    if (i >= exp.size()) { return true; }
    
    if (get_assign(set, get<0>(exp[i])) ||
        get_assign(set, get<1>(exp[i])) ||
        get_assign(set, get<2>(exp[i]))) {

        return eval_clause(i+1, set, exp);
    }
    return false;
}

bool evaluator(const expression & exp) {
    for (int i = 0; i <= MAX_ASSIGN; ++i){
        if (eval_clause(0, i, exp)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    expression exp;

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string var1, var2, var3;
        cin >> var1 >> var2 >> var3;

        exp.push_back(
            make_tuple(
                    get_val(var1), 
                    get_val(var2), 
                    get_val(var3)
            )
        );
    }

//     cout << endl << "Outputing: " << n << " clauses" << endl;
//     for (const auto& [var1, var2, var3] : exp) {
//         cout << var1 << " " << var2 << " " << var3 << "\n";
//     }

    if (evaluator(exp)) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}
