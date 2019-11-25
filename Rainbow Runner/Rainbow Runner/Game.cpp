#include "Game.h"
#include "Sprite.h"
#include "BackEnd.h"
#include "PhysicsSystem.h"

#include <random>


Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{	
	//Create different scenes
	std::string menuName = "Main Menu";
	std::string ruleName = "Rules";
	std::string exitName = "Exit";
	std::string spaceName = "Space";
	std::string rulesSecName = "Rules";

	//Initialize the current scene (starting screen)
	m_name = menuName;
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Load the different scenes into a list
	m_scenes.push_back(new RainbowRunner(menuName));
	m_scenes.push_back(new RulesScene(ruleName));
	m_scenes.push_back(new ExitScene(exitName));
	m_scenes.push_back(new RainbowRunnerGame(spaceName));
	m_scenes.push_back(new RulesSection(rulesSecName));

	//Access the starting scene
	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];	

	PhysicsSystem::Init();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	PhysicsSystem::Update(m_register);

#pragma region Scrolling Background
	//Scrolls the background for the game IF the active scene is the game scene
	if (m_activeScene == m_scenes[3])
	{		
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;

		//Background Scrolling
		auto entity = scene->GetBackground();
		auto entity2 = scene->GetBackground2();
		vec3 position = m_register->get<Transform>(entity).GetPosition();
		vec3 position2 = m_register->get<Transform>(entity2).GetPosition();
		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float bgSpeed = 100.f;
		float platSpeed = 70.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		if (start)
		{
			m_register->get<Transform>(entity).SetPositionX(position.x - (bgSpeed * Timer::deltaTime));
			m_register->get<Transform>(entity2).SetPositionX(position2.x - (bgSpeed * Timer::deltaTime));
		}
		///////////////////////////////////////////////////////////////////////////////////////
		//Platforms Moving (put into one if after!!!)
		auto p1 = scene->GetPlatform1();
		auto p2 = scene->GetPlatform2();
		auto p3 = scene->GetPlatform3();
		auto p4 = scene->GetPlatform4();
		auto p5 = scene->GetPlatform5();
		auto p6 = scene->GetPlatform6();
		auto p7 = scene->GetPlatform7();

		if (start)
		{
			m_register->get<Transform>(p1).SetPositionX(m_register->get<Transform>(p1).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p2).SetPositionX(m_register->get<Transform>(p2).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p3).SetPositionX(m_register->get<Transform>(p3).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p4).SetPositionX(m_register->get<Transform>(p4).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p5).SetPositionX(m_register->get<Transform>(p5).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p6).SetPositionX(m_register->get<Transform>(p6).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p7).SetPositionX(m_register->get<Transform>(p7).GetPosition().x - (platSpeed * Timer::deltaTime));
		}
	}
#pragma endregion

}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	//Just calls all the other input functions 
	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::KeyboardHold()
{
	int windowWidth = BackEnd::GetWindowWidth();

	//Movement of the sprite
#pragma region Movement
	if (m_activeScene == m_scenes[3])
	{
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
		auto entity = scene->GetPlayer();
		vec3 position = m_register->get<Transform>(entity).GetPosition();

		float speed = 60.f;

		if (Input::GetKey(Key::D))
		{
			m_register->get<Transform>(entity).SetPositionX(position.x + (speed * Timer::deltaTime));
		}
		else if (Input::GetKey(Key::A))
		{
			m_register->get<Transform>(entity).SetPositionX(position.x - (speed * Timer::deltaTime));
		}			
	}
#pragma endregion
	
}

void Game::KeyboardDown()
{
	//Keyboard button down	
#pragma region Screen Manipulation Functionality
	//Switches from Main Menu to Game Screen
	if (m_activeScene == m_scenes[0] && Input::GetKeyDown(Key::DownArrow))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rules";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[1]->GetScene();
		m_activeScene = m_scenes[1];
	}
	//Switches to the game scene
	else if (m_activeScene == m_scenes[0] && Input::GetKeyDown(Key::Space))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rainbow Runner";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];
	}
	//Swtiches back IF active scene is game screen to Main Menu
	else if (m_activeScene == m_scenes[1] && Input::GetKeyDown(Key::UpArrow))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Main Menu";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];
	}
	//Switches from rules to exit button
	else if (m_activeScene == m_scenes[1] && Input::GetKeyDown(Key::DownArrow))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Exit";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[2]->GetScene();
		m_activeScene = m_scenes[2];
	}
	//Switches to the rules section
	else if (m_activeScene == m_scenes[1] && Input::GetKeyDown(Key::Space))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rules";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[4]->GetScene();
		m_activeScene = m_scenes[4];
	}
	//Swithces from exit to rules button
	else if (m_activeScene == m_scenes[2] && Input::GetKeyDown(Key::UpArrow))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rules";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[1]->GetScene();
		m_activeScene = m_scenes[1];
	}
	//Exits the program
	else if (m_activeScene == m_scenes[2] && Input::GetKeyDown(Key::Space))
	{
		exit(1);
	}
	//Returns to the main menu from the rules section
	else if (m_activeScene == m_scenes[4] && Input::GetKeyDown(Key::Backspace))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Main Menu";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];
	}
#pragma endregion

#pragma region Jumping Code
if (m_activeScene == m_scenes[3])
	{
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
		auto entity = scene->GetPlayer();
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		auto& body = ECS::GetComponent<PhysicsBody>(entity);

		vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

		//Sets upwards vel + accel to make the sprite "jump"
		//Changes the corresponding animation
		if (Input::GetKeyDown(Key::W) && !jump)
		{	
			body.SetAcceleration(vec3(0.f, 85.f, 0.f));
			body.SetVelocity(vec3(0.f, 85.f, 0.f));
			jump = true;
			animController.SetActiveAnim(1);
			animController.GetAnimation(1).Reset();
		}

		//Checks to see if the player can jump again and changes animation
		//Eliminates double jumping
		if (body.GetAcceleration().y == 0.f && body.GetVelocity().y == 0.f)
		{
			jump = false;
			animController.SetActiveAnim(0);
		}
	}
#pragma endregion

	if (m_activeScene == m_scenes[3])
	{
		if (Input::GetKeyDown(Key::Enter))
		{
			start = true;
		}
	}
	//Exits fullscreen :)
	if (Input::GetKeyDown(Key::E))
	{
		exit(1);
	}

}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::P))
	{
		PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
	}

	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
