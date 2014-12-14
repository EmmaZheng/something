//
//  Master.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/13/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#ifndef OOO_Master_h
#define OOO_Master_h


#include "Manager.h"
using namespace std;


class Master{
public:
    Manager preManager;
    Manager curManager;
    int cycle;

    void init();
    void update(Trace curTrace);
};

//to memorize the last status maybe two managers.
void Master::init(){
    Manager preManager = Manager();
    Manager curManager = Manager();
    preManager.init();
    curManager.init();
    cycle = -1;
}



void Master::update(Trace curTrace){
    
    curManager.pushToActiveList(curTrace, preManager); //push curTrace to curManager but look at pre manager and also pusht to queues
    //if the queue is not full then active list must not be full
    curManager.update(preManager);
    preManager = curManager;//to replace with the updated manager
}

#endif
