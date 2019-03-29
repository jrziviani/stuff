#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    void swp(string &s, size_t ia, size_t ib)
    {
        char tmp = s[ia];
        s[ia] = s[ib];
        s[ib] = tmp;
    }

    /* TODO: this solution is O(n) but the swap part makes it very slow (36ms)
     * when compared to better solutions, which is also O(n) but runs 8ms.
     * I need to improve it */
    bool buddyStrings(string A, string B)
    {
        if (A.size() < 2 || A.size() != B.size()) {
            return false;
        }

        for (size_t i = 0, j = A.size() - 1; i < j;) {
            swp(A, i, j);
            if (A == B) {
                return true;
            }

            bool go_right = false;
            if (A > B) {
                go_right = true;
            }

            swp(A, i, j);

            if (go_right) {
                i++;
            }
            else {
                j--;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    cout << sol.buddyStrings("aaaabc", "aaaacb") << endl;

    return 0;
}
