// entryPoint.hpp

/*

This is the true entry ppoint of the application.
It creates an instance of the Engine and sets the title for the window.
It also creates an instance of your game, and sets it as the layer for the engine.
Then run engine is ran, which hosts the main loop of the applicaiton.
All of the instances clean up their objects and the program exists cleanly.

*/


// Includes engine.
#include "Core/include/EngineCore.hpp"
// Includes your game layer.
#include "../ExampleGame/include/ExampleGame.hpp"


// The parameters (argc, argv) aren’t used here,
// but are provided if you later want to parse command-line arguments, such as file systems.
int main(int argc, int argv[])
{
    // Create game engine and game layer instance.
    /* 
    This creates instances of GLFW, OpenGL and GLAD and
    loads relevent core functionalities.
	If any loading is failed, the engine will close immidiately.
    */
    std::unique_ptr<EngineCore> engine = std::make_unique<EngineCore>("Example Render");

    // Creates your game layer.
    /*
    This is a shared pointer as the engine core holds onto the layer internally.    
    */
    std::shared_ptr<ExampleGame> gameLayer = std::make_shared<ExampleGame>();

    // Attaches your game layer to the engine.
    /*
    All overridden functions from Layer will be ran within the engine loop.
    Inputs are also proccessed, but through the static Input class.
    */
    engine->SetLayer(gameLayer);

    // Starts the main loop of the engine.
    /*
    Before entering the loop, OnStart() is ran first.
    Then within the loop, they are ran in this order...
    - OnUpdate()
	- OnRender()
	- OnImGuiRender()
    Then the core will swap the back buffers.
    And then poll events.
    */
    engine->runEngine(); 

    // Sets the engine to null.
    /*
    Engine will clean up its own pointers and objects.
    */
    engine = nullptr;

    // Return 0 to finish program.
    return 0;
}
