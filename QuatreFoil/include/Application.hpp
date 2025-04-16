#pragma once
#include "Core/include/EngineCore.hpp"
#include "QuatreFoil.hpp"

EngineCore* StartApplication()
{
    EngineCore* core = new EngineCore();
    QuatreFoil* gameLayer = new QuatreFoil();

    core->SetLayer(gameLayer);
    return core;
}
