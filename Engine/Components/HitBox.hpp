#pragma once 
#include <entt/entt.hpp>

// Values for the hitbox of the player.
struct HitBox
{
	// Damage that a move should deal.
	float damage = 100.f;

	std::vector<entt::entity>hitEnemies;

	void addHitEnemy(entt::entity enemy)
	{
		hitEnemies.push_back(enemy);
	}

	void resetHitEnemies()
	{
		hitEnemies.clear();
	}

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