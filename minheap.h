#ifndef MINHEAP_H
#define MINHEAP_H

#include "node.h"
#include <vector>


class Minheap
{
public:
    node* peek_min();
    bool is_empty()const{return (heap.size()==0);}
    void swap(int a, int b);
    node* extractMin();
    void insert(node* &np);

    vector<node*> heap;
};


node* Minheap::peek_min(){
    if (heap.size()==0){
        return nullptr;
    }
    return heap.at(0);
}


void Minheap::swap(int a, int b){
    node* temp = heap.at(a);
    heap.at(a) = heap.at(b);
    heap.at(b) = temp;
}


void Minheap::insert(node* &np){
    int index = heap.size();
    heap.push_back(np);
    while (index>0 && heap.at(index/2)->freq > np->freq){
        swap(index, index/2);
    }
    return;
}


node* Minheap::extractMin(){
    if (heap.size()==0){
        return nullptr;
    }
    node* ret_node = heap.at(0);
    heap.at(0) = heap.at(heap.size()-1);
    int index = 0;
    heap.pop_back();
    while(index < heap.size()/2){
        if(heap.at(index)->freq > heap.at(index*2)->freq){
            swap(index, 2*index);
            index = 2*index;
        }
        else if(2*index + 1 > heap.size()-1){
            //No right child
            break;
        }
        else if (heap.at(index)->freq > heap.at(2*index+1)->freq){
            swap(index, 2*index + 1);
            index = 2*index + 1;
        }
        else{
            break;
        }
    }
    return ret_node;
}


#endif
