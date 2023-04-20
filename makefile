test: CP4
	./cp4

CP4: BST.o
	g++ -Wall -Wextra -g BST.o -o cp4

BST.o: BST.cpp
	g++ -Wall -Wextra -c BST.cpp
	
clean:
	rm -f *.o cp4
