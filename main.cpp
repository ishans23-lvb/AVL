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


void test1(void);

int main(int argc, const char * argv[])
{
    test1();
    
    return 0;
}

void test1(void)
{
    tree<int> t;
    for(int i=0;i<1000;i++)
    {
        int rn=rand();
        t.insert(rn);
        t.print();
    }
}
