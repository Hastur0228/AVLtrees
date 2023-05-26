#include <iostream>
#include "AvlTree.h"
using namespace std;
void display(SET<int, char*>* p) 
{
    if (p != NULL) cout << p->key << ", " << p->other << endl;
}
void rotation(bool r) 
{
    if (r) cout << "With rotation." << endl;
    else cout << "No rotation." << endl;
}
int main() 
{
    SET<int, char*> a[] = { {14,(char*)"fff"}, {28,(char*)"iii"}, {9,(char*)"ddd"}, {18,(char*)"hhh"},
                           {12,(char*)"eee"}, {50,(char*)"kkk"}, {5,(char*)"bbb"}, {17,(char*)"ggg"},
                           {7,(char*)"ccc"}, {30,(char*)"jjj"}, {3,(char*)"aaa"}, {60,(char*)"mmm"},
                           {30,(char*)"jjj"}, {53,(char*)"lll"}, {63,(char*)"nnn"} };
    AvlTree<int, char*> tree;
    for (int i = 0; i < 15; ++i) 
    {
        rotation(tree.insert(a[i]));
    }
    rotation(tree.insert({ 8,"xxx" }));
    rotation(tree.insert({ 4,"yyy" }));
    rotation(tree.insert({ 61,"zzz" }));
    for (int i = 0; i < 64; ++i) {
        display(tree.find(i));
    }
    return 0;
}