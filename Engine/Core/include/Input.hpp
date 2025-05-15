#pragma once
#include <GLFW/glfw3.h>
#include <functional>
#include <unordered_map>
#include <vector>
#include <iostream>

// Handles inputs for the engine.
// Runs callbacks from GLFW.
class Input
{
public:
	// Sets window reference and triggers KeyCallBacks.
	// @param windowTitle: Title of the window.
	// @return TRUE if passes, or FALSE if it fails.
	static bool Init(GLFWwindow* window);

	// Register a function to be ran when a key is pressed.
	// @param key: GLFW Key. @param function: Function to be ran when pressed (lambda).
	static void RegisterCallBack(int key, std::function<void()> function);

	// Process the inputs
	static void ProcessInput();
private:
	// Ran whenever as key input is heard.
	// Checks for any functions for certain keys.
	// Doesnt need to be ran by user, is automatically called by GLFW when key press happens.
	// @param window: Current window context.
	// @param key: Key that is being checked.
	// @param scancode: Raw keyboard input.
	// @param action: GLFW state eg... Pressed? Released?
	// @param mods: Modifier keys, like shift.
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	
	static inline GLFWwindow* m_window = nullptr; // GLFW window pointer
	static inline std::unordered_map<int, bool> m_keyStates; 	// Current key state
	static inline std::unordered_map<int, std::vector<std::function<void()>>>m_keyMap; 	// Stores keys and functions to be ran.

};