//
//  Manager.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/13/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#ifndef OOO_Manager_h
#define OOO_Manager_h

#include "ActiveList.h"
#include "Queue.h"
#include "FunctionalUnit.h"

class Trace{
public:
    opcode opcode;
    //    string rd;
    //    string rs;
    //    string rt;
    int rd;
    int rs;
    int rt;
    string extra;
};

class Manager{
public:
    unsigned long cycle;
    vector<Trace> tracefile;
    ActiveList activelist;
    IntegerQueue intqueue;
    AddQueue addqueue;
    FPQueue fpqueque;
    ALU ALU1;
    ALU ALU2;
    addressFU addFU;
    FPAdder fpadder;
    FPMul fpmul;
    
    
    void init();
    void pushToActiveList(Trace curTrace, Manager &preManager);
    
    bool busyTable[64];//the register contain the valid value;
    int mapTable[32]; // logical to physical
    bool freelist[64];//can free list be 64? I thought it was 32
    
    int getNewRegFreelist();
    int getOldRegMapTable(int rd);
    void update(Manager &premanage);
    
    //update subfunctions
    void issueToFunctionUnit(Manager &premanage);
    void updatequeues(Manager &premanage);
    void updateFU(Manager &premanage);
    void commit(Manager &premanage);
};



#endif
