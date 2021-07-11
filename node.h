#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename K, typename V>
class Node
{
public:
    Node(const K key, const V val);
    K getKey() const;
    void setKey(const K key) { key_=key; }
    V getVal() const;
    void setVal(const V val) { val_=val; }
    int countChilds() const;
    void deleteNode();
    Node<K,V>* find(const K key);
    Node* left;
    Node* right;
    Node* parent;
private:
    K key_;
    V val_;
};

template<typename K, typename V>
Node<K,V>::Node(const K key, const V val) {
    key_ = key;
    val_ = val;
    left=right=nullptr;
}

template<typename K, typename V>
K Node<K,V>::getKey() const {
    return key_;
}

template<typename K, typename V>
V Node<K,V>::getVal() const {
    return val_;
}


template<typename K, typename V>
int Node<K,V>::countChilds() const {
    int c=0;
    if(left!=nullptr) {
        c++;
        c+=left->countChilds();
    }
    if(right!=nullptr) {
        c++;
        c+=right->countChilds();
    }
    return c;
}

template<typename K, typename V>
Node<K,V>* Node<K,V>::find(const K key) {
    if(this->getKey() > key) {
        if(this->left!=nullptr)
            return this->left->find(key);
        else
            return nullptr;
    }
    if(this->getKey() < key) {
        if(this->right!=nullptr)
            return this->right->find(key);
        else
            return nullptr;
    }
    if(this->getKey() == key) return this;
    return nullptr;
}

template<typename K, typename V>
void Node<K,V>::deleteNode(){
    if(left!=nullptr)
        left->deleteNode();
    if(right!=nullptr)
        right->deleteNode();
    delete this;
}

#endif // NODE_H
