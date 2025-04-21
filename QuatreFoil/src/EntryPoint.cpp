// entryPoint.hpp
#include "Core/include/EngineCore.hpp"
#include "../QuatreFoil/include/QuatreFoil.hpp"

int main() 
{
    std::unique_ptr<EngineCore> engine = std::make_unique<EngineCore>("QuatreFoil");
    std::shared_ptr<QuatreFoil> gameLayer = std::make_shared<QuatreFoil>();
    engine->SetLayer(gameLayer);
    engine->runEngine(); 
    engine = nullptr;
    return 0;
}
