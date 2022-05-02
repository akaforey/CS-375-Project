#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include "minheap.h"

using namespace std;

int main(int argc, char *argv[])
{

    map<char, unsigned long> text;
    char letter;
    unsigned long long num_letters = 0;

    //Usage: ./huffman <input file name>
    ifstream in_file(argv[1]);
    if (!in_file.is_open()) {
        exit(1);
    }

    while (in_file.get(letter)) {
        text[letter]++;
        num_letters++;
    }
    for (const auto &i : text) {
        cout << i.first << " " << i.second << endl;
    }

    //Min heap

    Minheap heap;

    for (const auto &i : text) {
        heap.insert(new node(i.first, i.second));
    }

    for (int i=0; i<text.size()-1; i++) {
        node* x = heap.extractMin();
        node* y = heap.extractMin();
        node* z = new node(x.freq+y.freq); // Internal node
        z.left = x;
        z.right = y;
        heap.insert(z);
    }
    node* huffman_tree = heap.extractMin();


    //Queue code would go here:


    in_file.close();
    return 0;
}
