#pragma once

#include "Renderer/include/Quad.hpp"
#include "entt/entt.hpp"
#include "Components/PlayerComp.hpp"
#include "Components/Transform.hpp"
#include <memory>


class Player
{
public:
	Player(entt::registry& registry);
	~Player();

	entt::entity GetEntity() const;
	void Update(float dt);
	void CreatePlayer();

	void SpawnHitboxRight();

	// Move player by a distance.
	// @param speed: Speed that the player moves by.
	void moveX(float const speed, float const dt);

	auto& Player::GetTransformComp() const;
private:

	entt::registry& m_registry;
	std::unique_ptr<Quad> m_player;
	std::unique_ptr<Quad> m_hitBoxDebug;

	float hitboxTimeActive = 0.0f;
	float hitBoxTime = 2.f;
	bool canAttack = true;
	Transform* transformPlayerComp = nullptr;
};
