#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include "minheap.h"
#include "queue.h"
#include <chrono>

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

    pair<char, unsigned long> map_to_array[text.size()];
    int j=0;
    for (const auto &i : text) {
        map_to_array[j] = i;
        j++;
    }

    node* nodes[text.size()];
    for (int i=0; i < text.size(); i++){
        nodes[i] = new node(map_to_array[i].first, map_to_array[i].second, 1);
        int temp_index = i;
        while (temp_index >= 1){
            //swap down
            if (nodes[temp_index-1]->freq > nodes[temp_index]->freq) {
                node* temp_node = nodes[temp_index-1];
                nodes[temp_index-1] = nodes[temp_index];
                nodes[temp_index] = temp_node;
                temp_index--;
            }
            else {
                break;
            }
        }
    }




    auto begin = std::chrono::high_resolution_clock::now();
    Minheap heap;

    // for (int i=0; i < text.size(); i++){
    //     heap.insert(nodes[i]);
    // }

    for (const auto &i : text) {
        node* temp = new node(i.first, i.second, 1);
        heap.insert(temp);
    }
    auto end1 = std::chrono::high_resolution_clock::now();
    for (int i=0; i<text.size()-1; i++) {
        node* x = heap.extractMin();
        node* y = heap.extractMin();
        node* z = new node((x->freq)+(y->freq), 0); // Internal node
        z->left = x;
        z->right = y;
        heap.insert(z);
    }
    node* huffman_tree = heap.extractMin();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_min_heap = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    auto time_min_heap_1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - begin);
cout << "Printing tree:" << endl;
    unsigned int total_weight = 0;
    huffman_tree->printBT("", 0, "", &total_weight);
    huffman_tree->show_codes("", 0, "");
    // cout << total_weight << endl;
    cout << "Original num bits: " << num_letters*8 << endl;
    cout << "New num bits: " << total_weight << endl;
    cout << "Compression: " << (float)total_weight/(num_letters*8);

    

cout << "heap tree completed" << endl;


    //Queue code
 

    begin = std::chrono::high_resolution_clock::now();
    
    Queue queue1; // leaves
    Queue queue2; // trees
    

    for (int i=0; i < text.size(); i++){
        queue1.enqueue(nodes[i]);
    }


    for (int loops = 0; loops < text.size()-1; loops++){
        node* x;
        node* y;
        // find x
        if (queue1.head && queue2.head){
            if (queue1.head->n->freq <= queue2.head->n->freq) {
                x = queue1.dequeue();
            }
            else {
                x = queue2.dequeue();
            }
        } else if (queue1.head) {
            x = queue1.dequeue();
        } else if (queue2.head) {
            x = queue2.dequeue();
        }
        // find y
        if (queue1.head && queue2.head){
            if (queue1.head->n->freq <= queue2.head->n->freq) {
                y = queue1.dequeue();
            }
            else {
                y = queue2.dequeue();
            }
        } else if (queue1.head) {
            y = queue1.dequeue();
        } else if (queue2.head) {
            y = queue2.dequeue();
        }
        // make z
        node* z = new node((x->freq)+(y->freq), 0); // Internal node
        z->left = x;
        z->right = y;
        queue2.enqueue(z);
    }

    if (queue1.dequeue()){
        cout << "Something's wrong, queue1 not empty" << endl;
    }

    node* huffman_tree_2 = queue2.dequeue();
    end = std::chrono::high_resolution_clock::now();
    auto time_queues = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
cout << "Printing tree 2:" << endl;
    total_weight = 0;
    huffman_tree_2->printBT("", 0, "", &total_weight);
    huffman_tree_2->show_codes("", 0, "");
    // cout << total_weight << endl;
    cout << "Original num bits: " << num_letters*8 << endl;
    cout << "New num bits: " << total_weight << endl;
    cout << "Compression: " << (float)total_weight/(num_letters*8);
cout << "queue tree completed" << endl;



    in_file.close();
    cout << endl;
    cout << "min_heap time 1: " << time_min_heap_1.count() << endl;
    cout << "min_heap time: " << time_min_heap.count() << endl;
    cout << "queues time: " << time_queues.count() << endl;
    return 0;
}
