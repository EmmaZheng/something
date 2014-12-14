//
//  ActiveList.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/12/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//


//pipeline for each intruction type

//for integer add F D I A C
//for branch      F D I B C
//for FP add      F D I FA1 FA2 FA3 C
//for FP mul      F D I FM1 FM2 FM3 C
//for load&store  F D I L1  L2  C



//typedef enum opcode//This is the same as live link. input of trace files
//{
//    L,//load
//    S,//Store
//    I,//integer add or sub
//    B,//branch
//    A,//fadd
//    M //fmul
//    
//}opcode;
#include "Register.h"

#ifndef OOO_ActiveList_h
#define OOO_ActiveList_h
//Reorder buffer. Used to issue

#define numOfALEntries 32

class ALEntry{
public:
    bool done;
    opcode op;
    int cur;//current rd;
    int pre;//old rd;
    int rs;//coresponding physical register rs
    int rt;//coresponding physical register rt
    //to push to address queue

};


class ActiveList{
public:
    int head;
    int tail;
    int count;//circular queue
    
    
    ALEntry *entries;// I am not sure how this works. roger
    
    ActiveList(){
        entries = new ALEntry[numOfALEntries];//32 entries in the table
        head = 0;
        tail = 0;
        count = 0;
    }
    bool isFull();
    bool isEmpty();
};


bool ActiveList::isFull(){
    if (count == 32) {
        return true;
    }
    return false;
}

bool ActiveList::isEmpty(){
    if (count == 0) {
        return true;
    }
    else return false;
}

#endif
