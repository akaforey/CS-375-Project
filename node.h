#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <exception>
#include <tuple>

using namespace std;

class node
{
private:
    char data;
    int height;
public:
    explicit node(char& d) :data(d), height(1), left(nullptr), right(nullptr){}
    node(const node& n):data(n.data), height(n.get_height()), left(nullptr), right(nullptr){
        if (n.left != nullptr) left = new node(*(n.left));
        if (n.right != nullptr) right = new node(*(n.right));
    }
    void set_data(const char& d) {data = d;}
    int get_height()const {return height;}
    int set_height(){
        int lh = 0;
        int rh = 0;
        height = 1;

        if (left != nullptr) lh = left->set_height();
        if (right != nullptr) rh = right->set_height();
        if (lh > rh){
            return height+= lh;
        }else{
            return height += rh;
        }
    }

    char& value() {return data;}
    explicit operator char()const {return data;}
    node* left;
    node* right;
};
#endif