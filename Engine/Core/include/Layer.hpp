#pragma once

// Abstract class for user to create their own child class from.
// Allows the engine to run code wrote in the users game project.
class Layer
{
public:
	// Runs when is attatched to the engine.
	virtual void OnAttach(){}
	// Runs when the engine core is started.
	virtual void OnStart() {};
	// Runs every frame before anything is rendered.
	virtual void OnUpdate(){}
	// Runs ImGui every frame.
	virtual void OnImGuiRender(){}
	// Runs every frame.
	virtual void OnRender(){}

	bool m_terminate = false;
	float m_dt = 0.0f;
	float fpsTimeAccumulate = 0.0f;

	enum class EngineMode
	{
		Editor,
		Gameplay
	};

	EngineMode m_currentMode = EngineMode::Editor;
};