#include <iostream>

#include "bucket.h"


int main(){

    Bucket<int,int> bucket;

    bucket.insert(2,3);
    bucket.insert(3,4);
    bucket.insert(4,5);
    bucket.insert(2,5);

    bucket.printBucket();

    auto val = bucket.find(2);

    bucket.erase(2);

    

    if(val.first){
        std::cout<<val.second;
    }
    else{
        std::cout<<"Key not found";
    }

    bucket.printBucket();


}
