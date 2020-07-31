//
// Created by Andrew Maslov on 30.04.2020.
//
#include "optimized-tree.h"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

// tree::public
void tree::insert(int value) {
    node *tmp = nullptr; N_op+=1;
    node *ins = nullptr; N_op+=1;
    size++;
    // если дерево пустое
    if (head == nullptr) {
        head = getFreeNode(value, nullptr); N_op+=1;
        return;
    }
    tmp = head; N_op+=1;
    while (tmp) {
        // если значение больше
        if (value > tmp->value) {
            if (tmp->right) {
                tmp = tmp->right; N_op+=1;
                continue;
            } else {
                tmp->right = getFreeNode(value, tmp); N_op+=1;
                return;
            }
            //если меньше
        } else if (value < tmp->value) {
            if (tmp->left) {
                tmp = tmp->left; N_op+=1;
                continue;
            } else {
                tmp->left = getFreeNode(value, tmp); N_op+=1;
                return;
            }
        }
    }

}

void tree::erase(int value) {
    node* current = find_node(value); N_op+=1;
    if (current != nullptr) {

        // если есть правый потомок
        if (current->right != nullptr) {
            // если у правого потомка нету левого потомка
            if (current->right->left == nullptr) {
                current->value = current->right->value; N_op+=1;
                node* tmp = current->right; N_op+=1;
                current->right = current->right->right; N_op+=1;

                delete tmp;

            } else {
                // найти самого левого потомка у правого потомка
                node* most_left = current->right; N_op+=1;
                while (most_left->left != nullptr) {
                    most_left = most_left->left; N_op+=1;
                }
                current->value = most_left->value; N_op+=1;
                most_left->parent->left = most_left->right; N_op+=1;

                delete most_left;

            }
        }
        else {
            // если этот потомок у предка слева
            if (current->parent->left->value == current->value) {
                current->parent->left = current->left; N_op+=1;
            }
            else {
                current->parent->right = current->left; N_op+=1;
            }
            delete current;

        }
        size--; N_op+=2;
        balanced();
    }
}

void tree::print_direct(){
    std::vector<int> data;
    node* current = head;
    direct_bypass(current, data);
    for(auto it = data.begin(); it != data.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void tree::print_simmetric(){
    std::vector<int> data;
    node* current = head;
    simmetric_bypass(current, data);
    for(auto it = data.begin(); it != data.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void tree::print_reverse(){
    std::vector<int> data;
    node* current = head;
    reverse_bypass(current, data);
    for(auto it = data.begin(); it != data.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void tree::balanced(){
    std::vector<int> data;
    node* current = head; N_op+=1;
    simmetric_bypass(current, data);
    if(data.size() > 2) {
        tree temp;
        int start = 0, end = data.size(); N_op+=2;
        optimize(temp, start, end, data);
        *this = temp; N_op+=1;
    }
}

std::vector<int> tree::transfer_vec_direct(){
    std::vector<int> data;
    node* current = head;
    direct_bypass(current, data);
    return data;
}

std::vector<int> tree::transfer_vec_sim(){
    std::vector<int> data;
    node* current = head;
    simmetric_bypass(current, data);
    return data;
}

std::vector<int> tree::transfer_vec_reverse(){
    std::vector<int> data;
    node* current = head;
    reverse_bypass(current, data);
    return data;
}

//tree::private

tree::node* tree::find_node(int value) {
    node* current=head; N_op+=1;
    while(current != nullptr && current->value != value) {
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
        N_op+=1;
    }
    return current;
}

void tree::optimize(tree &temp, int start, int end, std::vector<int> data){
    int middle = (start + end) / 2, lock = (end - start) / 2; N_op += 3;
    temp.insert(data[middle]);
    if(start != 0) {
        if ((middle - start) != 1) {
            optimize(temp, start, middle, data);
        }
    } else {
        if((middle - start) != 0)
            optimize(temp, start, middle, data);
    }
    if((end - middle) != 1){
        optimize(temp, middle, end, data);
    }
}

void tree::simmetric_bypass(node* current, std::vector<int> &data){
    if(current->left != nullptr)
        simmetric_bypass(current->left,data);
    data.push_back(current->value); N_op+=1;
    if(current->right != nullptr)
        simmetric_bypass(current->right, data);
}

void tree::reverse_bypass(node* current, std::vector<int> &data){
    if(current->right != nullptr)
        direct_bypass(current->right, data);
    data.push_back(current->value); N_op+=1;
    if(current->left != nullptr)
        direct_bypass(current->left,data);
}

void tree::direct_bypass(node* current, std::vector<int> &data){
    data.push_back(current->value); N_op+=1;
    if(current->left != nullptr)
        direct_bypass(current->left,data);
    if(current->right != nullptr)
        direct_bypass(current->right, data);
}

tree::node* tree::getFreeNode(int value, node *parent) {
    node* tmp = new node(value, parent); N_op+=5;
    return tmp;
}

// operator

tree operator ^ (tree A, tree B){
    std::vector<int> vec_A = A.transfer_vec_sim();
    std::vector<int> vec_B = B.transfer_vec_sim();
    for(auto it = vec_A.begin(); it != vec_B.end(); it++){
        if(!(std::binary_search(vec_B.begin(), vec_B.end(), *it) ) ){
            A.erase(*it);
        }
    }
    A.balanced();
    return A;
}
