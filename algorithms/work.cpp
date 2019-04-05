#include <iostream>
#include <vector>
#include <string>

#include <queue>

using namespace std;

enum class VALID : int
{
    valid,
    invalid,
    dontknow,
};

VALID is_valid_schedule(const string &pattern, int expected)
{
    int result = 0;
    bool has_slot = false;
    for (auto c : pattern) {
        if (c == '?') {
            has_slot = true;
            continue;
        }
        result += c - '0';
    }

    if (result > expected || (result < expected && !has_slot)) {
        return VALID::invalid;
    }
    else if (result == expected && !has_slot) {
        return VALID::valid;
    }

    return VALID::dontknow;
}

size_t get_next_day(const string &pattern, size_t current_day)
{
    for (size_t i = current_day; i < pattern.size(); i++) {
        if (pattern[i] == '?') {
            return i;
        }
    }

    return pattern.size();
}

void generate(string &pattern, int current, int dayhour, int workhour)
{
    current = get_next_day(pattern, current);
    if (current == pattern.size()) {
        return;
    }

    for (int i = 0; i <= dayhour ; i++) {
        pattern[current] = i + '0';

        switch (is_valid_schedule(pattern, workhour)) {
            case VALID::dontknow:
                generate(pattern, current + 1, dayhour, workhour);
                break;

            case VALID::valid:
                cout << pattern << endl;
                break;

            default:
                break;
        }
        pattern[current] = '?';
    }
}



vector<string> findSchedules(int workHours, int dayHours, string pattern)
{
    vector<string> res;

    // count how many slots are avaible and the number
    // of hours worked
    int existing_hours = 0;
    int slots = 0;
    for (char c : pattern) {
        if (c == '?') {
            slots++;
        }
        else {
            existing_hours += c - '0';
        }
    }
    cout << "slots: " << slots << ", existing_hours: " << existing_hours << endl;

    // there is no empty slot to be filled, return the pattern
    // because it must be the correct schedule as per requirements
    if (slots == 0) {
        res.emplace_back(pattern);
        return res;
    }

    auto ptrn = pattern;
    generate(ptrn, 0, dayHours, workHours);

    return res;
}

int main()
{
    auto result = findSchedules(3, 1, "???????");
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }
    cout << "\n";

    return 0;
}
