#include "EngineCore.hpp"
#include <filesystem>

int main()
{
	std::filesystem::path vert("../QuatreFoil/Assets/Shaders/TriangleVert.glsl");
	std::filesystem::path frag("../QuatreFoil/Assets/Shaders/TriangleFrag.glsl");

	EngineCore engine;
	engine.setVertPath(vert);
	engine.setFragPath(frag);
	engine.loadEngine("Test Window");
	engine.runEngine();





}