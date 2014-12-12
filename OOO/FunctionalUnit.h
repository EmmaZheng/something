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
    int phase;
    int bound;
    BOOL busy;
};

class addressFU{
    int phase;
    int bound;
    BOOL busy;
};

class FPMul{
    int phase;
    int bound;
    BOOL busy;
};

class FPAdder{
    int phase;
    int bound;
    BOOL busy;
};

#endif
