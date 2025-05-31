#pragma once
// Variables relating to the player.
struct PlayerComp
{
	float health = 100.f; // Player health
	float speed = 100.f; // Player speed
	float damage = 20.f; // Player speed

	bool canAttack = true;
	bool hasBeenHit = false;
	float timeAccumulated = 0.f;

	void hit(float damage)
	{
		health -= damage;
		hasBeenHit = true;
	}
};