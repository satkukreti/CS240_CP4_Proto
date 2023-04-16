#include "BST.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

BST::BST(unsigned int rootData){
	count = -1;	
	root.data = rootData;
};

Node* BST::getRoot(){
	return &(this->root);
};

bool BST::insert(int n){
	if(n < 0){
		return false;	
	}
		
	insertRecursively(n, &root);
	return true;
};

void BST::insertRecursively(int n, Node* N){
	if (N == nullptr) {
        Node *newNode = new Node();
        newNode->data = n;
        N = newNode;
    } else if (n > N->data) {
        if (N->right == nullptr) {
            Node *newNode = new Node();
            newNode->data = n;
            N->right = newNode;
        } else {
            insertRecursively(n, N->right);
        }
    } else if (n <= N->data) {
        if (N->left == nullptr) {
            Node *newNode = new Node();
            newNode->data = n;
            N->left = newNode;
        } else {
            insertRecursively(n, N->left);
        }
    }
};

void BST::print(Node *node){
	if (node == nullptr)
        return;
 
    print(node->left);
    cout << node->data << " ";
    print(node->right);
};

