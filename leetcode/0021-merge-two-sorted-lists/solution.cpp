/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy;
        ListNode* newHead = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                newHead->next = list1;
                list1 = list1->next;
            } else {
                newHead->next = list2;
                list2 = list2->next;
            }
            newHead = newHead->next;
        }

        if (list1) {
            newHead->next = list1;
        } else {
            newHead->next = list2;
        }

        return dummy.next;
    }
};
