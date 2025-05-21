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
		m_enemy->SetTextureImagePath("../QuatreFoil/Assets/Textures/playerTemp.jpg");
		m_enemy->CreateQuad(glm::vec2(posX, -680), glm::vec2(30, 40));
		m_registry.emplace<EnemyComp>(m_enemy->GetEntity());
		m_registry.emplace<RenderLayer>(m_enemy->GetEntity(), RenderLayer::Characters);
		transformEnemyComp = &m_registry.get<Transform>(m_enemy->GetEntity());
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
	auto& view = m_registry.view<PlayerComp, Transform>();
	for (auto entity : view)
	{
		auto& playerTransform = view.get<Transform>(entity);

		if (auto* enemyComp = m_registry.try_get<EnemyComp>(m_enemy->GetEntity()))
		{
			glm::vec2 direction = glm::normalize(playerTransform.position - transformEnemyComp->position);
			transformEnemyComp->position.x += enemyComp->speed * direction.x * dt;
		}
	}

}


