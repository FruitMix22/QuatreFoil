// entryPoint.hpp
#include "Core/include/EngineCore.hpp"
#include "../ExampleGame/include/ExampleGame.hpp"

int main() 
{
    // Create game engine and game layer instance.
    std::unique_ptr<EngineCore> engine = std::make_unique<EngineCore>("Example Render");
    std::shared_ptr<ExampleGame> gameLayer = std::make_shared<ExampleGame>();

    engine->SetLayer(gameLayer);
    engine->runEngine(); // Main loop
    engine = nullptr;
    return 0;
}
