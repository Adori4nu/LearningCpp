
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    // std::list<int>::iterator it1{ list1*->begin() };
    // std::list<int>::iterator it2{ list2*->begin() };
    ListNode res{};
    ListNode* tmp{ &res };

    if (!list1 && !list2) return {};

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            tmp->next = list1;
            list1 = list1->next;
        } else {
            tmp->next = list2;
            list2 = list2->next;
        }
        tmp = tmp->next;
    }
    if (list1) {
        tmp->next = list1;
    } else {
        tmp->next = list2;
    }
    return res.next;
}