#pragma once
#include "Core/include/Input.hpp"

bool Input::Init(GLFWwindow* window)
{
	// Set window context and register call backs.
	m_window = window;
	if (m_window == nullptr)
	{
		std::cerr << "Failed to set window reference in Input!\n";
		return false;
	}
	if (!glfwSetKeyCallback(m_window, KeyCallback))
	{
		return false;
	}

	return true;
}

void Input::RegisterCallBack(int key, std::function<void()> function)
{
	// Add a new key to the vector, and relevent function to be ran if pressed.
	m_keyMap[key].push_back(std::move(function));
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_keyStates[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		m_keyStates[key] = false;
	}
}

void Input::ProcessInput()
{
	for (const auto& [key, isPressed] : m_keyStates)
	{
		if (isPressed)
		{
			// Look at the key thats pressed 
			auto pressedKey = m_keyMap.find(key);
			// If it exists
			if (pressedKey != m_keyMap.end())
			{
				for (auto& function : pressedKey->second)
					function();
			}
		}
	}
}
