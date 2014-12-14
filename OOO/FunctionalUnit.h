//
//  FunctionalUnit.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/12/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#ifndef OOO_FunctionalUnit_h
#define OOO_FunctionalUnit_h


class ALU{
public:
    bool busy;
    int index;//where is it in the active list.
    ALU(){
        index = 0;
        busy = false;
    }
};

class addressFU{
public:
    int steps[2] = {-1, -1};
    bool isFull(){
        if (steps[0] != -1 && steps[1] != -1) {
            return true;
        }
        return false;
    }
};

class FPMul{
public:
    int steps[3] = {-1, -1, -1};
    bool isFull(){
        if (steps[0] != -1 && steps[1] != -1 && steps[2] != -1) {
            return true;
        }
        return false;
    }
    


};

class FPAdder{
public:
    int steps[3] = {-1, -1, -1};
    bool isFull(){
        if (steps[0] != -1 && steps[1] != -1 && steps[2] != -1) {
            return true;
        }
        return false;
    }
};

#endif
