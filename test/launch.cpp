#include "../kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    cout << "Start Test" << endl;

    KASM::AsmController controller;
    controller.LoadScript("scripts/dev/hw.kasm");
    //controller.Test();
    controller.Run();

    cout << endl << endl << "END" << endl;

    return 0;
}