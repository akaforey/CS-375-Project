#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"

class DataNode {
    public:
    DataNode *next = nullptr; 
    DataNode *prev = nullptr;
    node* n;
    DataNode(node* n){
        this->n = n;
    }
    // char data;
    // unsigned long freq;
};


class Queue {
    public:
        Queue(unsigned int, DataNode*);
        Queue();
        // void enqueue(DataNode*);
        void enqueue(node*);
        node* dequeue();
        // DataNode* dequeue();
        DataNode *head = nullptr;
        DataNode *tail = nullptr;
};

Queue::Queue(){
    this->head = nullptr;
}

// Queue::Queue(unsigned int char_count, DataNode *array) {
//     this->head = 0;
//     this->tail = 0;
// }

void Queue::enqueue(node* n){
    DataNode* temp = new DataNode(n);
    if (this->head == nullptr){
        this->head = temp;
        this->tail = temp;
        return;
    }
    else {
        this->tail->next = temp;
        temp->prev = this->tail;
        temp->next = nullptr;
        this->tail = temp;
    }
    return;

}

// void Queue::enqueue(DataNode* n) {
//     if (this->head == 0) {
//         this->head = n;
//         n->prev = 0;
//     } else {
//         n->prev = this->tail;
//         n->prev->next = n;
//     }
//     this->tail = n;
//     n->next = 0;
// }

node* Queue::dequeue() {
    node* ret_val;
    if (this->head == nullptr){
        return nullptr;
    } else {
        ret_val = this->head->n;
        this->head = this->head->next;
        if (this->head){
            this->head->prev = nullptr;
        } else {
            this->tail = nullptr;
        }
    }
    return ret_val;
}

// DataNode* Queue::dequeue() {
//     if (this->tail == 0) {
//         return 0;
//     } else {
//         DataNode *ret_node = this->tail;
//         this->tail = this->tail->prev;
//         if (this->tail != 0) {
//             this->tail->next = 0;
//         }
//     }
// }

#endif
