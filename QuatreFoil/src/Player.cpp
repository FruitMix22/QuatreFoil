#include "../QuatreFoil/include/Player.hpp"


Player::Player(entt::registry& registry) : m_registry(registry), m_player(std::make_unique<Quad>(registry)), m_hitBoxDebug(std::make_unique<Quad>(registry)) {}

Player::~Player() {  m_player.reset(); }

entt::entity Player::GetEntity() const
{
	return m_player->GetEntity();
}

entt::entity Player::GetHitBoxEntity() const
{
	return m_hitBoxDebug->GetEntity();
}

void Player::CreatePlayer()
{
	m_player->SetTextureImagePath("../QuatreFoil/Assets/Textures/warriorSpriteSheet.png");
	m_player->SetVertexPath("../QuatreFoil/Assets/Shaders/playerVert.glsl");
	m_player->SetFragPath("../QuatreFoil/Assets/Shaders/playerFrag.glsl");
	m_player->CreateQuad(glm::vec2(250, -660), glm::vec2(60, 60));
	m_registry.emplace<PlayerComp>(m_player->GetEntity());
	m_registry.emplace<RenderLayer>(m_player->GetEntity(), RenderLayer::Characters);
	m_registry.emplace<Animator>(m_player->GetEntity(), glm::vec2(414.f,748.f), glm::vec2(69.f, 44.f));
	transformPlayerComp = &m_registry.get<Transform>(m_player->GetEntity());

	// Create hit box
	m_hitBoxDebug->CreateQuad(glm::vec2(4000, -2000), glm::vec2(20, 50));
	m_registry.emplace<RenderLayer>(m_hitBoxDebug->GetEntity(), RenderLayer::UI);
	m_registry.emplace<HitBox>(m_hitBoxDebug->GetEntity());
	m_registry.emplace<Collider>(m_hitBoxDebug->GetEntity(), 10.f);
}

void Player::moveX(float const speed, float const dt)
{
	// Move player on X axis
	transformPlayerComp->position += glm::vec2(speed * dt, 0.f);

	// Flip player if moving left or right
	if (speed < 0) { transformPlayerComp->scale = glm::vec2(-60, 60); }
	else { transformPlayerComp->scale = glm::vec2(60, 60);  }

	// Set running
	isMoving = true;
	auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
	animatorComp.setAnimState(Animator::animState::Running);
}
 
void Player::SpawnHitboxRight()
{
	if (canAttack)
	{
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(20.f,-10.0f);
		canAttack = false;
		hitboxTimeActive = 0.f;
		Console::Log("Player Attacked.");
	}
}

void Player::SpawnHitboxLeft()
{
	if (canAttack)
	{
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(-40.f, -10.0f);
		canAttack = false;
		hitboxTimeActive = 0.f;
		Console::Log("Player Attacked.");
	}
}

void Player::Update(float dt)
{
	if (!isMoving)
	{
		auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
		animatorComp.setAnimState(Animator::animState::Idle);
	}


	auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
	animatorComp.Update(dt);

	isMoving = false; // Reset for next frame

	if (hitboxTimeActive <= hitBoxTime)
	{
		hitboxTimeActive += dt;
	}
	else
	{
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		transformHitBoxComp.position = glm::vec2(4000, -2000);
		canAttack = true;
	}
}

