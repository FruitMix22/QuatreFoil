#pragma once 
#include <glm.hpp>

struct Animator
{
	Animator(glm::vec2 sizeOfSheet, glm::vec2 sizeOfOneSprite)
	{
		uvScale = glm::vec2(sizeOfOneSprite.x / sizeOfSheet.x, sizeOfOneSprite.y / sizeOfSheet.y);
		currentAnimState = animState::Idle;
		currentSprite = 0;
	}
	glm::vec2 sizeOfSheet;
	glm::vec2 sizeOfOneSprite;
	
	size_t spriteX;
	size_t spriteY;
	glm::vec2 uvScale;
	glm::vec2 uvOffset;

	int startIdle = 0;
	int endIdle = 6;
	int currentSprite;

	float animUpdate = 0.2f;
	float timePassed = 0.0f;

	
	void Update(float& dt)
	{
		timePassed += dt;

		if (timePassed >= animUpdate)
		{
			timePassed = 0.0f;

			switch (currentAnimState)
			{
			case animState::Idle:
			{
				uvOffset = glm::vec2(currentSprite * uvScale.x, 0.0f);

				currentSprite += 1;
				if (currentSprite > endIdle) {
					currentSprite = startIdle;
				}
				break;
			}
			}
		}
	}



	enum class animState
	{
		Idle = 0,
		Running = 1,
		Attacking = 2
	};

	void setAnimState(Animator::animState state)
	{
		currentAnimState = state;
	}

private:
	animState currentAnimState = animState::Idle;
};