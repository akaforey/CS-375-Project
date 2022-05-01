FLAGS = -Wall -Wextra -g
EXECUTABLE = huffman

all: huffman

huffman:	main.o	#BST.o
	g++  main.o -o	huffman

main.o: main.cpp
	g++ -c main.cpp

BST.o:	node.h	BST.cpp
	g++ -c BST.cpp

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f *.o $(EXECUTABLE)
