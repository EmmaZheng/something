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



bool Manager::getQueueisFull(Manager &premanager, opcode op){
    switch (op) {
        case L:
            return premanager.addqueue.isFull();
            break;
        case S:
            return premanager.addqueue.isFull();
            break;
        
        case I:
            return premanager.intqueue.isFull();
            break;
        case B:
            return premanager.intqueue.isFull();
            break;
        case A:
            return premanager.fpqueque.isFull();
            break;
        case M:
            return premanager.fpqueque.isFull();
            break;
            
        default:
            break;
    }
    return false;
    
}

//void Manager::issueToFunctionUnit(Manager &premanage){
//    int current = premanage.activelist.head;
//    for (int i = 0; i < 32; i++) {
//        if (premanage.activelist.entries[(current + i) % 32].done == false) {//looking for the instruction to put into the queue;
//            
//        }
//    }
//}
void Manager::updatequeues(Manager &premanage){
    //update integer queue
    //update address queue
    //update fp queue
    
    
    
}
void Manager::updateFU(Manager &premanage){
    if (premanage.ALU1.busy) {
        activelist.entries[premanage.ALU1.index].done = true;
        ALU1.busy = false;
        //change the busy table as well: todo
        int rd = activelist.entries[premanage.ALU1.index].cur;
        busyTable[rd] = true;
        //ALU1 is done;
    }
    if (premanage.ALU2.busy) {
        activelist.entries[premanage.ALU2.index].done = true;
        ALU2.busy = false;
        int rd = activelist.entries[premanage.ALU2.index].cur;
        busyTable[rd] = true;
        //ALU2 is done;
    }
    //search if there is a branch in the integer queue; todo
    
    
    
    
}
void Manager::commit(Manager &premanage){
    if (premanage.activelist.entries[premanage.activelist.head].done == true) {
        activelist.head = activelist.head++ % 32;
        //this one should be committed. TODO
    }
}


void Manager::update(Manager &premanager){//after to push to active list. and update the queue the FU
    if (premanager.activelist.isEmpty()) {
        return;
    }
    //issue to functional units
    //issueToFunctionUnit(premanager);
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


void Manager::pushToaddQueue(Trace curTrace, Manager &preManager){
    addqueue.tail = (addqueue.tail++) % 32;
    addqueue.count++;
    addqueue.entries[addqueue.tail].op = curTrace.opcode;
    addqueue.entries[addqueue.tail].rd = curTrace.rd;
    addqueue.entries[addqueue.tail].rt = curTrace.rt;
    addqueue.entries[addqueue.tail].rs = curTrace.rs;
    addqueue.entries[addqueue.tail].address = curTrace.extra;
    
    addqueue.entries[addqueue.tail].indexAL = activelist.tail;
}
void Manager::pushToIntQueue(Trace curTrace, Manager &preManager){
    intqueue.count++;
    intqueue.entries[intqueue.tail()].op = curTrace.opcode;
    intqueue.entries[intqueue.tail()].rd = curTrace.rd;
    intqueue.entries[intqueue.tail()].rt = curTrace.rt;
    intqueue.entries[intqueue.tail()].rs = curTrace.rs;
    
    intqueue.entries[intqueue.tail()].indexAL = activelist.tail;
}
void Manager::pushToFPQueue(Trace curTrace, Manager &preManager){
    //todo
    fpqueque.count++;
    fpqueque.entries[fpqueque.tail()].op = curTrace.opcode;
    fpqueque.entries[fpqueque.tail()].rd = curTrace.rd;
    fpqueque.entries[fpqueque.tail()].rt = curTrace.rt;
    fpqueque.entries[fpqueque.tail()].rs = curTrace.rs;
    
    fpqueque.entries[fpqueque.tail()].indexAL = activelist.tail;
}


void Manager::pushToActiveList(Trace curTrace, Manager &preManager){//not sure if this is going to work
    // I am in the current manager;
    //and also push to queue TODO
    int curIndex = activelist.tail++ % numOfALEntries;
    activelist.count++;
    activelist.entries[curIndex].done = false;// set the done bit to false;
    activelist.entries[curIndex].op = curTrace.opcode; //record the opcode
    int newPRegister = preManager.getNewRegFreelist();
    
    activelist.entries[curIndex].cur = newPRegister;   //get new register from free list
    freelist[newPRegister] = false;  //update curManager's free list
    activelist.entries[curIndex].pre = preManager.getOldRegMapTable(curTrace.rd);  //get the old register from maptable
    mapTable[curTrace.rd] = newPRegister; //update curManager's maptable
    //push to coresponding queues

    
    switch (curTrace.opcode) {
        case L:
            pushToaddQueue(curTrace, preManager);//if I don't pass a reference will it work?
            break;
        case S:
            pushToaddQueue(curTrace, preManager);
            break;
        case I:
            pushToIntQueue(curTrace, preManager);
            break;
        case B:
            pushToIntQueue(curTrace, preManager);//branch instruction push to interger too.
            break;
        case A:
            pushToFPQueue(curTrace, preManager);
            break;
        case M:
            pushToFPQueue(curTrace, preManager);
            break;
            
        default:
            break;

    }
    commit(preManager);
    updateFU(preManager);
    updatequeues(preManager);
    
    
}