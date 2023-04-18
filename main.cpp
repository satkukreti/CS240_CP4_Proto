#include "BST.cpp"
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

int main(){
	BST first(10);
	first.insert(9);
	first.insert(16);
	first.print(first.getRoot());
	return 0;
};