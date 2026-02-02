#include <unordered_map>
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
        //cout << "adding to node n: " << this->n << " " << symbol << " " << state << endl;
        //cout << "delta: " << endl;
        //for (const auto& [id, name] : delta) {
        //    std::cout << "string : " << id << " state: " << name << std::endl;
        //}
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
            //cout << "N " << this->n << " goes to " << it->second << " on " << EPSILON << endl;
            if(next_states.insert(it->second).second){
                search_states.push_back(it->second);
            }
        }
    }
}

//vector<int> get_next(int n, string symbol, const vector<Node> &nfa) {
//    vector<int> next_states;

    //cout << "symbol: " << symbol << endl;
    //find all next states
//    int len = next_states.size();
//    for(int i = 0; i < len; i++){
//        for (int state : nfa[next_states[i]].eps_closure){
//            next_states.push_back(state);
//        }

  //  }

//    return next_states;
//}


void simulate(string strg, const vector<Node> &nfa) {
    vector<bool> cur_states(nfa.size(), false);
    vector<bool> new_states(nfa.size(), false);

    //cout << endl << "simulation for " << strg << " beginning." << endl;
    
    cur_states[START_STATE] = true;
    for(int state : nfa[START_STATE].eps_closure) {
        cur_states[state] = true;
    }
    
    for(const char& c : strg){
        fill(new_states.begin(), new_states.end(), false);

        for(int i = 0; i < nfa.size(); ++i){
            if(!cur_states[i]) continue;
           
            auto [begin_it, end_it] = nfa[i].delta.equal_range(string(1, c));
            for(auto it = begin_it; it != end_it; ++it){
                //cout << "N " << this->n << " goes to " << it->second << " on " << symbol << endl;
                new_states[it->second] = true;
                for(int eps : nfa[it->second].eps_closure){
                    new_states[eps] = true;
                }
            }


        }
        cur_states = new_states;

    }


    for(int i = 0; i < nfa.size(); ++i){
        if(cur_states[i] && nfa[i].f) {
            cout << "accept" << endl;
            return;
        }
    }
    cout << "reject" << endl;

    //cout << endl << endl;
    return;
}


int main() {
    vector<Node> nfa;

    int n, m, f;

    cin >> n;
    cin >> m;

    for(int i = 0; i < n; i++){
        nfa.emplace_back(i);
    }

    //cout << n << " " << m << " " << endl;

    int a, c;
    string b;
    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        //idx with a to map of nodes
        //add b -> c to transition function (delta) map
        //cout << a << " " << b << " " << c << endl;
        nfa[a].insert_delta(b, c);
    }

    cin >> f;
    for(int i = 0; i < f; i++){
        cin >> a;
        nfa[a].f = true;
        //cout << "setting final state: " << a << " " << nfa[a].f << endl;
        //insert a to set of final states
    }

    for(int i = 0; i < n; ++i){
        set<int> eps_closure;
        follow_epsilon(i, eps_closure, nfa); 
        nfa[i].eps_closure = eps_closure;
    }
   
    int s;
    cin >> s;
    string strg;
    cin.ignore();
    for(int i = 0 ;i < s; i++){
        getline(cin, strg);
        simulate(strg, std::ref(nfa));
        //cout << strg << endl;
    }

    return 0;
}

