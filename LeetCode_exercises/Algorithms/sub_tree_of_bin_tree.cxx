
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

 bool sameTree(TreeNode* root, TreeNode* subRoot) {
     if (!root && !subRoot) {
         return true;
     }
 
     if (root && subRoot && root->val == subRoot->val) {
         return sameTree(root->left, subRoot->left) &&
                 sameTree(root->right, subRoot->right); 
     }
 
     return false;
 }

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!subRoot) return true;

    if (!root) return false;

    if (sameTree(root, subRoot)) return true;

    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}

#pragma region
string serialize(TreeNode* root) {
    if (!root) return "$#";

    return "$" + to_string(root->val) + serialize(root->left) + serialize(root->right);
}

vector<int> z_function(string s) {
    vector<int> z(s.size());
    int l{}, r{}, n{static_cast<int>(s.size())};

    for (int i{}; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    string serialized_root = serialize(root);
    string serialized_subRoot = serialize(subRoot);
    string combined = serialized_subRoot + "|" + serialized_root;

    vector<int> z_values = z_function(combined);
    int sub_len = serialized_subRoot.size();

    for (int i = sub_len + 1; i < combined.size(); i++) {
        if (z_values[i] == sub_len) {
            return true;
        }
    }
    return false;
}