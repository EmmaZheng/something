//
//  ActiveList.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/12/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#include "InstructionType.h"

//pipeline for each intruction type

//for integer add F D I A C
//for branch      F D I B C
//for FP add      F D I FA1 FA2 FA3 C
//for FP mul      F D I FM1 FM2 FM3 C
//for load&store  F D I L1  L2  C


typedef enum InstType
{
    IntALU,
    Rd,
    Wr,
    IntMult
} InstType;

typedef enum opcode//This is the same as live link. input of trace files
{
    L,//load
    S,//Store
    I,//integer add or sub
    B,//branch
    A,//fadd
    M //fmul
    
}opcode;


#ifndef OOO_ActiveList_h
#define OOO_ActiveList_h
//Reorder buffer. Used to issue

#define numOfALEntries 32
class ALEntry{
public:
    bool done;
    InstType instType;
    int cur;
    int pre;

};


class ActiveList{
public:
    bool isEmpty;
    bool isFull;
    int head;
    int tail;
    int count;//circular queue
    
    
    ALEntry *entries;// I am not sure how this works. Roger
    
    ActiveList(){
        isEmpty = true;
        entries = new ALEntry[numOfALEntries];//32 entries in the table
    }
};

#endif
