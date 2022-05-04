#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include "minheap.h"
#include "queue.h"

using namespace std;

int main(int argc, char *argv[])
{

    map<char, unsigned long> text;
    char letter;
    unsigned long long num_letters = 0;

    if (argc != 2){
        cout << "Usage: ./huffman <input file name>" << endl;
    }

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
        node* temp = new node(i.first, i.second, 1);
        heap.insert(temp);
    }

    for (int i=0; i<text.size()-1; i++) {
        node* x = heap.extractMin();
        node* y = heap.extractMin();
        node* z = new node((x->freq)+(y->freq), 0); // Internal node
        z->left = x;
        z->right = y;
        heap.insert(z);
    }
    node* huffman_tree = heap.extractMin();
cout << "Printing tree:" << endl;
    huffman_tree->printBT("", 0);
    

cout << "heap tree completed" << endl;


    //Queue code
    DataNode data_nodes[text.size()];
    char sorted[text.size()];
    int k = 0;
    for (const auto &j : text) {
        unsigned long min_freq = 0;
        char min_char = 0;
        for (const auto &i : text) {
            if (min_char == 0 || i.second < min_freq) {
                min_char = i.first;
                min_freq = i.second;
            }
        }
        sorted[k] = min_char;
        k++;
    }
    Queue queue1(text.size(),data_nodes), queue2(text.size(),data_nodes);
    for (int i = 0; i < text.size(); i++) {
        data_nodes[i].data = sorted[i];
        data_nodes[i].freq = text[sorted[i]];
        queue1.enqueue(&data_nodes[i]);
    }

    while (queue1.head != 0 || queue2.head != 0) {
         DataNode *node1, *node2;
        if (queue2.head == 0) {
            node1 = queue1.dequeue();
            if (queue1.head != 0)
                node2 = queue1.dequeue();
        }
        else if (queue1.head == 0) {
            node1 = queue2.dequeue();
            if (queue2.head != 0)
            node2 = queue2.dequeue();
        }
        else {
            if (queue1.tail->freq < queue2.tail->freq) {
                node1 = queue1.dequeue();
            }
            else {
                node1 = queue2.dequeue();
            }
        }
    }

    in_file.close();
    return 0;
}
