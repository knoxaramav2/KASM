#include "../kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    cout << "Test" << endl;

    KASMController controller;
    controller.LoadScript("scripts/test.kasm");

    return 0;
}