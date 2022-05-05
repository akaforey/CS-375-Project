#ifndef MINHEAP_H
#define MINHEAP_H

#include "node.h"
#include <vector>


class Minheap
{
public:
    // node* peek_min();
    // bool is_empty()const{return (heap.size()==0);}
    void swap(int a, int b);
    void minHeapify(int);
    node* extractMin();
    void insert(node* &np);

    vector<node*> heap;
};


// node* Minheap::peek_min(){
//     if (heap.size()==0){
//         return nullptr;
//     }
//     return heap.at(0);
// }


void Minheap::swap(int a, int b){
    node* temp = heap.at(a);
    heap.at(a) = heap.at(b);
    heap.at(b) = temp;
}


// void Minheap::insert(node* &np){
//     int index = heap.size();
//     heap.push_back(np);
//     while (index>0 && heap.at(index/2)->freq > np->freq){
//         swap(index, index/2);
//     }
//     return;
// }

void Minheap::insert(node* &np){
    heap.push_back(np);
    int index = heap.size();
    while (index>1 && heap.at(index/2-1)->freq > heap.at(index-1)->freq){
        swap(index-1, index/2-1);
        index /= 2;
    }
}


// node* Minheap::extractMin(){
//     if (heap.size()==0){
//         return nullptr;
//     }
//     node* ret_node = heap.at(0);
//     heap.at(0) = heap.at(heap.size()-1);
//     int index = 1;
//     heap.pop_back();
//     while(index < heap.size()/2 + 1){
//         if(2*index + 1 <= heap.size()-1){
//             if (heap.at(2*index-1)->freq <= heap.at(2*index)->freq) {
//                 swap(index-1, 2*index-1);
//                 index = 2*index;
//             } else {
//                 swap(index-1, 2*index);
//                 index = 2*index + 1;
//             }
//         }
//         else if(heap.at(index-1)->freq > heap.at(2*index-1)->freq){
//             swap(index-1, 2*index-1);
//             index = 2*index;
//         }
//         else{
//             break;
//         }
//     }
//     return ret_node;
// }

void Minheap::minHeapify(int i){
    int l = 2*i + 1;
    int r = 2*i+2;
    int smallest;

    if(l < heap.size() && heap.at(l)->freq < heap.at(i)->freq){
        smallest = l;
    }
    else{
        smallest = i;
    }
    if (r < heap.size() && heap.at(r)->freq < heap.at(smallest)->freq){
        smallest = r;
    }
    if (smallest != i){
        swap(i, smallest);
        minHeapify(smallest);
    }
}


node* Minheap::extractMin(){
    if (heap.size()==0){
        return nullptr;
    }
    node* ret_node = heap.at(0);
    heap.at(0) = heap.at(heap.size()-1);
    heap.pop_back();

    minHeapify(0);
    return ret_node;
}



#endif
