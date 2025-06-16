#include <iostream>
#include <string>
#include "view.h"
#include "BreakoutController.h"
#include "AnsiPrint.h"
/**
 * Print my id
 * */
void
PrintMyID(std::string studId) {

    std::string str = "ID: " + studId;
    std::cout << AnsiPrint(str.c_str(),YELLOW,RED, true, true) << std::endl << std::endl;
}



int main(){
    View view;
    BreakoutController controller(view);
    try{
        controller.run();
    }// TODO 


    // TODO
    // change to your student ID.
    catch (endGame&){
        PrintMyID("113703023");
    }
}
