#include <iostream>
#include <string>
#include "node.h"
#include "tree.h"
#include <assert.h>

using namespace std;

int main()
{
    /*tree.insert_node(20, "a");
    tree.insert_node(22, "aa");
    tree.insert_node(15, "aaa");
    tree.insert_node(12, "aaaa");
    tree.insert_node(18, "aaaaa");
    Tree<int,string> tree2(tree);
    Tree<int,string> tree3;
    tree3.insert_node(18, "aaaaa");
    cout << "Root objects: " << tree.count() << endl;
    bool f = tree.isExist(15);
    if(f==false)
        cout << "No elems with key" << endl;
    else
        cout << "Elem found" << endl;
    vector<string> t = tree.getAllVal();
    for(auto k : t){
        cout << k << endl;
    }
    tree.deleteElem(12);
    cout << "Root objects: " << tree.count() << endl; */
    /* tree.fromFile("C:\\Users\\andre\\Documents\\laba2_1\\test.txt");
    vector<string> t = tree.getAllVal();
    for(auto k : t){
        cout << k << endl;
    }
    cout << "Objects: " << tree.count() << endl;
    Tree<int, string> tree2(tree);
    tree.deleteElem(15);
    cout << "Objects: " << tree2.count() << endl;
    if(tree == tree2)
        cout << "YES!" << endl;
    tree.toFile("C:\\Users\\andre\\Documents\\laba2_1\\test2.txt");
    */
    Tree<int, string> tree;
    assert(tree.count() == 0);
    tree.insert_node(5544, "Furniture1");
    assert(tree.count() == 1);
    tree.insert_node(5544, "Fur1");
    assert(tree.count() == 1);
    assert(tree.isExist(5544));
    assert(tree[5544]=="Furniture1");
    tree.insert_node(2, "Furniture2");
    tree.insert_node(3, "Furniture3");
    tree.deleteElem(2);
    assert(tree.count()==2);
    tree.deleteElem(5);
    assert(tree.count()==2);
    assert(!tree.isExist(2));
    tree.deleteAll();
    Tree<int, string> tree2;
    assert(tree == tree2);
    tree.insert_node(2, "Furniture2");
    tree.insert_node(3, "Furniture3");
    Tree<int, string> tree3(tree);
    assert(tree == tree3);
    tree3.find(2)->setVal("Fur2");
    assert(!(tree == tree3));
    tree.toFile("C:\\Users\\andre\\Documents\\laba2_1\\demo.txt");
    Tree<int, string> tree4;
    tree4.fromFile("C:\\Users\\andre\\Documents\\laba2_1\\demo.txt");
    assert(tree == tree4);
    cout << "Tests are passed!" << endl;
    return 0;
}
