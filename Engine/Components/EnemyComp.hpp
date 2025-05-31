#pragma once
// Simple component for Enemies.
struct EnemyComp
{
	// Health of the enemy.
	float health = 100.f;
	// Speed of the enemy.
	float speed = 30.f;
	// Damage
	float damage = 20.f;

	bool canAttack = true;
	bool hasBeenHit = false;
	float timeAccumulated = 0.f;

	void hit(float damage)
	{
		health -= damage;
		hasBeenHit = true;
	}
};
