#ifndef BST_CPP
#define BST_CPP
#include <iostream>
#include <exception>
#include <tuple>
#include "node.h"

using namespace std;


class BST
{
public:
    BST():root(nullptr), pptr(&root){}
    BST(const BST& t) :root(nullptr), pptr(&root) {if(t.root != nullptr) root = new node(*(t.root));}

    node* &get_root(){return root;}
    bool is_empty()const{return (root == nullptr);}

    void find_node(char& d, node* &np, node* &match);
    void insert(char& d);
    void delete_tree() {delete_tree(root);}

    void remove_node(node* &cp);

    tuple<char&, bool> find_val(char& d, node* np);

    tuple<char&, bool> find(char& d);
//    node** find(T d);
//  T& find(T d, node* np);

    void print_level(ostream& out)const {print_level(root, out);}
    void print_level(node* cp, ostream& out)const;
    void print(node* cp, ostream& out, int lp)const;

    char remove_last(node* &cp);
    void remove(char& d, node* np);
    int get_height()const
    {if(is_empty()) return 0; return root->get_height();}
    void set_height() const {if(root != nullptr) root->set_height();}

    ~BST(){delete_tree(root);}
    void insert(char& d, node* &cp);
    node* root;
    node** pptr;
private:
    void delete_tree(node* &cp);
};


void BST::find_node(char& d, node* &np, node* &match){
    if (match != nullptr)
        return;
    if (np != nullptr){
        find_node(d, np->left, match);
        if (d == np->value()){
            match = np;
            pptr = &np;
            return;
        }
        find_node(d, np->right, match);
    }
}


tuple<char&, bool> BST::find_val(char& d, node* np){

    bool found = false;
    node* mptr = nullptr;

    find_node(d, root, mptr);

    if (*pptr != nullptr){
        if ((*pptr)->value() == d)
            found = true;
        return {(*pptr)->value(), found};
    }else{
        return {d, found};
    }
}


tuple<char&, bool> BST::find(char& d){
    return find_val(d, root);
}


void BST::insert(char& d){
    insert(d, root);
}

void BST::insert(char& d, node* &cp)
{
    if (cp == nullptr){
        cp = new node(d);
        if (is_empty()) root = cp;
    }else{
        if (d < cp->value())
            insert(d, cp->left);
        else
            insert(d, cp->right);
        if (root != nullptr)
            root->set_height();
    }
}


void BST::remove_node(node* &cp)
{
    if (cp->left == nullptr && cp->right == nullptr){
        delete cp;
        cp = nullptr;
    }
    else if (cp->left == nullptr){
        node* temp = cp->right;
        delete cp;
        cp = temp;
    }
    else if (cp->right == nullptr){
        node* temp = cp->left;
        delete cp;
        cp = temp;
    }else{
        cp->set_data(remove_last(cp->right));
    }
    if (root != nullptr) root->set_height();
}


char BST::remove_last(node* &cp)
{
//     if (cp == nullptr){};
    if (cp->left == nullptr)
    {
        char temp = cp->value();
        node* tmptr = cp->right;
        delete cp;
        cp = tmptr;
        if (root != nullptr)
            root->set_height();
        return temp;
    }
    return remove_last(cp->left);
}


void BST::remove(char& d, node* np)
{
    node* mptr = nullptr;
    find_node(d, root, mptr);
    if (*pptr != nullptr){
        if ((*pptr)->value() == d) remove_node((*pptr));
    }
    if (root != nullptr)
        root->set_height();
}


void BST::print(node* cp, ostream& out, int lp)const{
    static int cl = 0;
    if (lp < 1)
        return;
    if (cp != nullptr){
        cl++;
        if (cl <= lp) print(cp->left, out, lp);
        if (cl == lp) out << cp->value() << "[" << cp->get_height() << "] ";
        if (cl <= lp) print(cp->right, out, lp);
        cl--;
    }
}


void BST::print_level(node* cp, ostream& out)const
{
    if (cp == nullptr)
        return;
    for(int i = 1; i <= cp->get_height(); i++){
        out << "level " << i << ": ";
        print(cp, out, i);
        out << endl;
    }
}


void BST::delete_tree(node* &cp)
{
    if (cp != nullptr){
        delete_tree(cp->left);
        delete_tree(cp->right);
        delete cp;
        cp = nullptr;
        if (root != nullptr)
            root->set_height();
    }
}


ostream& operator<<(ostream& out, BST tree){
    tree.print_level(tree.get_root(), out);
    return out;
}
#endif
