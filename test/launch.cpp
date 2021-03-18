#include "../src/kasm/kasm.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv){

    string file = "scripts/dev/graphics.kasm";

    if (argc >= 2){
        file = argv[1];
    }

    cout << "Start Test" << endl;

    KASM::AsmController controller;
    KASM::LoadGraphics(controller);
    
    if (!controller.LoadScript(file)){
        cout << "Compilation failed." << endl;
        return -1;
    }
    controller.Run();

    return 0;
}