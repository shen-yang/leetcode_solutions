// Naive solution would iterate all lists to take the smallest head every time to
// add to the merged list. Actually we have a efficient data structure to retrieve
// the smallest element from a bunch of elements. That is a "min heap".
// In the implementation below, I created a wrapper for list so that we could use 
// heap provided by STL more smoothly.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    struct Proxy {
        ListNode* list;
        Proxy(){}
        Proxy(ListNode* head): list(head){}
        bool next() {
            list = list->next;
            return list != nullptr;
        }
        bool operator < (const Proxy& rhs) const {
            return list->val > rhs.list->val;
        }
    };
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<Proxy> heads;
        for (auto l: lists) {
            if (l != nullptr) {
                heads.push_back(Proxy(l));
            }
        }
        make_heap(heads.begin(), heads.end());
        ListNode dummy(0);
        ListNode* merged_list = &dummy;
        while (!heads.empty()) {
            pop_heap(heads.begin(), heads.end());
            Proxy& smallest = heads.back();
            merged_list->next = smallest.list;
            merged_list = merged_list->next;
            if (smallest.next()) {
                push_heap(heads.begin(), heads.end());
            } else {
                heads.pop_back();
            }
        }
        return dummy.next;
    }
};