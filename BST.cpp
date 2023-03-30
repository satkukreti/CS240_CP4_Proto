#include "BST.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

BST::BST(unsigned int rootData){
	root.data = rootData;
	root.right = nullptr;
	root.left = nullptr;
}

Node& BST::getRoot(){
	return (this->root);
}

bool BST::insert(int n, Node &N){
	if(n < 0){
		return false;	
	}	
	
	if(N.data == -1){
		N.data = n;
		return true;
	}
	
	Node *temp = new Node();
	temp = &N;
	//cout<<temp.data;
	if(n > N.data){
		temp = N.right;
		insert(n, *(temp));
	} else if(n < N.data){
		temp = N.left;
		insert(n, *(temp));
	} else {
		return false;
	}
	
	return false;
}

