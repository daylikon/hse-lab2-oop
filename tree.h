#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<typename K, typename V>
class Tree
{
public:
    Tree();
    ~Tree();
    Tree(const Tree<K,V> &tree);
    void insert_node(const K key, const V val);
    Node<K,V> *getRoot();
    Node<K,V> *find(const K key);
    Node<K,V>* find_succsessor(const K key);
    Node<K,V>* find_min(Node<K,V>* node);
    bool isExist(const K key);
    void deleteElem(const K key);
    void deleteAll();
    vector<V> getAllVal();
    vector<K> getAllKeys();
    void getVal(Node<K,V> *&root);
    int count() const;
    void toFile(string filename) const;
    void fromFile(string filename);
    V operator[](const K key) {
        if(isExist(key)) {
            Node<K,V>* node = find(key);
            return node->getVal();
        }
        return 0;
    };
    bool operator ==(Tree &other);
private:
    Node<K,V> *root;
    vector<V> values;
    vector<K> keys;
};

// Конструктор по умолчанию
template<typename K, typename V>
Tree<K,V>::Tree() {
    root = nullptr;
}

// Конструктор копирования
template<class K, class V>
Tree<K, V>::Tree(const Tree &tree)
{
    root = new Node<K, V>(*tree.root);
}

template<typename K, typename V>
void Tree<K,V>::insert_node(const K key, const V val) {
    Node<K,V>* n = new Node<K,V>(key, val);
    Node<K,V>* ptr;
    Node<K,V>* ptr1 = nullptr;

    n->parent=n->left=n->right=nullptr;
    ptr=root;
    while(ptr!=nullptr) {
        ptr1=ptr;
        if(key < ptr->getKey())
            ptr=ptr->left;
        else
            ptr=ptr->right;
    }
    n->parent=ptr1;
    if(ptr1==nullptr) {
        root=n;
    }
    else {
        if(!isExist(key)) {
            if(key < ptr1->getKey())
                ptr1->left=n;
            else
                ptr1->right=n;
        }
    }
}

template<typename K, typename V>
Node<K,V>* Tree<K,V>::getRoot() {
    return root;
}

template<typename K, typename V>
int Tree<K,V>::count() const {
    if(root==nullptr) return 0;
    return 1+(root->countChilds());
}

template<typename K, typename V>
Node<K,V>* Tree<K,V>::find(const K key) {
    return root->find(key);
}

template<typename K, typename V>
bool Tree<K,V>::isExist(const K key) {
    if(find(key)!=nullptr) return true;
    return false;
}

template<class K, class V>
void Tree<K,V>::getVal(Node<K,V> *&root) {
    if(root==nullptr) return;
    getVal(root->left);
    values.push_back(root->getVal());
    keys.push_back(root->getKey());
    getVal(root->right);
}

template<class K, class V>
vector<V> Tree<K,V>::getAllVal() {
    values.resize(0);
    getVal(root);
    return values;
}

template<class K, class V>
vector<K> Tree<K,V>::getAllKeys() {
    keys.resize(0);
    getVal(root);
    return keys;
}

template<typename K, typename V> //перегрузка оператора ==
bool Tree<K, V>::operator ==(Tree &other)
{
    vector<V> val1 = getAllVal();
    vector<K> keys1 = getAllKeys();
    vector<V> val2 = other.getAllVal();
    vector<K> keys2 = other.getAllKeys();
    int s = keys2.size();
    if(keys1.size() != keys2.size()) return false;
    for(int i=0;i<s;i++) {
        if(val1[i] != val2[i])
            return false;
    }
    return true;
}

template<typename K, typename V>
void Tree<K,V>::deleteAll() {
    root->deleteNode();
    root=nullptr;
}

template<typename K, typename V>
Tree<K,V>::~Tree() {
    delete root;
}

template<typename K, typename V>
void Tree<K,V>::deleteElem(const K key) {
    Node<K,V>* z;
    if(isExist(key)) {
        z = find(key);
        Node<K,V>* x;
        Node<K,V>* y;
        if(z->left==nullptr && z->right==nullptr) {
            x=z->parent;
            if(x->left==z)
                x->left=nullptr;
            if(x->right==z)
                x->right=nullptr;
            delete z;
        } else {
            if(z->left==nullptr || z->right==nullptr) {
                x=z->parent;
                if(x->left == z) {
                    if(z->right==nullptr)
                        x->left=z->left;
                    else
                        x->left=z->right;
                }
                else {
                    if(z->right==nullptr) {
                        x->right=z->left;
                    }
                    else {
                        x->right=z->right;
                    }
                }
                delete z;
            }
            else {
                x=z->right;
                while(x->left!=nullptr) {
                    x=x->left;
                }
                y=x->parent;
                z->setKey(x->getKey());
                z->setVal(x->getVal());
                if(x->right!=nullptr)
                    y->left=x->right;
                else
                    y->left=nullptr;
                delete x;
            }
        }
    }
}

template<typename K, typename V>
Node<K,V>* Tree<K,V>::find_min(Node<K,V>* x)
{
        while(x->left!=nullptr)
                x=x->left;
        return x;
}

template<typename K, typename V>
Node<K,V>* Tree<K,V>::find_succsessor(const K key)
{
        Node<K,V>* x;
        if(isExist(key))
            x = find(key);
        Node<K,V>* y;
        if(x == nullptr)
                return nullptr;
        if(x->right!=nullptr)
                return find_min(x->right);
        y=x->parent;
        while(y!=nullptr && x == y->right)
        {
                x=y;
                y=y->parent;
        }
        return y;
}

template<typename K, typename V>
void Tree<K,V>::toFile(string filename) const {
    fstream s(filename, s.binary | s.trunc | s.out);
    if (!s.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        int ks = keys.size();
        for(int i=0;i<ks;i++) {
            s << keys[i] << " " << values[i] << endl;
        }
        s.close();
    }
}

template<typename K, typename V>
void Tree<K,V>::fromFile(string filename) {
    getAllVal();
    fstream s(filename, s.binary | s.in);
    if (!s.is_open()) {
        std::cout << "failed to open " << filename << '\n';
    } else {
        root = nullptr;
        while(!s.eof()) {
            K k;
            V v;
            s >> k >> v;
            insert_node(k,v);
        }
        s.close();
    }
}

#endif // TREE_H
