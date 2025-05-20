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

entt::entity Enemy::GetEntity() const
{
	return m_enemy->GetEntity();
}

void Enemy::CreateEnemy()
{
	m_enemy->SetTextureImagePath("../QuatreFoil/Assets/Textures/playerTemp.jpg");
	m_enemy->CreateQuad(glm::vec2(600, -680), glm::vec2(30, 40));
	m_registry.emplace<EnemyComp>(m_enemy->GetEntity());
	m_registry.emplace<RenderLayer>(m_enemy->GetEntity(), RenderLayer::Characters);
	transformEnemyComp = &m_registry.get<Transform>(m_enemy->GetEntity());

	//	m_hitBoxDebug->SetTextureImagePath("../QuatreFoil/Assets/Textures/container.jpg");
	//m_hitBoxDebug->CreateQuad(glm::vec2(250, -2000), glm::vec2(20, 50));
//	m_registry.emplace<RenderLayer>(m_hitBoxDebug->GetEntity(), RenderLayer::UI);
}

void Enemy::moveX(float const speed, float const dt)
{
	// Move enemy on X axis
	//transformEnemyComp->position += glm::vec2(speed * dt, 0.f);
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
		//playerPos = playerTransform.position;

		auto& enemyComp = m_registry.get<EnemyComp>(m_enemy->GetEntity());
		glm::vec2 direction = glm::normalize(playerTransform.position - transformEnemyComp->position);
		transformEnemyComp->position.x += enemyComp.speed * direction.x * dt;
	}

}

