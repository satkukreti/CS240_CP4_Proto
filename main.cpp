#include "BST.h"
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

int main(){
	BST first(10);
	first.insert(12, first.getRoot());
	return 0;
};