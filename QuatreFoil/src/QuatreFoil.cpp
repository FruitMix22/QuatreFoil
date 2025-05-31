#include "../QuatreFoil/include/QuatreFoil.hpp"
#include <iostream>

QuatreFoil::QuatreFoil()
{
	// Make a camera object & framebuffer
	m_camera = std::make_unique<Camera>(m_registry);
	m_fbo = std::make_unique<Framebuffer>(1920, 1080, DEBUG_MODE);
	m_fbo->Bind(); 

	m_waveSystem = std::make_unique<EnemySpawner>(m_registry);
}

void QuatreFoil::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
}

void QuatreFoil::OnStart()
{
	currentGameState = GameState::Menu; 

	// Set inputs            //input    //function ran when pressed
	Input::RegisterCallBack(GLFW_KEY_D, [this] {m_playerNew->moveX(300.f, m_dt);});
	Input::RegisterCallBack(GLFW_KEY_A, [this] {m_playerNew->moveX(-300.f, m_dt);});
	Input::RegisterCallBack(GLFW_KEY_RIGHT, [this] {m_playerNew->SpawnHitboxRight();});
	Input::RegisterCallBack(GLFW_KEY_LEFT, [this] {m_playerNew->SpawnHitboxLeft();});
}

void QuatreFoil::StartGame()
{


	for (auto& quad : m_quads)
	{
		m_registry.destroy(quad.GetEntity());
	}
	m_quads.clear();

	if (m_waveSystem) 
	{
		m_waveSystem->KillAllEnemies();
		m_waveSystem->Reset();
	}

	if (m_playerNew && m_playerNew->GetEntity() != entt::null)
	{
		m_registry.destroy(m_playerNew->GetEntity()); 
	}

	m_playerNew = std::make_unique<Player>(m_registry);
	m_playerNew->CreatePlayer();

	#ifdef DEBUG_MODE
	m_playerNew->renderHitBox = true;
	#endif

	generateFloor();

	createBackground();

	currentGameState = GameState::GamePlay;
}

void QuatreFoil::OnUpdate()
{
	// If game is active
	if (currentGameState == GameState::GamePlay)
	{
		m_playerNew->Update(m_dt);
		auto& playerTransform = m_registry.get<Transform>(m_playerNew->GetEntity());
		m_camera->Setposition(glm::vec2(playerTransform.position.x + 625.f, 880.f));

		if (playerTransform.position.x <= -650) { playerTransform.position.x = -650; }
		if (playerTransform.position.x >= 1500) { playerTransform.position.x = 1500; }

		auto& playerAnimator = m_registry.get<Animator>(m_playerNew->GetEntity());
		auto& playerRenderable = m_registry.get<Renderable>(m_playerNew->GetEntity());

		playerRenderable.m_shader->SetUniform("uvOffset", playerAnimator.uvOffset);
		playerRenderable.m_shader->SetUniform("uvScale", playerAnimator.uvScale);

		auto& ememyview = m_registry.view<EnemyComp, Renderable, Animator>();
		for (auto& enemy : ememyview)
		{
			auto& enemyRenderable = m_registry.get<Renderable>(enemy);
			auto& enemyAnimator = m_registry.get<Animator>(enemy);
			enemyRenderable.m_shader->SetUniform("uvOffset", enemyAnimator.uvOffset);
			enemyRenderable.m_shader->SetUniform("uvScale", enemyAnimator.uvScale);
		}

		m_waveSystem->Update(m_dt);


		std::vector<entt::entity> hitEntities;
		std::vector<entt::entity> killedEntities;

		// HitBox collision
		auto hitboxView = m_registry.view<HitBox, Transform, Collider>();
		auto enemyView = m_registry.view<EnemyComp, Transform, Collider>();

		for (auto hitBoxEntity : hitboxView)
		{
			auto& hitBoxTransform = hitboxView.get<Transform>(hitBoxEntity);
			auto& hitBoxCollider = hitboxView.get<Collider>(hitBoxEntity);
			auto& hitBoxComp = hitboxView.get<HitBox>(hitBoxEntity);

			for (auto enemyEntity : enemyView)
			{
				auto& enemyTransform = enemyView.get<Transform>(enemyEntity);
				auto& enemyCollider = enemyView.get<Collider>(enemyEntity);

				bool xOverlap = std::abs(hitBoxTransform.position.x - enemyTransform.position.x) <= (hitBoxCollider.halfWidth + enemyCollider.halfWidth);

				if (xOverlap && !hitBoxComp.hasBeenHit(enemyEntity))
				{
					hitBoxComp.addHitEnemy(enemyEntity);

					auto& playerComp = m_registry.get<PlayerComp>(m_playerNew->GetEntity());
					auto& enemyComp = m_registry.get<EnemyComp>(enemyEntity);

					enemyComp.hit(playerComp.damage);
					Console::Log("Enemy Hit.");
				}

				if (auto* enemyComp = m_registry.try_get<EnemyComp>(enemyEntity))
				{
					if (enemyComp->health <= 0)
					{
						Console::Log("Enemy Died.");
						m_waveSystem->RemoveDeadEnemy(enemyEntity);
						m_registry.destroy(enemyEntity);
					}
				}
			}
		}

		auto playerEntity = m_playerNew->GetEntity();
		//auto& playerTransform = m_registry.get<Transform>(playerEntity);
		auto& playerCollider = m_registry.get<Collider>(playerEntity);
		auto& playerComp = m_registry.get<PlayerComp>(playerEntity);

		for (auto enemyEntity : enemyView)
		{
			auto& enemyTransform = enemyView.get<Transform>(enemyEntity);
			auto& enemyCollider = enemyView.get<Collider>(enemyEntity);
			auto& enemyComp = enemyView.get<EnemyComp>(enemyEntity);

			bool xOverlap = std::abs(playerTransform.position.x - enemyTransform.position.x) <= (playerCollider.halfWidth + enemyCollider.halfWidth);

			if (xOverlap && !playerComp.hasBeenHit)
			{
				playerComp.hit(enemyComp.damage);

				Console::Log("Player Hit!");
			}
		}

		if (playerComp.health <= 0)
		{
			Console::Log("Player Died!");
			currentGameState = GameState::Menu; // Reset to menu if player dies
		}



		// Update all uniforms for all renderables
		auto& view = m_registry.view<Renderable, Transform>();
		for (auto entity : view)
		{
			auto& renderable = view.get<Renderable>(entity);
			auto& transformable = view.get<Transform>(entity);

			renderable.m_shader->SetUniform("projection", m_camera->GetProjectionMatrix());
			renderable.m_shader->SetUniform("view", m_camera->GetViewMatrix());
			renderable.m_shader->SetUniform("model", transformable.GetModelMatrix());
		}
	}

} 

void QuatreFoil::OnRender()
{
	if(DEBUG_MODE){ m_fbo->Bind(); }

	// Run the renderer
	m_renderer.Render(m_registry);

	if(DEBUG_MODE) { m_fbo->Unbind(); }
}

void QuatreFoil::OnImGuiRender()
{
	if (currentGameState == GameState::Menu)
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoBackground;
		ImVec2 gameViewportSize = ImVec2(m_camera->GetPerspective().x, m_camera->GetPerspective().y);
		ImGui::SetNextWindowPos(ImVec2(0, 0)); 
		ImGui::SetNextWindowSize(gameViewportSize, ImGuiCond_Always);
		ImGui::SetNextWindowSizeConstraints(gameViewportSize, gameViewportSize);
		ImGui::Begin("Background", nullptr, flags);
		ImGui::Image(menuBackground->GetID(), ImVec2(1920, 1080));
		ImGui::End();
		 

		// Set the size for the game viewport window
		ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));
		// Set window size constraints before beginning the window
		ImGui::SetNextWindowSize(gameViewportSize, ImGuiCond_Always);
		ImGui::SetNextWindowSizeConstraints(gameViewportSize, gameViewportSize);

		
		ImGui::SetNextWindowPos(ImVec2(800, 480));
		ImGui::SetNextWindowFocus();
		ImGui::Begin("Menu", nullptr, flags);
		if (ImGui::Button("Start Game", ImVec2(200, 50))) { StartGame(); }
		if (ImGui::Button("Quit Game", ImVec2(200, 50))) { m_terminate = true; }
		ImGui::End();
		ImGui::PopStyleColor();
	
	}
	// If game is active
	if (currentGameState == GameState::GamePlay)
	{
		auto& playerComp = m_registry.get<PlayerComp>(m_playerNew->GetEntity());
		if (!DEBUG_MODE)
		{
			ImGui::SetNextWindowPos(ImVec2(10, 10)); 
			ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0, 0, 0, 0));
			ImGui::Begin("Stats Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
			ImGui::Text("health: %.0f", playerComp.health);
			ImGui::Text("Enemies Remaining: %.0f", (float)m_waveSystem->GetNumberOfEnemiesActive());
			ImGui::Text("Current Wave: %.0f", (float)m_waveSystem->GetCurrentWave() - 1);
			ImGui::End();
			ImGui::PopStyleColor();
		}
		else // Only render engine gui if in Debug build
		{
			// Make the whole window a dock space
			ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);

			// Build dock space for the window 
			if (!dockspace_built) { generateDockSpace(); }

			// Set the size for the game viewport window
			ImVec2 gameViewportSize = ImVec2(m_camera->GetPerspective().x, m_camera->GetPerspective().y);

			// Set window size constraints before beginning the window
			ImGui::SetNextWindowSize(gameViewportSize, ImGuiCond_Always);
			ImGui::SetNextWindowSizeConstraints(gameViewportSize, gameViewportSize);

			/***************************
			*		Game view          *
			***************************/

			// Create a viewport window
			ImGui::Begin("Viewport");
			ImGui::Image(static_cast<intptr_t>(m_fbo->GetTextureID()), ImVec2(gameViewportSize.x / 1.4, gameViewportSize.y / 1.4), ImVec2(0, 1), ImVec2(1, 0)); // Image from the frame buffer (game view)
			ImVec2 viewPortPos = ImGui::GetWindowPos();
			ImGui::End();

			ImVec2 floatingPos = ImVec2(viewPortPos.x + 20, viewPortPos.y + 30);
			ImGui::SetNextWindowPos(floatingPos, ImGuiCond_Always);
			// Begin the floating window
			ImGui::Begin("Floating Stats Window", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
			ImGui::SetWindowFontScale(2.f);
			ImGui::Text("health: %.0f", playerComp.health);
			ImGui::Text("Enemies Remaining: %.0f", (float)m_waveSystem->GetNumberOfEnemiesActive());
			ImGui::Text("Current Wave: %.0f", (float)m_waveSystem->GetCurrentWave() - 1);
			ImGui::SetWindowFontScale(1.0f);

			ImGui::End();
			/***************************
			*		Bottom Bar         *
			***************************/

			int entityCount = 0;
			auto& view = m_registry.view<Transform>();

			for (auto entity : view)
			{
				entityCount++;
			}
			ImGui::Begin("Bottom Bar");
			ImGui::Text("Current number of entities: %d", entityCount); // Number of entities being rendered

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
			if (ImGui::Button("Close ", ImVec2(200.f, 30.f))) { m_terminate = true; } // Button to close the program
			ImGui::PopStyleColor(1);

			ImGui::Text("Time in between frames: %f", m_dt); // Delta time text

			ImGui::Text("FPS: %f", GetFPS()); // FPS text

			ImGui::End();

			/***************************
			*		Right Bar          *
			***************************/

			static int selectedItem = 0; // the currently selected entity

			m_entityNames.clear(); // clear the list to make sure it doesnt buffer from previous frames
			m_items.clear(); // Same for the items...

			// for every entiy in the quad, add to a list of the number of the entity
			for (int i = 0; i < m_quads.size(); i++)
			{
				// Raw pointers go boom so this needs to be here
				m_entityNames.push_back(std::to_string(i));
				m_items.push_back(m_entityNames.back().c_str());
			}

			ImGui::Begin("Right Panel");
		
			ImGui::Combo("Selected entity", &selectedItem, m_items.data(), static_cast<int>(m_items.size())); // Currently selected entity
			auto& transform = m_registry.get<Transform>(m_quads[selectedItem].GetEntity()); // Start editing the transform of the current selected entity
			ImGui::SliderFloat("X pos", &transform.position.x, -100.0f, 1000.f);
			ImGui::SliderFloat("Y pos", &transform.position.y, -800.0f, 1000.f);

			if (ImGui::Button("Spawn new entity", ImVec2(200.f, 30.f)))
			{
				spawnNewEntity(); // Spawn a new entity
				selectedItem = m_quads.size() - 1; // set current item to new one (ease of use)}
			}

			auto& transformPlayerComp = m_registry.get<Transform>(m_playerNew->GetEntity());
			if (ImGui::SliderFloat("Player X Pos", &transformPlayerComp.position.x, -200.f, 1000.f)); // Player x Pos slider

			ImGui::Text("Camera X Pos: %.2f", m_camera->GetPosition().x); // camera x Pos 

			if (ImGui::Button("Kill all Enemies.")) { m_waveSystem->KillAllEnemies(); }

			ImGui::End();

			/***************************
			*     Bottom Right Bar     *
			***************************/

			ImGui::Begin("Console");

			// Optionally clear
			if (ImGui::Button("Clear")) Console::Clear();

			// Get log lines
			const auto& logs = Console::GetLogs();

			// Check if the user is at the bottom before adding text
			ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(200, 200, 200, 255)); // dark gray
			ImGui::BeginChild("ConsoleScrollRegion", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
			bool shouldScroll = ImGui::GetScrollY() >= ImGui::GetScrollMaxY();

			for (const auto& line : logs) ImGui::TextWrapped("%s", line.c_str());

			if (shouldScroll) ImGui::SetScrollHereY(1.0f);

			ImGui::EndChild();
			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

void QuatreFoil::generateFloor()
{
	// temp number of floors
	size_t totalTiles = 30;
	float xPositionTile = -1250.f;

	for (int i = 0; i < totalTiles; i++)
	{
		m_quads.emplace_back(m_registry);
		m_quads.back().SetTextureImagePath("Textures/mcGrass.jpg");
		m_quads.back().CreateQuad(glm::vec2(xPositionTile, -800), glm::vec2(60, 80));
		m_registry.emplace<RenderLayer>(m_quads.back().GetEntity(), RenderLayer::MidGround);
		xPositionTile += 120.f;
	}
}

void QuatreFoil::generateDockSpace()
{
	// Ill be honest i have no idea how dock builder works, the documentation
	// on it is hard to find.

	// Dont run it again
	dockspace_built = true;

	// Set nodes for dock spaces

	ImGuiID dockspace_id = ImGui::GetMainViewport()->ID;
	ImGui::DockBuilderRemoveNode(dockspace_id);
	ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

	ImGuiID dock_main_id = dockspace_id;
	ImGuiID right;
	ImGuiID bottom;
	ImGuiID bottom_right;

	// Split off the bottom bar
	bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.19f, nullptr, &dock_main_id);
	// Split off the right sidebar
	right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.3f, nullptr, &dock_main_id);
	// Split bottom again to get bottom-right
	bottom_right = ImGui::DockBuilderSplitNode(bottom, ImGuiDir_Right, 0.5f, nullptr, &bottom);

	// Dock windows
	ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
	ImGui::DockBuilderDockWindow("Bottom Bar", bottom);
	ImGui::DockBuilderDockWindow("Right Panel", right);
	ImGui::DockBuilderDockWindow("Console", bottom_right);

	// Done
	ImGui::DockBuilderFinish(dockspace_id);
}

void QuatreFoil::spawnNewEntity()
{
	m_quads.emplace_back(m_registry);
	m_quads.back().CreateQuad(glm::vec2(250, -400), glm::vec2(60, 80));
	m_registry.emplace<RenderLayer>(m_quads.back().GetEntity(), RenderLayer::Characters);
}

void QuatreFoil::createBackground()
{
	Quad background(m_registry);
	background.SetTextureImagePath("Textures/tempBackground.jpg");
	background.CreateQuad(glm::vec2(200.f, -350.0f), glm::vec2(2000, 600));
	m_registry.emplace<RenderLayer>(background.GetEntity(), RenderLayer::Background);
}

float QuatreFoil::GetFPS()
{
	fpsTimeAccumulate += m_dt;
	if (fpsTimeAccumulate >= 1.0f)
	{
		// Change FPS and reset timer
		m_fps = 1.0f / m_dt;
		fpsTimeAccumulate = 0.0f;
	}
	return m_fps;
}





