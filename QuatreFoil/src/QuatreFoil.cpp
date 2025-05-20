#include "../QuatreFoil/include/QuatreFoil.hpp"
#include <iostream>

QuatreFoil::QuatreFoil()
{
	// Make a camera object & framebuffer
	m_camera = std::make_unique<Camera>(m_registry);
	m_fbo = std::make_unique<Framebuffer>(1000, 800);
}

void QuatreFoil::OnAttach()
{
	std::cout << "Attaching Game to Engine...\n";
}

void QuatreFoil::OnStart()
{
	// Spawn Temp floor & Player & background
	generateFloor();
	m_playerNew->CreatePlayer();
	m_enemy->CreateEnemy();
	createBackground();
	// TODO: Change when adding more meshes

	// Set inputs            //input    //function ran when pressed
	Input::RegisterCallBack(GLFW_KEY_D, [this] {m_playerNew->moveX(100.f, m_dt);});
	Input::RegisterCallBack(GLFW_KEY_A, [this] {m_playerNew->moveX(-100.f, m_dt);});
	Input::RegisterCallBack(GLFW_KEY_RIGHT, [this] {m_playerNew->SpawnHitboxRight();});
	Input::RegisterCallBack(GLFW_KEY_LEFT, [this] {m_playerNew->SpawnHitboxLeft();});
}

void QuatreFoil::OnUpdate()
{
	auto& playerTransform = m_registry.get<Transform>(m_playerNew->GetEntity());
	m_camera->Setposition(glm::vec2(playerTransform.position.x -250.f, 0.f));

	if (playerTransform.position.x <= -1000) { playerTransform.position.x = -1000; }
	if (playerTransform.position.x >=  1800) { playerTransform.position.x =  1800; }

	m_playerNew->Update(m_dt);
	m_enemy->Update(m_dt);

	// Update all uniforms for all renderables
	auto view = m_registry.view<Renderable, Transform>();
	for (auto entity : view)
	{
		auto& renderable = view.get<Renderable>(entity);
		auto& transformable = view.get<Transform>(entity);

		renderable.m_shader->SetUniform("projection", m_camera->GetProjectionMatrix());
		renderable.m_shader->SetUniform("view", m_camera->GetViewMatrix());
		renderable.m_shader->SetUniform("model", transformable.GetModelMatrix());
	}
} 

void QuatreFoil::OnRender()
{
	m_fbo->Bind(); // (Not strictly neccesary right now as there are no other FBO's, but will be neccesary in the future with my FBO's.

	// Clear all
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Run the renderer
	m_renderer.Render(m_registry);

	m_fbo->Unbind();
}

void QuatreFoil::OnImGuiRender()
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
	ImGui::Image(static_cast<intptr_t>(m_fbo->GetTextureID()), gameViewportSize, ImVec2(0, 1), ImVec2(1, 0)); // Image from the frame buffer (game view)
	ImGui::End();


	/***************************
	*		Bottom Bar         *
	***************************/

	ImGui::Begin("Bottom Bar");
	ImGui::Text("Current number of entities: %d", m_quads.size()); // Number of entities being rendered

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	if (ImGui::Button("Close ", ImVec2(200.f, 30.f))) { m_terminate = true; } // Button to close the program
	ImGui::PopStyleColor(1);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
	if (ImGui::Button("Play ", ImVec2(200.f, 30.f))) { m_currentMode = EngineMode::Gameplay; } // Start gameplay
	ImGui::PopStyleColor(1);

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
	if (ImGui::Button("Stop ", ImVec2(200.f, 30.f))) { m_currentMode = EngineMode::Editor; } // End gameplay
	ImGui::PopStyleColor(1);

	if (m_currentMode == EngineMode::Editor) { ImGui::TextColored(ImVec4(0.0f, 0.0f, 1.0f, 1.0f), "Editing Mode."); }
	else { ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "GamePlay Mode."); } // Mode text

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

	ImGui::Text("Camera X Pos: %.2f" ,m_camera->GetPosition().x); // camera x Pos slider

	ImGui::End();
}

void QuatreFoil::generateFloor()
{
	// temp number of floors
	size_t totalTiles = 30;
	float xPositionTile = -1250.f;

	for (int i = 0; i < totalTiles; i++)
	{
		m_quads.emplace_back(m_registry);
		m_quads.back().SetTextureImagePath("../QuatreFoil//Assets/Textures/mcGrass.jpg");
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
	ImGui::DockBuilderRemoveNode(dockspace_id); // clear any existing layout
	ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
	ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

	// Split the workspace into areas
	ImGuiID dock_main_id = dockspace_id;
	ImGuiID right;
	ImGuiID bottom;

	// Split off the bottom bar
	bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.25f, nullptr, &dock_main_id);
	// Split off the right sidebar
	right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.3f, nullptr, &dock_main_id);

	// Dock windows into regions by name
	ImGui::DockBuilderDockWindow("Viewport", dock_main_id);
	ImGui::DockBuilderDockWindow("Bottom Bar", bottom);
	ImGui::DockBuilderDockWindow("Right Panel", right);

	// Done
	ImGui::DockBuilderFinish(dockspace_id);
}

void QuatreFoil::spawnNewEntity()
{
	m_quads.emplace_back(m_registry);
	m_quads.back().CreateQuad(glm::vec2(250, -400), glm::vec2(60, 80));
}

void QuatreFoil::createBackground()
{
	Quad background(m_registry);
	background.SetTextureImagePath("../QuatreFoil/Assets/Textures/tempBackground.jpg");
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





