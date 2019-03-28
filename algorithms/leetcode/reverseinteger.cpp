#include <limits>

using namespace std;

constexpr int MAX = numeric_limits<int>::max();
constexpr int MIN = numeric_limits<int>::min();

class Solution {
public:
    int reverse(int x)
    {
        long int result = 0;

        while (x != 0) {
            int digit = x % 10;

            if ((x > 0 && result > (MAX - digit) / 10) ||
                (x < 0 && result < (MIN - digit) / 10)) {
                return 0;
            }

            result = result * 10 + digit;
            x /= 10;
        }

        return result;
    }
};
