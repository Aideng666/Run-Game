#include "Game.h"
#include "Sprite.h"

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
	std::string MainMenuName = "Main Menu";
	vec4 mainMenuClear = vec4(0.15f, 0.33f, 0.58f, 1.f);
	std::string GameName = "Rainbow Runner";
	vec4 gameClear = vec4(0.15f, 0.33f, 0.58f, 1.f);
	//std::string RulesName = "Rules";
	//vec4 rulesClear = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initialize the current scene (starting screen)
	m_name = MainMenuName;
	m_clearColor = mainMenuClear;

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Load the different scenes into a list
	m_scenes.push_back(new RainbowRunner(MainMenuName));
	//m_scenes.push_back(new RulesScene(RulesName));
	m_scenes.push_back(new RainbowRunnerGame(GameName));

	//Access the starting scene
	m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
	m_register = m_scenes[0]->GetScene();
	m_activeScene = m_scenes[0];
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

	//Scrolls the background for the game IF the active scene is the game scene
	if (m_activeScene == m_scenes[1])
	{
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;

		auto entity = scene->GetBackground();
		auto entity2 = scene->GetBackground2();
		vec3 position = m_register->get<Transform>(entity).GetPosition();
		vec3 position2 = m_register->get<Transform>(entity2).GetPosition();

		int bgWidth = m_register->get<Sprite>(entity).GetWidth();

		float speed = 50.f;

		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

		m_register->get<Transform>(entity).SetPositionX(position.x - (speed * Timer::deltaTime));
		m_register->get<Transform>(entity2).SetPositionX(position2.x - (speed * Timer::deltaTime));
	}
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
	//Keyboard button held
}

void Game::KeyboardDown()
{
	//Keyboard button down	
	//Switches from Main Menu to Game Screen
	if (m_activeScene == m_scenes[0] && Input::GetKeyDown(Key::Space))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rainbow Runner";
		m_clearColor = vec4(0.28f, 0.59f, 0.28f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[1]->GetScene();
		m_activeScene = m_scenes[1];
	}
	//Swtiches back IF active scene is game screen to Main Menu [Delete after! :)]
	else if (m_activeScene == m_scenes[1] && Input::GetKeyDown(Key::Space))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Main Menu";
		m_clearColor = vec4(0.28f, 0.59f, 0.28f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];
	}
}

void Game::KeyboardUp()
{
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
