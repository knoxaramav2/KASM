#include "externalLoaders.hpp"
#include "instructionRegistery.hpp"
#include "controller.hpp"

#include "../graphics/drawable.hpp"

void KASM::LoadGraphics(KASM::AsmController&ctrl){

    KASM::InitGraphics();

    ctrl.RegisterCommand("pushxwin", _pushWindow);
    
}