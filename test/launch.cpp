#include "../kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    cout << "Start Test" << endl;

    KASM::AsmController controller;
    controller.LoadScript("scripts/dev/conditionals.kasm");
    //controller.Test();
    controller.Run();

    return 0;
}