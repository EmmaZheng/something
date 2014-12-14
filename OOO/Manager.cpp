//
//  Manager.cpp
//  OOO
//
//  Created by xiaoxiao zheng on 12/14/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#include <stdio.h>
#include "Manager.h"

void Manager::init(){
    //initilize the busy table
    for (int i = 0; i < 31; i++) {
        busyTable[i] = true;
        mapTable[i] = i;
        freelist[i] = false;
    }
    for (int i = 31; i < 64; i++) {
        busyTable[i] = false;
        freelist[i] = true;
    }
    activelist = ActiveList();
    intqueue = IntegerQueue();
    addqueue = AddQueue();
    fpqueque = FPQueue();
    
    //initialize the functional unit
    
    ALU1 = ALU();
    ALU2 = ALU();
    addFU = addressFU();
    fpmul = FPMul();
    fpadder = FPAdder();
}



void Manager::issueToFunctionUnit(Manager &premanage){
    int current = premanage.activelist.head;
    for (int i = 0; i < 32; i++) {
        if (premanage.activelist.entries[(current + i) % 32].done == false) {//looking for the instruction to put into the queue;
            
        }
    }
}
void Manager::updatequeues(Manager &premanage){
    
}
void Manager::updateFU(Manager &premanage){
    
}
void Manager::commit(Manager &premanage){
    
}


void Manager::update(Manager &premanager){//after to push to active list. and update the queue the FU
    if (premanager.activelist.isEmpty()) {
        return;
    }
    //issue to functional units
    issueToFunctionUnit(premanager);
    updatequeues(premanager);
    updateFU(premanager);
    commit(premanager);
}

int Manager::getNewRegFreelist(){
    for (int i = 0; i < 64; i++) {
        if( freelist[i] == true ){
            return i;
        }
    }
    return -1;
}
int Manager::getOldRegMapTable(int rd){
    for (int i = 0; i < 32; i++) {
        if (i == rd) {
            return mapTable[rd];//return its physical address
        }
    }
    return -1;
}

void Manager::pushToActiveList(Trace curTrace, Manager &preManager){//not sure if this is going to work
    // I am in the current manager;
    int curIndex = activelist.tail++ % numOfALEntries;
    activelist.count++;
    activelist.entries[curIndex].done = false;// set the done bit to false;
    activelist.entries[curIndex].op = curTrace.opcode; //record the opcode
    int newPRegister = preManager.getNewRegFreelist();
    
    activelist.entries[curIndex].cur = newPRegister;   //get new register from free list
    freelist[newPRegister] = false;  //update curManager's free list
    activelist.entries[curIndex].pre = preManager.getOldRegMapTable(curTrace.rd);  //get the old register from maptable
    mapTable[curTrace.rd] = newPRegister; //update curManager's maptable
}