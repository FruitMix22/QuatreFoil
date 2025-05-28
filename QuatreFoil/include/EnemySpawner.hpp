#pragma once
#include <entt/entt.hpp>
#include <glm.hpp>
#include "Components/PlayerComp.hpp"
#include "../QuatreFoil/include/Enemy.hpp"
#include "Components/EnemyComp.hpp"
#include "Components/Transform.hpp"
#include "Core/include/Console.hpp"

class EnemySpawner
{
public:
	EnemySpawner(entt::registry& registry);

	void Update(float dt);

	// DEBUG TOOL
	void KillAllEnemies();

	void RemoveDeadEnemy(entt::entity& deadEntities);

private:
	void SpawnWave();
	glm::vec2 GetOffScreenPosition();


	entt::registry& m_registry;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	int m_waveNumber = 1;
	float m_timeSinceLastSpawn = 0.f;
	float m_spawnCooldown = 2.0f;
	bool m_waveCleared = false;
};