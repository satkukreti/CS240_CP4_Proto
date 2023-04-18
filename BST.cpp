#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        root = insertHelper(root, val);
    }

    bool find(int val) {
        return findHelper(root, val);
    }

    void remove(int val) {
        root = removeHelper(root, val);
    }
    
        TreeNode* getRoot() const {
    return root;
    }

private:
    TreeNode* root;

    TreeNode* insertHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }

        return node;
    }

    bool findHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return false;
        }

        if (val == node->val) {
            return true;
        } else if (val < node->val) {
            return findHelper(node->left, val);
        } else {
            return findHelper(node->right, val);
        }
    }

    TreeNode* removeHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return nullptr;
        }

        if (val < node->val) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = removeHelper(node->right, val);
        } else {
            if (node->left == nullptr) {
                TreeNode* rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                TreeNode* leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                TreeNode* successor = getSuccessor(node->right);
                node->val = successor->val;
                node->right = removeHelper(node->right, successor->val);
            }
        }

        return node;
    }

    TreeNode* getSuccessor(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
};

void insertAll(BinarySearchTree& bst, const vector<int>& vals) {
    for (int val : vals) {
        bst.insert(val);
    }
}

void removeAll(BinarySearchTree& bst, const vector<int>& vals) {
    for (int val : vals) {
        bst.remove(val);
    }
}

void shuffle(vector<int>& vals, int S) {
    srand(time(0));
    for (int i = 0; i < S; i++) {
        int j = rand() % vals.size();
        int k = rand() % vals.size();
        swap(vals[j], vals[k]);
    }
}

void shake(vector<int>& vals, int S, int R) {
    srand(time(0));
    for (int i = 0; i < S; i++) {
        int j = rand() % vals.size();
        int k = rand() % R + 1;
        if (rand() % 2 == 0) {
            // Move element j to the right
            int temp = vals[j];
            for (int l = j; l < j + k && l < vals.size()-1; l++) {
                vals[l] = vals[l+1];
            }
            vals[j + k - 1] = temp;
        } else {
            // Move element j to the left
            int temp = vals[j];
            for (int l = j; l > j - k && l > 0; l--) {
                vals[l] = vals[l-1];
            }
            vals[j - k + 1] = temp;
        }
    }
}

double averageDepth(TreeNode* node, int depth) {
    if (node == nullptr) {
        return 0;
    }

    double leftDepth = averageDepth(node->left, depth+1);
    double rightDepth = averageDepth(node->right, depth+1);

    return (leftDepth + rightDepth + depth) / 2;
}

int height(TreeNode* node) {
    if (node == nullptr) {
        return -1;
    }

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return max(leftHeight, rightHeight) + 1;
}

class ComparisonCounter {
public:
    ComparisonCounter() : count(0) {}

    void reset() {
        count = 0;
    }

    int getCount() {
        return count;
    }

    void increment() {
        count++;
    }

private:
    int count;
};

class BinarySearchTreeWithCount : public BinarySearchTree {
public:
    BinarySearchTreeWithCount() : BinarySearchTree(), counter() {}

    void insert(int val) {
        BinarySearchTree::insert(val);
        counter.increment();
    }

    bool find(int val) {
        counter.increment();
        return BinarySearchTree::find(val);
    }

    void remove(int val) {
        BinarySearchTree::remove(val);
        counter.increment();
    }

    void resetCount() {
        counter.reset();
    }

    int getCount() {
        return counter.getCount();
    }

private:
    ComparisonCounter counter;
};

int main() {
    BinarySearchTreeWithCount bst;
    vector<int> vals = {5, 3, 7, 1, 4, 6, 8};
    vector<int> removes = {3, 8, 9, 6, 7};
    insertAll(bst, vals);
    cout << "Average depth: " << averageDepth(bst.getRoot(), 0) << endl;
    cout << "Height: " << height(bst.getRoot()) << endl;
    bst.resetCount();
    bst.find(2);
    bst.resetCount();
    bst.insert(9);
    bst.remove(1);
    removeAll(bst, removes);
    cout << "Comparison count: " << bst.getCount() << endl;

    shuffle(vals, 10);
    removeAll(bst, vals);
    return 0;
}