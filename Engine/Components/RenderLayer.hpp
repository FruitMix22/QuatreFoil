#pragma once

// Number of layers defined globaly.
constexpr size_t NUM_RENDER_LAYERS = 5;

// Layers for rending (rendered 0 -> 5)
enum class RenderLayer
{
	Background = 0,
	MidGround = 1,
	Characters = 2,
	ForeGround = 3, 
	UI = 4
};