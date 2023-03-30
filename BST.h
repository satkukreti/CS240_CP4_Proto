#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std

struct Node{
 unsigned int data;
 Node *right = nullptr;
 Node *left = nullptr;
}

class BST{
	public:
		bool insert(Node &n);
		bool removeNode(Node &n);
		bool find(Node &n);

	private:
		unsigned int root;
		Node *rN;
		Node *lN;
};