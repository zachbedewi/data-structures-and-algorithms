/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) {
            return nullptr;
        }

        // First round: Make copies and insert after original
        Node* iter = head;
        while (iter) {
            Node* copy = new Node(iter->val);
            copy->next = iter->next;
            iter->next = copy;
            iter = copy->next;
        }

        // Second round: Assign random pointers for the copies
        iter = head;
        while (iter) {
            if (iter->random) {
                iter->next->random = iter->random->next;
            }
            iter = iter->next->next;
        }

        // Third round: restore and remove copies
        iter = head;
        Node* newHead = head->next;
        while (iter) {
            Node* copy = iter->next;
            iter->next = copy->next;
            if (copy->next) {
                copy->next = copy->next->next;
            }
            iter = iter->next;
        }

        return newHead;
    }
};
