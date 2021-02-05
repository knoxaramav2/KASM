#include "../kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    cout << "Start Test" << endl;

    KASM::AsmController controller;
    controller.LoadScript("scripts/dev/test.kasm");
    controller.Test();

    return 0;
}