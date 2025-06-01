// entryPoint.hpp
#include "Core/include/EngineCore.hpp"
#include "../QuatreFoil/include/QuatreFoil.hpp"

int main() 
{
    // Create game engine and game layer instance.
    std::unique_ptr<EngineCore> engine = std::make_unique<EngineCore>("QuatreFoil");
    std::shared_ptr<QuatreFoil> gameLayer = std::make_shared<QuatreFoil>();

    engine->SetLayer(gameLayer);
    engine->runEngine(); // Main loop
    engine = nullptr;
    return 0;
}
