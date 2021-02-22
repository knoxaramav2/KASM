#include "externalLoaders.hpp"
#include "instructionRegistery.hpp"
#include "controller.hpp"
#include "graphics.hpp"

void KASM::LoadGraphics(KASM::AsmController&ctrl){

    KASM::GRAPHICS::InitGraphics(ctrl);    
}