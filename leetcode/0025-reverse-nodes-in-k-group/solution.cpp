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
private:
    ListNode* getKthNode(ListNode* head, int k) {
        ListNode* curr = head;

        while (curr && k > 0) {
            curr = curr->next;
            k--;
        }

        return curr;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0, head);
        ListNode* prevGroup = &dummy;

        while (true) {
            ListNode* kthNode = getKthNode(prevGroup, k);
            if (!kthNode) {
                break;
            }

            ListNode* nextGroup = kthNode->next;

            ListNode* prev = nextGroup;
            ListNode* curr = prevGroup->next;
            while (curr != nextGroup) {
                ListNode* tmp = curr->next;
                curr->next = prev;
                prev = curr;
                curr = tmp;
            }

            ListNode* tmp = prevGroup->next;
            prevGroup->next = kthNode;
            prevGroup = tmp;
        }

        return dummy.next;
    }
};
