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
	m_registry.emplace<Collider>(m_player->GetEntity(), 20.f);
	transformPlayerComp = &m_registry.get<Transform>(m_player->GetEntity());

	// Create hit box
	m_hitBoxDebug->CreateQuad(glm::vec2(4000, -2000), glm::vec2(20, 50));
	if (m_registry.all_of<Renderable>(m_hitBoxDebug->GetEntity()) && !renderHitBox) 
	{
		m_registry.remove<Renderable>(m_hitBoxDebug->GetEntity());
	} 
	//m_hitBoxDebug->GetEntity()
	m_registry.emplace<RenderLayer>(m_hitBoxDebug->GetEntity(), RenderLayer::UI);
	m_registry.emplace<HitBox>(m_hitBoxDebug->GetEntity());
	m_registry.emplace<Collider>(m_hitBoxDebug->GetEntity(), 10.f);

	auto& playerRenderComp = m_registry.get<Renderable>(m_player->GetEntity());
	playerRenderComp.m_shader->SetUniform("colour", glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void Player::moveX(float const speed, float const dt)
{
	if (canAttack)
	{
		// Move player on X axis
		transformPlayerComp->position += glm::vec2(speed * dt, 0.f);
		auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
		animatorComp.setAnimState(Animator::animState::Running);
		// Flip player if moving left or right
		if (speed < 0) { transformPlayerComp->scale = glm::vec2(-60, 60); }
		else { transformPlayerComp->scale = glm::vec2(60, 60); }
	}
	else
	{
		// Move player on X axis
		transformPlayerComp->position += glm::vec2((speed / 2) * dt, 0.f);
	}


	// Set running
	isMoving = true;
}
 
bool Player::doesMatchCombo(const std::vector<AttackType>& combo)
{
	if (attackHistory.size() < combo.size()) return false;

	// Compare from the end of attackHistory
	for (int i = 0; i < combo.size(); ++i) {
		if (attackHistory[attackHistory.size() - combo.size() + i] != combo[i]) {
			return false;
		}
	}

	return true;
}

void Player::SpawnHitboxRight()
{
	if (canAttack)
	{
		// Atack stream
		attackHistory.push_back(AttackType::Right);

		if (doesMatchCombo(SideSlashRight))
		{
			attackHistory.clear();
			auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
			auto& animationComp = m_registry.get<Animator>(m_player->GetEntity());
			auto& playerComp = m_registry.get<PlayerComp>(m_player->GetEntity());
			animationComp.setAnimState(Animator::animState::AttackSlash);
			//Make it do more damage
			playerComp.damage = 100;
			transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(30.f, -10.0f);
			transformPlayerComp->scale = glm::vec2(60, 60);
			canAttack = false;
			hitboxTimeActive = 0.f;
			Console::Log("Player did COMBBOOOO.");
		}
		else
		{
			auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
			auto& animationComp = m_registry.get<Animator>(m_player->GetEntity());
			animationComp.setAnimState(Animator::animState::Attacking);
			transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(30.f, -10.0f);
			transformPlayerComp->scale = glm::vec2(60, 60);
			canAttack = false;
			hitboxTimeActive = 0.f;
			Console::Log("Player Attacked.");
		}
	}
}

void Player::SpawnHitboxLeft()
{
	// Atack stream
	attackHistory.push_back(AttackType::Left);

	if (doesMatchCombo(SideSlashLeft))
	{
		attackHistory.clear();
		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		auto& animationComp = m_registry.get<Animator>(m_player->GetEntity());
		auto& playerComp = m_registry.get<PlayerComp>(m_player->GetEntity());
		animationComp.setAnimState(Animator::animState::AttackSlash);
		//Make it do more damage
		playerComp.damage = 100;
		transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(-40.f, -10.0f);
		transformPlayerComp->scale = glm::vec2(-60, 60);
		canAttack = false;
		hitboxTimeActive = 0.f;
		Console::Log("Player did COMBBOOOO.");
	}
	if (canAttack)
	{
		// Attack stream
		attackHistory.push_back(AttackType::Left);

		auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
		auto& animationComp = m_registry.get<Animator>(m_player->GetEntity());
		animationComp.setAnimState(Animator::animState::Attacking);
		transformHitBoxComp.position = transformPlayerComp->position + glm::vec2(-40.f, -10.0f);
		transformPlayerComp->scale = glm::vec2(-60, 60);
		canAttack = false;
		hitboxTimeActive = 0.f;
		Console::Log("Player Attacked.");
	}
}

void Player::Update(float dt)
{
	if (!isMoving && canAttack)
	{
		auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
		animatorComp.setAnimState(Animator::animState::Idle);
	}

	auto& animatorComp = m_registry.get<Animator>(m_player->GetEntity());
	animatorComp.Update(dt);

	auto& playerRenderComp = m_registry.get<Renderable>(m_player->GetEntity());

	// Damage frames
	if (auto* playerComp = m_registry.try_get<PlayerComp>(m_player->GetEntity()))
	{
		if (playerComp->hasBeenHit)
		{
			timeAccumulated += dt;

			playerRenderComp.m_shader->SetUniform("colour", glm::vec4(1.f, 0.f, 0.f, 1.f));
		}
		if (timeAccumulated >= 0.8f)
		{
			playerComp->hasBeenHit = false;
			playerRenderComp.m_shader->SetUniform("colour", glm::vec4(1.f, 1.f, 1.f, 1.f));
			timeAccumulated = 0.f;
		}

		isMoving = false; // Reset for next frame

		if (hitboxTimeActive <= hitBoxTime)
		{
			hitboxTimeActive += dt;
		}
		else
		{
			auto& transformHitBoxComp = m_registry.get<Transform>(m_hitBoxDebug->GetEntity());
			auto& hitBoxComp = m_registry.get<HitBox>(m_hitBoxDebug->GetEntity());
			auto& playerComp = m_registry.get<PlayerComp>(m_player->GetEntity());
			playerComp.damage = 20;
			transformHitBoxComp.position = glm::vec2(4000, -2000);
			hitBoxComp.resetHitEnemies();
			canAttack = true;
		}
	}
}

