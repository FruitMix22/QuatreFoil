#pragma once 
#include <glm.hpp>

struct Animator
{
	// Sets neccesary values and defaults enum state.
	// @param sizeOfSheet: size of whole sprite sheet (x,y)
	// @param sizeOfOneSprite: size of just one frame (x,y)
	Animator(glm::vec2 sizeOfSheet, glm::vec2 sizeOfOneSprite)
	{
		// How much of the sprite the texture covers
		uvScale = glm::vec2(sizeOfOneSprite.x / sizeOfSheet.x, sizeOfOneSprite.y / sizeOfSheet.y);

		// Calculates how many frames there are in once row
		spritesPerRow = static_cast<int>(sizeOfSheet.x / sizeOfOneSprite.x);

		
		currentAnimState = animState::Idle; // Start with Idle animation state
		currentSprite = startIdle; // Start at idle for default
		timePassed = 0.0f; 
		animUpdate = 0.2f; 
	}

	glm::vec2 sizeOfSheet; // Size of sprite sheet (pixels)
	glm::vec2 sizeOfOneSprite; // Size of one frame (pixels)

	// (both normalised for texture coords)
	glm::vec2 uvScale; // How much UV space each sprite takes up on texture
	glm::vec2 uvOffset; // UV offset to select the current frame on the texture

	int spritesPerRow; // How many frames are in 1 row of the sprite sheet
	int currentSprite; // The current sprite to be shown 

	// Ranges for anims
	int startIdle = 0;
	int endIdle = 5;

	int startRun = 6;
	int endRun = 13;

	// Animation timing
	float animUpdate = 0.1f; // Time between frames
	float timePassed = 0.0f; // Additive time since last update

	// Current animation state enum
	enum class animState
	{
		Idle = 0,
		Running = 1,
		Attacking = 2
	};

	animState currentAnimState; // Current animaiton state

	// Calculates what sprite is active.
	// Run every frame.
	// @param dt: delta time (time between frames).
	void Update(float& dt)
	{
		timePassed += dt;

		// Only update if enough time has passed
		// (Avoids from sprite changing frames too fast)
		if (timePassed >= animUpdate)
		{
			timePassed = 0.0f;

			// Advance frame based on state
			switch (currentAnimState)
			{
				case animState::Idle:
				{

				// TODO: Abstract into a function
					int frameIndex = currentSprite;  // Calculate where to start
					int col = frameIndex % spritesPerRow;  // column is remainder
					int row = 0;  // idle is on first row

					// Calculate UV offset in texture space
					uvOffset = glm::vec2(col * uvScale.x, row * uvScale.y);

					// Advance frame to next
					currentSprite++;

					// Dont allow to go beyond frames that arent the current state
					if (currentSprite > endIdle) currentSprite = startIdle;
					break;

				}
				case animState::Running:
				{
					int frameIndex = currentSprite;  // Calculate where to start
					int col = frameIndex % spritesPerRow;  // column is remainder
					int row = frameIndex / spritesPerRow; // Row is integer left
					
					// Calculate UV offset in texture space
					uvOffset = glm::vec2(col * uvScale.x, row * uvScale.y);


					// Dont allow to go beyond frames that arent the current state
					currentSprite++;
					if (currentSprite > endRun) currentSprite = startRun;
					break;
				}

		
			}

		}
	}





	void setAnimState(Animator::animState state)
	{
		if (currentAnimState != state)
		{
			currentAnimState = state;
			// Reset frame to start of current animation
			switch (state)
			{
			case animState::Idle:
				currentSprite = startIdle;
				break;
			case animState::Running:
				currentSprite = startRun;
				break;
			}
		//TODO: Updates as more states are supported
		}
	}



};