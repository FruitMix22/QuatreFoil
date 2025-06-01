#pragma once 
#include <vector>
#include <entt/entt.hpp>

// Values for the hitbox of the player.
struct HitBox
{
	// Damage that an attack should deal.
	float damage = 100.f;

	std::vector<entt::entity>hitEnemies; // Enemies that have been hit.

	// Add an enemy to the hit enemies list.
	// @param enemy The enemy entity that has been hit.
	void addHitEnemy(entt::entity enemy)
	{
		hitEnemies.push_back(enemy);
	}

	// Reset the hit enemies list.
	void resetHitEnemies()
	{
		hitEnemies.clear();
	}

	// Check if an enemy has been hit.
	// @param hitEnemy The enemy entity to check.
	// @return True if the enemy has been hit, false otherwise.
	bool hasBeenHit(entt::entity hitEnemy)
	{
		for (const auto& enemy : hitEnemies)
		{
			if (enemy == hitEnemy)
				return true;
		}
		return false;
	}
};