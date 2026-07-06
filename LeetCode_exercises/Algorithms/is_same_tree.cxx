

struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode() : val(0), left(nullptr), right(nullptr) {}
   TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
   TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool is_same_tree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;

    if ((!p && q) || (p && !q)) return false;

    // std::cout << "p->val: " << p->val << "\n";
    // std::cout << "q->val: " << q->val << "\n";

    if (p->val != q->val) return false;

    return is_same_tree(p->left, q->left) && is_same_tree(p->right, q->right);
}

bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;

    if (p && q && p->val == q->val)
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    else return false;
}