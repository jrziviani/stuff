/**
 * Definition for singly-linked list.
 * */
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr) {
            return head;
        }

        ListNode *prev = head;
        ListNode *current = head->next;
        head->next = nullptr;
        while (current != nullptr) {
            ListNode *tmp = current->next;
            current->next = prev;
            prev = current;
            current = tmp;
        }

        return prev;
    }
};
