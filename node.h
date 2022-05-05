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
    explicit node(char& d) :data(d), height(1), freq(1), left(nullptr), right(nullptr){}
    // node(const node& n):data(n.value()), height(n.get_height()), freq(n.freq), left(nullptr), right(nullptr){
    //     if (n.left != nullptr) left = new node(*(n.left));
    //     if (n.right != nullptr) right = new node(*(n.right));
    // }
    
    node(unsigned long long frequency, bool is_leaf){
        this->freq = frequency;
        this->leaf = is_leaf;
    }
    node(char data, unsigned long frequency, bool is_leaf){
        this->data = data;
        this->freq = (unsigned long long) frequency;
        this->leaf = is_leaf;
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

    // void print(int level){
    //     if (this->left){
    //         (this->left)->print(level+1);
    //     }
    //     if (this->data){
    //         cout << "Char (ascii): " << (unsigned int)this->data << ", char: " << this->data << ", frequency: " << this->freq << ", level: " << level << endl;
    //     }
    //     if (this->right){
    //         (this->right)->print(level+1);
    //     }
    // }

    void printBT(const std::string& prefix, bool isLeft, string path, unsigned int* total_weight_p){
        // if( this != nullptr ){
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            // std::cout << node->m_val << std::endl;
            if (this->leaf){
                // cout << "Char (ascii): " << (unsigned int)this->data << ", char: " << this->data << ", frequency: " << this->freq << endl;
                cout << "Char (ascii): " << (unsigned int)this->data << ", char: " << this->data << ", frequency: " << this->freq << endl;
                *total_weight_p += path.length() * this->freq;
            }
            else {
                cout << "Internal, frequency: " << this->freq << endl;
            }

            // enter the next tree level - left and right branch
            if (this->left){
                this->left->printBT( prefix + (isLeft ? "│   " : "    "), true, path + '0', total_weight_p);
            }
            if (this->right){
                this->right->printBT( prefix + (isLeft ? "│   " : "    "), false, path + '1', total_weight_p);
            }
        // }
    }

    char value() {return data;}
    explicit operator char()const {return data;}
    node* left = 0;
    node* right = 0;
    unsigned long long freq;
    bool leaf = 1;
};
#endif
