#include "../kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    cout << "Start Test" << endl;

    KASMController controller;
    controller.LoadScript("scripts/dev/test.kasm");

    return 0;
}