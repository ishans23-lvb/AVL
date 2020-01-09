//
//  main.cpp
//  AVL
//
//  Created by Ishan Shah on 1/8/20.
//  Copyright © 2020 Ishan Shah. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include "tree.hpp"
using namespace std;



int main(int argc, const char * argv[])
{
    tree<int> t;
    
    t.insert(7);
    t.insert(10);
    t.insert(11);
    t.insert(8);
    t.insert(6);
    t.insert(5);
    
    t.print();
    
    
    return 0;
}
