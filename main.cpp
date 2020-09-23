#include <iostream>

#include "map.h"


int main(){

    map<int,int> hello;

    hello.insert(2,3);
    hello.insert(3,2);
    hello.insert(2,4);
    hello.insert(3,4);


    hello.printKeyBucket(2);


}
