struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    int set_number(ListNode **node, int value)
    {
        ListNode *newnode = new ListNode(value);
        if (newnode->val / 10 > 0) {
            newnode->val %= 10;
        }

        if (*node == nullptr) {
            *node = newnode;
        }
        else {
            (*node)->next = newnode;
            *node = (*node)->next;
        }

        return value / 10;
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        ListNode *result = nullptr;
        ListNode *head = nullptr;

        int carry = 0;
        for (; l1 != nullptr; l1 = l1->next) {
            if (l2 != nullptr) {
                carry = set_number(&result, l1->val + l2->val + carry);
                l2 = l2->next;
            }
            else {
                carry = set_number(&result, l1->val + carry);
            }

            if (head == nullptr) {
                head = result;
            }
        }

        for (; l2 != nullptr; l2 = l2->next) {
            carry = set_number(&result, l2->val + carry);
            if (head == nullptr) {
                head = result;
            }
        }

        if (carry > 0) {
            set_number(&result, carry);
        }

        return head;
    }
};
