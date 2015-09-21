// https://leetcode.com/problems/delete-node-in-a-linked-list/
// Since node given is not a tail. We could do a trick: copy the contents of
// the next node, then connect to the next of next, delete the next node.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void deleteNode(ListNode* node) {
        if (node->next != nullptr) {
            ListNode* tmp = node->next;
            node->val = tmp->val;
            node->next = tmp->next;
            delete tmp;
        } else {
            // we are assured node is not the tail.
            throw std::invalid_argument(to_string(reinterpret_cast<intptr_t>(node)) + " points to a tail.");
        }
    }
};