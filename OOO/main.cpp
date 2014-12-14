//
//  main.cpp
//  OOO
//
//  Created by xiaoxiao zheng on 12/11/14.
//  Copyright (c) 2014 xiaoxiao zheng. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Master.h"

using namespace std;

/*typedef enum opcode//This is the same as live link. input of trace files
{
    L,//load
    S,//Store
    I,//integer add or sub
    B,//branch
    A,//fadd
    M //fmul
    
}opcode;
*/


Trace decode(string instruction){
    Trace newTrace = *new Trace();
    
    if (instruction.size() == 0) {
        return newTrace;
    }
    opcode opcode;
    switch (instruction[0]) {
        case 'L':
            opcode = L;
            break;
        case 'S':
            opcode = S;
        case 'I':
            opcode = I;
        case 'B':
            opcode = B;
        case 'A':
            opcode = A;
        case 'M':
            opcode = M;
        default:
            break;
    }
    string rdString = instruction.substr(2,2);
    string rsString = instruction.substr(5,2);
    string rtString = instruction.substr(8,2);
    string extra;
    if (instruction.size() > 10) {
        extra = instruction.substr(11, 8);
    }
    int rd = stoi(rdString, nullptr, 16);
    int rs = stoi(rsString, nullptr, 16);
    int rt = stoi(rtString, nullptr, 16);
    newTrace.opcode = opcode;
    newTrace.rs = rs;
    newTrace.rd = rd;
    newTrace.rt = rt;
    newTrace.extra = extra;
//    cout<<rs<<endl;
//    cout<<rt<<endl;
//    cout<<rd<<endl;
//    cout<<extra<<endl;
    return newTrace;
    
}

vector<Trace> readTraceFile(){
    ifstream infile;
    infile.open("trace.txt");
    string line;
    vector<Trace> tracefile;
    while (!infile.eof())
    {
        getline(infile, line);
        Trace newTrace = decode(line);
        tracefile.push_back(newTrace);
    }
    
    infile.close();
    return tracefile;
    
    
}

int main(int argc, const char * argv[]) {
    Master master;
    master.init();
    vector<Trace> traceFile;
    traceFile = readTraceFile();
    for (int i = 0; i < traceFile.size(); i++) {
        master.cycle++;
        if (master.preManager.activelist.isFull() || master.preManager.getQueueisFull(master.preManager, traceFile[i].opcode)) {
            //if the activation list is full or the coresponding queue is full then don't fetch stop at decode.
            //TODO. seems to remember that it needs to decode
            i--;
        }
        else{
            master.update(traceFile[i]);
        }
        
        
    }
    
    return 0;
}
