#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;

  TreeNode(int val) : val(val), left(nullptr), right(nullptr) {}
};

class ComparisonCounter {
public:
  ComparisonCounter() : count(0) {}

  void reset() { count = 0; }

  int getCount() { return count; }

  void increment() { count++; }

private:
  int count;
};

class BinarySearchTree {
public:
  BinarySearchTree() : root(nullptr) {}

  void insert(int val) { root = insertHelper(root, val); }

  bool find(int val) { return findHelper(root, val); }

  void remove(int val) { root = removeHelper(root, val); }

  TreeNode *getRoot() const { return root; }

  int getCount() { return counts.getCount(); }

  void resetCount() { counts.reset(); }

  void print(TreeNode *node) {
    if (node == nullptr)
      return;

    print(node->left);
    cout << node->val << " ";
    print(node->right);
  }

private:
  TreeNode *root;
  ComparisonCounter counts;

  TreeNode *insertHelper(TreeNode *node, int val) {
    if (node == nullptr) {
      return new TreeNode(val);
    }

    if (val < node->val) {
      counts.increment();
      node->left = insertHelper(node->left, val);
    } else if (val > node->val) {
      counts.increment();
      node->right = insertHelper(node->right, val);
    }

    return node;
  }

  bool findHelper(TreeNode *node, int val) {
    if (node == nullptr) {
      return false;
    }

    if (val == node->val) {
      counts.increment();
      return true;
    } else if (val < node->val) {
      counts.increment();
      return findHelper(node->left, val);
    } else {
      counts.increment();
      return findHelper(node->right, val);
    }
  }

  TreeNode *removeHelper(TreeNode *node, int val) {
    if (node == nullptr) {
      return nullptr;
    }

    if (val < node->val) {
      counts.increment();
      node->left = removeHelper(node->left, val);
    } else if (val > node->val) {
      counts.increment();
      node->right = removeHelper(node->right, val);
    } else {
      if (node->left == nullptr) {
        TreeNode *rightChild = node->right;
        delete node;
        return rightChild;
      } else if (node->right == nullptr) {
        TreeNode *leftChild = node->left;
        delete node;
        return leftChild;
      } else {
        TreeNode *successor = getSuccessor(node->right);
        node->val = successor->val;
        node->right = removeHelper(node->right, successor->val);
      }
    }

    return node;
  }

  TreeNode *getSuccessor(TreeNode *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }
};

void insertAll(BinarySearchTree &bst, const vector<int> &vals) {
  for (int val : vals) {
    bst.insert(val);
  }
}

void removeAll(BinarySearchTree &bst, const vector<int> &vals) {
  for (int val : vals) {
    bst.remove(val);
  }
}

void shuffle(vector<int> &vals, int S) {
  srand(time(0));
  for (int i = 0; i < S; i++) {
    int j = rand() % vals.size();
    int k = rand() % vals.size();
    swap(vals[j], vals[k]);
  }
}

void shake(vector<int> &vals, int S, int R) {
  srand(time(0));
  for (int i = 0; i < S; i++) {
    int j = rand() % vals.size();
    int k = rand() % R + 1;
    if (rand() % 2 == 0) {
      int temp = vals[j];
      for (int l = j; l < j + k && l < vals.size() - 1; l++) {
        vals[l] = vals[l + 1];
      }
      vals[j + k - 1] = temp;
    } else {
      int temp = vals[j];
      for (int l = j; l > j - k && l > 0; l--) {
        vals[l] = vals[l - 1];
      }
      vals[j - k + 1] = temp;
    }
  }
}

int sumDepths(TreeNode *root, int depth) {
  if (!root) {
    return 0;
  }
  return depth + sumDepths(root->left, depth + 1) +
         sumDepths(root->right, depth + 1);
}
int countNodes(TreeNode *root) {
  if (!root) {
    return 0;
  }
  return 1 + countNodes(root->left) + countNodes(root->right);
}
double averageDepth(TreeNode *root, int depth) {
  int numNodes = 0;
  if (!root) {
    return 0.0;
  }
  numNodes = countNodes(root);
  int sumDepthsValue = sumDepths(root, 0);
  return (double)sumDepthsValue / numNodes;
}

int height(TreeNode *node) {
  if (node == nullptr) {
    return -1;
  }

  int leftHeight = height(node->left);
  int rightHeight = height(node->right);

  return max(leftHeight, rightHeight) + 1;
}

void populate(int low, int high, const vector<int> &values, vector<int> &bst){
  if(low == high){
    return;
  }
  
  int middle = (low+high)/2;
  bst.push_back(values.at(middle));

  int temp = high;
  high = middle;
  populate(low, high, values, bst);
  
  low = middle + 1;
  high = temp;
  populate(low, high, values, bst);
}

int main() {
  BinarySearchTree perfectBST;
  BinarySearchTree linkedBST;
  BinarySearchTree randomBST;
  int size = 1000;

/*int k = 1;
while (k <= 1027) {
  for (int i = 0; i < k; i++) {
    perfectVect.push_back(k);
  }
  k *= 2;
}*/
  /*int j = 500;
  int k = 1;
  int l = 0;
  
  perfectVect.push_back(j);
  while (k <= 1000) {
    j /= 2;
    for (int i = 0; i < k; i++) {
      perfectVect.push_back(j+l);
      perfectVect.push_back(j*3+l);
      for(int m = 0; m < 2; m++){
        l = j*2;
      }
    }
    k *= 2;
    l = 0;
  }*/

  vector<int> linkedVect;
  for (int i = 0; i < size; i++) {
    linkedVect.push_back(i);
  }  

  vector<int> perfectVect;
  populate(0, 999, linkedVect, perfectVect);

  vector<int> temp = linkedVect;
  vector<int> randVect;
  
  shuffle(temp,1000);
  randVect = temp;

  vector<int> removes;
  for (int i = 0; i < size / 2; i++) {
    int b = rand() % 999 + 1;
    removes.push_back(b);
  }  


  //-----------------TESTS---------------
  // Rand
  cout << "----------------------RANDOM BST----------------------" << endl;
  insertAll(randomBST, randVect);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(randomBST.getRoot(), 0) << endl;
  cout << "Height: " << height(randomBST.getRoot()) << endl;
  randomBST.resetCount();
  randomBST.find(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  randomBST.insert(181);
  randomBST.find(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  removeAll(randomBST, removes);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  removeAll(randomBST, randVect);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  cout << "SHUFFLE" << endl;
  insertAll(randomBST, randVect);
  shuffle(randVect, 10);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(randomBST.getRoot(), 0) << endl;
  cout << "Height: " << height(randomBST.getRoot()) << endl;
  randomBST.resetCount();
  randomBST.find(181);
  randomBST.remove(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  randomBST.insert(181);
  randomBST.find(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  removeAll(randomBST, removes);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  removeAll(randomBST, randVect);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  cout << "SHAKE" << endl;
  insertAll(randomBST, randVect);
  shake(randVect,3,4);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(randomBST.getRoot(), 0) << endl;
  cout << "Height: " << height(randomBST.getRoot()) << endl;
  randomBST.resetCount();
  randomBST.find(181);
  randomBST.remove(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  randomBST.insert(181);
  randomBST.find(181);
  cout << "Comparison count: " << randomBST.getCount() << endl;
  randomBST.resetCount();
  removeAll(randomBST, removes);
  randomBST.remove(181);
  randomBST.print(randomBST.getRoot());
  cout << endl;
  removeAll(randomBST, randVect);
  randomBST.print(randomBST.getRoot());
  cout << endl;
    cout << "------------------------------------------------------------------" << endl;

  
  // Perf
  cout << "----------------------COMPLETE BST----------------------" << endl;
  insertAll(perfectBST, perfectVect);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(perfectBST.getRoot(), 0) << endl;
  cout << "Height: " << height(perfectBST.getRoot()) << endl;
  perfectBST.resetCount();
  perfectBST.find(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  perfectBST.insert(181);
  perfectBST.find(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  removeAll(perfectBST, removes);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  removeAll(perfectBST, perfectVect);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  cout << "SHUFFLE" << endl;
  insertAll(perfectBST, perfectVect);
  shuffle(perfectVect, 10);
  perfectBST.print(perfectBST.getRoot());
  cout << "Average depth: " << averageDepth(perfectBST.getRoot(), 0) << endl;
  cout << "Height: " << height(perfectBST.getRoot()) << endl;
  perfectBST.resetCount();
  perfectBST.find(181);
  perfectBST.remove(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  perfectBST.insert(181);
  perfectBST.find(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  removeAll(perfectBST, removes);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  removeAll(perfectBST, perfectVect);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  cout << "SHAKE" << endl;
  insertAll(perfectBST, perfectVect);
  shake(perfectVect,3,4);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(perfectBST.getRoot(), 0) << endl;
  cout << "Height: " << height(perfectBST.getRoot()) << endl;
  perfectBST.resetCount();
  perfectBST.find(181);
  perfectBST.remove(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  perfectBST.insert(181);
  perfectBST.find(181);
  cout << "Comparison count: " << perfectBST.getCount() << endl;
  perfectBST.resetCount();
  removeAll(perfectBST, removes);
  perfectBST.remove(181);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
  removeAll(perfectBST, perfectVect);
  perfectBST.print(perfectBST.getRoot());
  cout << endl;
    cout << "------------------------------------------------------------------" << endl;

  // Link
  cout << "----------------------Linked-List BST----------------------" << endl;
  insertAll(linkedBST, linkedVect);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(linkedBST.getRoot(), 0) << endl;
  cout << "Height: " << height(linkedBST.getRoot()) << endl;
  linkedBST.resetCount();
  linkedBST.find(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  linkedBST.insert(181);
  linkedBST.find(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  removeAll(linkedBST, removes);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  removeAll(linkedBST, linkedVect);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "SHUFFLE" << endl;
  insertAll(linkedBST, linkedVect);
  shuffle(linkedVect, 10);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(linkedBST.getRoot(), 0) << endl;
  cout << "Height: " << height(linkedBST.getRoot()) << endl;
  linkedBST.resetCount();
  linkedBST.find(181);
  linkedBST.remove(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  linkedBST.insert(181);
  linkedBST.find(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  removeAll(linkedBST, removes);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  removeAll(linkedBST, linkedVect);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "SHAKE" << endl;
  insertAll(linkedBST, linkedVect);
  shake(linkedVect,3,4);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "Average depth: " << averageDepth(linkedBST.getRoot(), 0) << endl;
  cout << "Height: " << height(linkedBST.getRoot()) << endl;
  linkedBST.resetCount();
  linkedBST.find(181);
  linkedBST.remove(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  linkedBST.insert(181);
  linkedBST.find(181);
  cout << "Comparison count: " << linkedBST.getCount() << endl;
  linkedBST.resetCount();
  removeAll(linkedBST, removes);
  linkedBST.remove(181);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  removeAll(linkedBST, linkedVect);
  linkedBST.print(linkedBST.getRoot());
  cout << endl;
  cout << "------------------------------------------------------------------" << endl;

  return 0;
}