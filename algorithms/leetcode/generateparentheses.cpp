#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <stack>
#include <unordered_map>

using namespace std;

set<string> results;

bool check_solution(string &arr)
{
    int c = 0;
    for (auto item : arr) {
        if (item == '(') {
            c++;
        }
        else {
            c--;
        }

        if (c < 0) {
            return false;
        }
    }

    return (c == 0) ? true : false;
}

void swp(string &s, size_t a, size_t b)
{
    char tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}

/* I need to revisit this solution later. It passes all testcases but performance is
 * not the best. It basically does DFS to permut all possibilities with memoization
 * to skip known solutions.
 */
void permutations(string &par, size_t begin)
{
    stack<pair<string, size_t>> stk;
    stk.emplace(pair<string, size_t>(par, 0));
    results.insert(par);

    unordered_map<string, set<size_t>> mem;

    int i = 0;
    while (!stk.empty()) {
        auto item = stk.top();
        stk.pop();

        string parentheses = item.first;
        size_t idx = item.second;

        for (size_t i = idx + 1; i < parentheses.size(); i++) {
            swp(parentheses, idx, i);
            bool is_valid = check_solution(parentheses);
            bool is_first = mem.find(parentheses) == mem.end() || mem[parentheses].find(idx + 1) == mem[parentheses].end();
            if (is_valid && is_first) {
                stk.emplace(pair<string, size_t>(parentheses, idx + 1));
                mem[parentheses].insert(idx + 1);
                results.insert(parentheses);
            }
            swp(parentheses, idx, i);
        }
    }
}

void generate(int n)
{
    string par(n * 2, 0);
    for (size_t i = 0; i < n; i++) {
        par[i] = '(';
    }

    for (size_t i = n; i < par.size(); i++) {
        par[i] = ')';
    }

    permutations(par, 0);
}
