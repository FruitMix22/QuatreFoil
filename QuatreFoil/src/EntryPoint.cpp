// entryPoint.hpp
#include "Core/include/EngineCore.hpp"
#include "../QuatreFoil/include/QuatreFoil.hpp"

int main() 
{
    std::unique_ptr<EngineCore> engine = std::make_unique<EngineCore>("Title");

    //CHANGE TO A SMARTT POINTER
    QuatreFoil *gameLayer = new QuatreFoil();
    engine->SetLayer(gameLayer);
    engine->runEngine(); 
    engine = nullptr;
    delete gameLayer;
    return 0;
}
