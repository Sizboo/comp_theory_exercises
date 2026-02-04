#include <unordered_map>
#include <utility>
#include <sstream>
#include <map>
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

const int START_STATE = 0;
const string EPSILON = "eps";

struct Node {
    int n;
    bool f;
    unordered_multimap <string, int> delta;
    set<int> eps_closure;

    Node() = default;

    Node(int n) {
        this->n = n;
        this->f = false;
    }

    void insert_delta(string symbol, int state) {
        this->delta.emplace(symbol, state);
    }

    bool operator<(const Node& other) const {
        if (this->f != other.f) {
            return f > other.f;
        }

        return this->n < other.n;
    }

};

void follow_epsilon(int n, set<int> &next_states, const vector<Node> &nfa) {
    //follow all epsilon transitions
    //vector<int> search_states(next_states.begin(), next_states.end());
    vector<int> search_states;
    search_states.push_back(n);

    while(!search_states.empty()){
        int next = search_states.back();
        search_states.pop_back();

        auto [it_begin, it_end] = nfa[next].delta.equal_range(EPSILON);

        for(auto it = it_begin; it != it_end; ++it){
            if(next_states.insert(it->second).second){
                search_states.push_back(it->second);
            }
        }
    }
}

void build_determ(const set<string> &sigma, const vector<Node> &nfa, ostringstream & oss, int &n, int &m) {
    vector<bool> cur_states(nfa.size(), false);
    vector<bool> new_states(nfa.size(), false);

    int num_final = 0;
    n =0;
    m = 0;
    bool f = nfa[START_STATE].f;
    cur_states[START_STATE] = true;
    for(int state : nfa[START_STATE].eps_closure) {
        cur_states[state] = true;
        if (nfa[state].f) f = true;
    }
    if (f) ++num_final;

    vector<vector<bool>> search_states = { cur_states };
    int q = 0;
    map<vector<bool>, pair<int, bool>> determ_map = {{cur_states, {q, f}}};
    ++q;

    while(!search_states.empty()){
        vector<bool> next = search_states.back();
        search_states.pop_back();

        
        for(auto it = sigma.begin(); it != sigma.end(); ++it){
            f = false;
            fill(new_states.begin(), new_states.end(), false);
            for(int i = 0; i < nfa.size(); ++i){
                if(!next[i]) continue;
          

                auto [begin_it, end_it] = nfa[i].delta.equal_range(*it);
                for(auto it = begin_it; it != end_it; ++it){
                    new_states[it->second] = true;
                    if (nfa[it->second].f) f = true;
                    for(int eps : nfa[it->second].eps_closure){
                        new_states[eps] = true;
                        if (nfa[eps].f) f = true;
                    }
                }
            } 


            if(determ_map.insert({new_states, {q, f}}).second){
                search_states.push_back(new_states);
                ++q;
                if (f) ++num_final;
            }

            oss << determ_map[next].first << " " << *it << " " << determ_map[new_states].first << "\n";
            m += 1;
              
        }
        
    }
    n = determ_map.size();
    oss << n - num_final << "\n";
    for(auto it = determ_map.begin(); it != determ_map.end(); ++it){
        if(!it->second.second){
            oss << it->second.first << "\n";
        }
    }



    return;
}


int main() {
    vector<Node> nfa;
    set <string> sigma;
    ostringstream oss;

    int n, m, f;

    cin >> n;
    cin >> m;

    for(int i = 0; i < n; i++){
        nfa.emplace_back(i);
    }


    int a, c;
    string b;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if(b != EPSILON){
            sigma.insert(b);
        }
        nfa[a].insert_delta(b, c);
    }

    cin >> f;
    for(int i = 0; i < f; i++){
        cin >> a;
        nfa[a].f = true;
    }

    for(int i = 0; i < n; ++i){
        set<int> eps_closure;
        follow_epsilon(i, eps_closure, nfa); 
        nfa[i].eps_closure = eps_closure;
    }

    build_determ(sigma, nfa, oss, n, m); 
    
    cout << n << "\n" << m << "\n";
    cout << oss.str();
    cout.flush();

    return 0;
}

