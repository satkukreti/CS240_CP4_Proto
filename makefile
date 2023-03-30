test: main
	./cp4

main: main.o BST.o
	g++ -Wall -Wextra -g main.o BST.o -o cp4

main.o: main.cpp
	g++ -Wall -Wextra -c main.cpp

BST.o: BST.cpp BST.h
	g++ -Wall -Wextra -c BST.cpp BST.h
	
clean:
	rm -f *.o cp4