#include "../src/kasm/kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    string file = "scripts/dev/caller.kasm";

    if (argc >= 2){
        file = argv[1];
    }

    cout << "Start Test" << endl;

    KASM::AsmController controller;
    KASM::LoadGraphics(controller);
    

    return 0;
}