#include "../QuatreFoil/include/enemy.hpp"


Enemy::Enemy(entt::registry& registry) : m_registry(registry), m_enemy(std::make_unique<Quad>(registry)), m_hitBoxDebug(std::make_unique<Quad>(registry)) 
{
	auto& view = m_registry.view<PlayerComp, Transform>();
	for (auto entity : view)
	{
		auto& playerTransform = view.get<Transform>(entity);
		playerPos = playerTransform.position;
	}
}

Enemy::~Enemy() { m_enemy.reset(); }


void Enemy::CreateEnemy(float posX)
{
	{
		m_enemy->SetTextureImagePath("../QuatreFoil/Assets/Textures/enemySlime.png");
		m_enemy->SetVertexPath("../QuatreFoil/Assets/Shaders/playerVert.glsl");
		m_enemy->SetFragPath("../QuatreFoil/Assets/Shaders/playerFrag.glsl");
		m_enemy->CreateQuad(glm::vec2(posX, -680), glm::vec2(30, 40));
		m_registry.emplace<EnemyComp>(m_enemy->GetEntity());
		m_registry.emplace<RenderLayer>(m_enemy->GetEntity(), RenderLayer::Characters);
		m_registry.emplace<Collider>(m_enemy->GetEntity(), 20.f);
		m_registry.emplace<Animator>(m_enemy->GetEntity(), glm::vec2(176.f,32.f), glm::vec2(16.f,32.f));
		auto& enemyAnim = m_registry.get<Animator>(m_enemy->GetEntity());
		enemyAnim.endIdle = 6;
	}
}

entt::entity Enemy::GetEntity() const
{
	return m_enemy->GetEntity();
}

auto& Enemy::GetTransformComp() const
{
	return m_registry.get<Transform>(m_enemy->GetEntity());
}

void Enemy::SpawnHitboxRight()
{

}

void Enemy::SpawnHitboxLeft()
{

}

void Enemy::Update(float dt)
{
	auto& enemyAnim = m_registry.get<Animator>(m_enemy->GetEntity());
	enemyAnim.setAnimState(Animator::animState::Idle);
	enemyAnim.Update(dt);

	auto& view = m_registry.view<PlayerComp, Transform>();
	for (auto entity : view)
	{
		auto& playerTransform = view.get<Transform>(entity);
		auto& transformEnemyComp = m_registry.get<Transform>(m_enemy->GetEntity());
		if (auto* enemyComp = m_registry.try_get<EnemyComp>(m_enemy->GetEntity()))
		{
			if (enemyComp->hasBeenHit)
			{
				timeAccumulated += dt;
			}
			if (timeAccumulated >= 0.8f)
			{
				enemyComp->hasBeenHit = false;
			}
			glm::vec2 direction = glm::normalize(playerTransform.position - transformEnemyComp.position);
			transformEnemyComp.position.x += enemyComp->speed * direction.x * dt;
			if (direction.x >= 0)
			{
				transformEnemyComp.scale = glm::vec2(30,40);
			}
			else
			{

				transformEnemyComp.scale = glm::vec2(-30,40);
			}
		}
	}

}



