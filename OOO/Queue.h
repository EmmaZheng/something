//
//  IntegerQueue.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/11/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//


#include "Register.h"
#include <vector>
#include <iostream>
#ifndef OOO_IntegerQueue_h
#define OOO_IntegerQueue_h
using namespace std;
//also known as reservation stations
class queueEntry{
public:
    bool busy;
    int rd;
    int rt;
    int rs;
    opcode op;
    int indexAL;
    
};

class addEntry: public queueEntry{
public:
    string address;
};

//integer queue is not fifo.. Everytime we just need to search whoever oprands ready first
class IntegerQueue{
public:
    queueEntry entries[32];
    int count;
    
    IntegerQueue(){
        count = 0;
    }
    bool isFull(){
        return count == 32? true:false;
    }
    bool isEmpty(){
        return count == 0? true:false;
    }
    int tail(){
        for (int i = 0; i < 32; i++) {
            if(!entries[i].busy){
                return i;
            }
        }
        return -1;
    }
};


class FPQueue{//circular queue
public:
    queueEntry entries[32];
    int count;
    FPQueue(){
    
        count = 0;
    }
    bool isFull(){
        return count == 32? true:false;
    }
    bool isEmpty(){
        return count == 0? true:false;
    }
    int tail(){
        for (int i = 0; i < 32; i++) {
            if(!entries[i].busy){
                return i;
            }
        }
        return -1;
    }
};
//address queue is fifo. it will not get out of queue unless it is committed.

class AddQueue{//address queue
public:
    addEntry entries[32];//No need to new. why? roger
    int count;
    int head;
    int tail;
    AddQueue(){
        head = 0;
        tail = 0;
        count = 0;
    }
    
    bool isFull(){
        return count == 32? true:false;
    }
    bool isEmpty(){
        return count == 0? true:false;
    }
};
#endif
