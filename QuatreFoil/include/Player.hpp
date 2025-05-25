#pragma once

#include "Renderer/include/Quad.hpp"
#include "entt/entt.hpp"
#include "Components/PlayerComp.hpp"
#include "Components/Transform.hpp"
#include "Components/RenderLayer.hpp"
#include "Components/Collider.hpp"
#include "Components/HitBox.hpp"
#include "Components/Animator.hpp"
#include "Core/include/Console.hpp"
#include <memory>


class Player
{
public:
	Player(entt::registry& registry);
	~Player();

	entt::entity GetEntity() const;
	entt::entity GetHitBoxEntity() const;
	void Update(float dt);
	void CreatePlayer();

	void SpawnHitboxRight();
	void SpawnHitboxLeft();

	// Move player by a distance.
	// @param speed: Speed that the player moves by.
	void moveX(float const speed, float const dt);
private:

	entt::registry& m_registry;
	std::unique_ptr<Quad> m_player;
	std::unique_ptr<Quad> m_hitBoxDebug;

	float hitboxTimeActive = 0.0f;
	float hitBoxTime = 0.3f;
	bool canAttack = true;
	bool isMoving = false;
	Transform* transformPlayerComp = nullptr;
};
