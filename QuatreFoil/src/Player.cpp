#include "../QuatreFoil/include/Player.hpp"


Player::Player(entt::registry& registry) : m_registry(registry), m_player(std::make_unique<Quad>(registry)), m_hitBoxDebug(std::make_unique<Quad>(registry)) {}

Player::~Player() {  m_player.reset(); }

entt::entity Player::GetEntity() const
{
	return m_player->GetEntity();
}

void Player::CreatePlayer()
{
	m_player->SetTextureImagePath("../QuatreFoil/Assets/Textures/playerTemp.jpg");
	m_player->CreateQuad(glm::vec2(250, -680), glm::vec2(30, 40));
	m_registry.emplace<PlayerComp>(m_player->GetEntity());
	transformPlayerComp = &m_registry.get<Transform>(m_player->GetEntity());

	m_hitBoxDebug->SetTextureImagePath("../QuatreFoil/Assets/Textures/container.jpg");
	m_hitBoxDebug->CreateQuad(glm::vec2(250, -700), glm::vec2(80, 80));
}

void Player::moveX(float const speed, float const dt)
{
	// Move player on X axis
	transformPlayerComp->position += glm::vec2(speed * dt, 0.f);
}

auto& Player::GetTransformComp() const
{
	return m_registry.get<Transform>(m_player->GetEntity());
}

void Player::SpawnHitboxRight()
{
	if (canAttack)
	{
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		transformHitBoxComp.position = transformPlayerComp->position;
		canAttack = false;
		hitboxTimeActive = 0.f;
		std::cout << "Attack!\n";
	}
	else { std::cout << "Cant Attack!\n"; }
}

void Player::Update(float dt)
{
	if (hitboxTimeActive <= hitBoxTime)
	{
		hitboxTimeActive += dt;
	}
	else
	{
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		transformHitBoxComp.position = glm::vec2(250, -800);
		canAttack = true;

	}
}

