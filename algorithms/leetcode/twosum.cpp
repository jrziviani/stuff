#include <vector>
#include <unordered_map>

// Solution: O(n) x O(n)

using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        vector<int> result(2, 0);
        unordered_map<int, size_t> missing;

        for (size_t i = 0; i < nums.size(); i++) {
            if (missing.find(target - nums[i]) != missing.end()) {
                result[0] = missing[target - nums[i]];
                result[1] = i;
                return result;
            }

            missing[nums[i]] = i;
        }

        return result;
    }
};


