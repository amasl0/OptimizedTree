//
// Created by Andrew Maslov on 30.04.2020.
//
#pragma once
#include <vector>

class tree {
private:
    class node{
    public:
        int value;
        node* right;
        node* left;
        node* parent;
        node(int value){
            this->value = value;
            this->right = nullptr;
            this->left = nullptr;
            this->parent = nullptr;
        }
        node(int value, node* parent){
            this->value = value;
            this->right = nullptr;
            this->left = nullptr;
            this->parent = parent;
        }
    };
    node* head = nullptr;
    int size = 0;
public:
    long long N_op = 0;

    void insert(int value);

    void erase(int value);

    void print_direct();

    void print_simmetric();

    void print_reverse();

    void balanced();

    std::vector<int> transfer_vec_direct();

    std::vector<int> transfer_vec_sim();

    std::vector<int> transfer_vec_reverse();
private:
    node* find_node(int value);

    void optimize(tree &temp, int start, int end, std::vector<int> data);

    void simmetric_bypass(node* current, std::vector<int> &data);

    void reverse_bypass(node* current, std::vector<int> &data);

    void direct_bypass(node* current, std::vector<int> &data);

    node* getFreeNode(int value, node *parent);

};

tree operator ^ (tree A, tree B);
