//
//  IntegerQueue.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/11/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//


#include "Register.h"
#ifndef OOO_IntegerQueue_h
#define OOO_IntegerQueue_h
using namespace std;
//also known as reservation stations
class queueEntry{
public:
    int rd;
    int rt;
    int ts;
    opcode op;
    
};

class addEntry: public queueEntry{
public:
    string address;
};

class IntegerQueue{
public:
    queueEntry entries[32];
    int head;
    int tail;
    int count;
    
    IntegerQueue(){
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


class FPQueue{//circular queue
public:
    queueEntry entries[32];
    int head;
    int tail;
    int count;
    FPQueue(){
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


class AddQueue{//address queue
public:
    addEntry entries[32];//No need to new. why? roger
    int head;
    int tail;
    int count;
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
