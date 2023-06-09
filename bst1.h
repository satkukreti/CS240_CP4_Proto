//#ifndef BST_H

#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

struct Node{
 int data = -1;
 Node *right = nullptr;
 Node *left = nullptr;
};

class BST{
	public:
		BST(unsigned int rootData);
		Node* getRoot();
		bool insert(int n);
		void insertRecursively(int n, Node *N);
		
		bool removeNode(unsigned int n);
		bool find(unsigned int n);
		void print(Node *node);


	private:
		Node root;
		int count;
};