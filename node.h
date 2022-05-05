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
public:    
    node(unsigned long long frequency, bool is_leaf){
        this->freq = frequency;
        this->leaf = is_leaf;
    }
    node(char data, unsigned long frequency, bool is_leaf){
        this->data = data;
        this->freq = (unsigned long long) frequency;
        this->leaf = is_leaf;
    }

    void printBT(const std::string& prefix, bool isLeft, string path, unsigned int* total_weight_p){
        // if( this != nullptr ){
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            // std::cout << node->m_val << std::endl;
            if (this->leaf){
                // cout << "Char (ascii): " << (unsigned int)this->data << ", char: " << this->data << ", frequency: " << this->freq << endl;
                cout << "Char (ascii): " << (unsigned int)this->data << ", char: " << this->data << ", frequency: " << this->freq << endl;
                // cout << this->data << ": " << path << endl;
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

    void show_codes(const std::string& prefix, bool isLeft, string path){

            if (this->leaf){
                cout << this->data << ": " << path << endl;
            }

            // enter the next tree level - left and right branch
            if (this->left){
                this->left->show_codes( prefix + (isLeft ? "│   " : "    "), true, path + '0');
            }
            if (this->right){
                this->right->show_codes( prefix + (isLeft ? "│   " : "    "), false, path + '1');
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
