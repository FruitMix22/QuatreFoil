#include "../QuatreFoil/include/Player.hpp"


Player::Player(entt::registry& registry) : m_registry(registry), m_entity(std::make_unique<Quad>(registry)) {}

Player::~Player() {  m_entity.reset(); }

entt::entity Player::GetEntity() const
{
	return m_entity->GetEntity();
}

void Player::CreatePlayer()
{
	m_entity->SetTextureImagePath("../QuatreFoil/Assets/Textures/playerTemp.jpg");
	m_entity->CreateQuad(glm::vec2(250, -680), glm::vec2(30, 40));
	m_registry.emplace<PlayerComp>(m_entity->GetEntity());
}

void Player::moveX(float const speed, float const dt)
{
	// Move player on X axis
	auto& transformPlayerComp = m_registry.get<Transform>(m_entity->GetEntity());
	transformPlayerComp.position += glm::vec2(speed * dt, 0.f);
}

auto& Player::GetTransformComp() const
{
	return m_registry.get<Transform>(m_entity->GetEntity());
}
