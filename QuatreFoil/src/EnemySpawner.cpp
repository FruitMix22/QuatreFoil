#include "../QuatreFoil/include/EnemySpawner.hpp"

EnemySpawner::EnemySpawner(entt::registry& registry) : m_registry(registry)
{}

void EnemySpawner::Update(float dt)
{
	m_timeSinceLastSpawn += dt;

	for (auto& enemy : m_enemies)
	{
		enemy->Update(dt);
	}

	if (m_waveCleared && m_timeSinceLastSpawn >= m_spawnCooldown)
	{
		Console::Log("Spawning wave " + m_waveNumber);
		SpawnWave();
		m_waveCleared = false;
		m_timeSinceLastSpawn = 0.0f;
	}

	auto& view = m_registry.view<EnemyComp>();
	if (view.begin() == view.end())
	{
		m_waveCleared = true;
		Console::Log("Wave cleared.");
	}

}

void EnemySpawner::SpawnWave()
{
	int enemiesToSpawn = m_waveNumber * 3;
	auto& view = m_registry.view<PlayerComp, Transform>();
	for (auto entity : view)
	{
		auto& transformPlayerComp = m_registry.get<Transform>(entity);
		
		int enemiesSpawned;
		for (enemiesSpawned = 0; enemiesSpawned < enemiesToSpawn; enemiesSpawned++)
		{
			glm::vec2 spawnPos = GetOffScreenPosition();
			glm::vec2 dir = glm::normalize(transformPlayerComp.position - spawnPos);

			auto enemy = std::make_unique<Enemy>(m_registry);
			enemy->CreateEnemy(spawnPos.x);
			Console::Log("Spawning enemy at: " + std::to_string(spawnPos.x));

			m_enemies.push_back(std::move(enemy));
		}

		Console::Log("Spawned " + std::to_string(enemiesSpawned) + " enemies.");
		m_waveNumber ++;
		break;
	}
}

glm::vec2 EnemySpawner::GetOffScreenPosition()
{
	float margin = 100.0f; 

	bool spawnLeft = rand() % 2 == 0;

	auto& view = m_registry.view<PlayerComp, Transform>();
	for (auto entity : view)
	{
		auto& transformPlayerComp = m_registry.get<Transform>(entity);

	
		float offscreenDistance = 600.f; 
		float spreadRange = 200.f;     

		bool spawnLeft = (rand() % 2) == 0;
		float baseX = spawnLeft ? transformPlayerComp.position.x - offscreenDistance
			: transformPlayerComp.position.x + offscreenDistance;

	
		float randomOffset = ((float)rand() / RAND_MAX) * 2.f * spreadRange - spreadRange;

		float spawnX = baseX + randomOffset;
		float spawnY = transformPlayerComp.position.y; 

		return glm::vec2(spawnX, spawnY);
	}
}
