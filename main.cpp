#include <iostream>

#include "node.h"


int main(){

    Node<int,int> a(2,3);
    Node<std::string,int> b("hello",4);

    a.printNode();
    a.setValue(5);
    a.printNode();
    b.printNode();


}
