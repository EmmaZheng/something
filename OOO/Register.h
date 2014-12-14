//
//  Register.h
//  OOO
//
//  Created by xiaoxiao zheng on 12/11/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#ifndef OOO_Register_h
#define OOO_Register_h
typedef enum opcode//This is the same as live link. input of trace files
{
    L,//load
    S,//Store
    I,//integer add or sub
    B,//branch
    A,//fadd
    M //fmul
    
}opcode;

#endif
