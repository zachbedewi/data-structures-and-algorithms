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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int length = 0;
        ListNode* first = head;
        while (first) {
            first = first->next;
            length += 1;
        }

        int itemToRemove = length - n;
        if (itemToRemove == 0) {
            return head->next;
        }

        int currIdx = 0;
        ListNode* second = head;
        while (currIdx < itemToRemove - 1) {
            currIdx +=1;
            second = second->next;
        }

        second->next = second->next->next;
        return head;
    }
};
