#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>

using namespace std;

const vector<int> existing_coins = {1, 5, 12, 19};
//const vector<int> existing_coins = {7, 2, 3, 6};

enum class results : int
{
    OK,
    MISS,
    OVER
};

results valid_solution(const vector<int> &coins, int change)
{
    int sum = 0;
    for (auto coin : coins) {
        sum += coin;
    }

    if (change == sum) {
        return results::OK;
    }
    else if (change > sum) {
        return results::MISS;
    }
    else {
        return results::OVER;
    }
}

// backtrack
int give_change_i(vector<int> &coins, int change, int min)
{
    auto res = valid_solution(coins, change);
    if (res == results::OK) {
        return (coins.size() < min) ? coins.size() : min;
    }
    else if (res == results::MISS) {
        for (auto coin : existing_coins) {
            coins.push_back(coin);
            min = give_change_i(coins, change, min);
            coins.pop_back();
        }
    }

    return min;
}

// backtrack with memoization
unordered_set<int> mem;

int give_change_ii(vector<int> &coins, int change, int min)
{
    auto res = valid_solution(coins, change);
    if (res == results::OK) {
        auto m = (coins.size() < min) ? coins.size() : min;
        mem.insert(m);
        return m;
    }
    else if (res == results::MISS) {
        for (auto coin : existing_coins) {
            if (mem.find(coins.size() + 1) != mem.end()) {
                continue;
            }

            coins.push_back(coin);
            min = give_change_ii(coins, change, min);
            coins.pop_back();
        }
    }

    return min;
}

// DP
int give_change_iii(int change)
{
    int inf = 9999999;
    vector<vector<int>> total(existing_coins.size(), vector<int>(change + 1, inf));

    for (int i = 0; i < existing_coins.size(); i++) {
        for (int j = 0; j <= change; j++) {

            if (j == existing_coins[i]) {
                total[i][j] = 1;
            }
            else if (j > existing_coins[i]) {
                int cs = total[i][j - existing_coins[i]] + 1;
                if (i > 0) {
                    total[i][j] = min(total[i - 1][j], cs);
                }
                else {
                    total[i][j] = cs;
                }
            }
            else {
                if (i > 0) {
                    total[i][j] = total[i - 1][j];
                }
            }
        }
    }

    /*
    for (int i = 0; i < existing_coins.size(); i++) {
        for (int j = 0; j <= change; j++) {
            if (total[i][j] == inf) {
                cout << "x ";
                continue;
            }
            cout << total[i][j] << " ";
        }
        cout << endl;
    }
    */
    int m = inf;
    for (int i = 0; i < existing_coins.size(); i++) {
        m = min(m, total[i][change]);
    }
    return m;
}

int main()
{
    vector<int> c;
    cout << give_change_ii(c, 51, 99999999) << endl;
    cout << give_change_iii(51) << endl;
    return 0;
}
