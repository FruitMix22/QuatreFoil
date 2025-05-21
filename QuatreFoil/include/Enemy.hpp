#pragma once

#include "Renderer/include/Quad.hpp"
#include "entt/entt.hpp"
#include "Components/PlayerComp.hpp"
#include "Components/EnemyComp.hpp"
#include "Components/Transform.hpp"
#include "Components/RenderLayer.hpp"
#include "Components/Collider.hpp"
#include <memory>

class Enemy
{
public:
	Enemy(entt::registry& registry);
	~Enemy();

	entt::entity GetEntity() const;
	void Update(float dt);
	void CreateEnemy(float posX);

	void SpawnHitboxRight();
	void SpawnHitboxLeft();

	auto& GetTransformComp() const;
private:

	entt::registry& m_registry;
	std::unique_ptr<Quad> m_enemy;
	std::unique_ptr<Quad> m_hitBoxDebug;

	float hitboxTimeActive = 0.0f;
	float hitBoxTime = 0.5f;
	bool canAttack = true;
	glm::vec2& playerPos = glm::vec2(0.f, 0.f);
};
