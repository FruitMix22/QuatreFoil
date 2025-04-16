#pragma once
#include "Core/include/Layer.hpp"

class QuatreFoil : public Layer
{
public:
	void OnAttach() override;
	void OnUpdate() override;
	void OnRender() override;
};