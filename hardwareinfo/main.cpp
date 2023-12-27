
#include <iostream>
#include <string>

#include "InstructionSet.h"

int main(){

    printSupport();
    
    std::cout<<"cpu id [ "<<GetCpuIndex()<<" ]"<<std::endl;

    return 0;
}