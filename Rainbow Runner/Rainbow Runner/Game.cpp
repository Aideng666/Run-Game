#include "Game.h"
#include "Sprite.h"
#include "BackEnd.h"

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
	std::string gameOverName = "Game Over";

	//Initialize the current scene (starting screen)
	m_name = menuName;
	m_clearColor = vec4(0.0f, 0.0f, 0.0f, 1.f);

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
	m_scenes.push_back(new GameOver(gameOverName));

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

#pragma region Scrolling Backgrounds/Platform
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

		auto s = scene->GetStart();

		//Platforms Moving 
		auto pS = scene->GetPlatformS();
		auto p1 = scene->GetPlatform1();
		auto p2 = scene->GetPlatform2();
		auto p3 = scene->GetPlatform3();
		auto p4 = scene->GetPlatform4();
		auto p5 = scene->GetPlatform5();
		auto p6 = scene->GetPlatform6();
		auto p7 = scene->GetPlatform7();
		auto p8 = scene->GetPlatform8();
		auto p9 = scene->GetPlatform9();
		auto p10 = scene->GetPlatform10();
		auto p11 = scene->GetPlatform11();
		auto p12 = scene->GetPlatform12();
		auto p13 = scene->GetPlatform13();
		auto p14 = scene->GetPlatform14();
		auto p15 = scene->GetPlatform15();
		auto p16 = scene->GetPlatform16();
		auto p17 = scene->GetPlatform17();
		auto p18 = scene->GetPlatform18();

		auto p19 = scene->GetPlatform19();

		float bgSpeed = 100.f;
		float platSpeed = 70.f;
		float platSpeed2 = 72.f;

		//Loops the backgrounds
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
			m_register->get<Transform>(s).SetPositionX(m_register->get<Transform>(s).GetPosition().x - (bgSpeed * Timer::deltaTime));
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			m_register->get<Transform>(pS).SetPositionX(m_register->get<Transform>(pS).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p1).SetPositionX(m_register->get<Transform>(p1).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p2).SetPositionX(m_register->get<Transform>(p2).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p3).SetPositionX(m_register->get<Transform>(p3).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p4).SetPositionX(m_register->get<Transform>(p4).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p5).SetPositionX(m_register->get<Transform>(p5).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p6).SetPositionX(m_register->get<Transform>(p6).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p7).SetPositionX(m_register->get<Transform>(p7).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p8).SetPositionX(m_register->get<Transform>(p8).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p9).SetPositionX(m_register->get<Transform>(p9).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p10).SetPositionX(m_register->get<Transform>(p10).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p11).SetPositionX(m_register->get<Transform>(p11).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p12).SetPositionX(m_register->get<Transform>(p12).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p13).SetPositionX(m_register->get<Transform>(p13).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p14).SetPositionX(m_register->get<Transform>(p14).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p15).SetPositionX(m_register->get<Transform>(p15).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p16).SetPositionX(m_register->get<Transform>(p16).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p17).SetPositionX(m_register->get<Transform>(p17).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p18).SetPositionX(m_register->get<Transform>(p18).GetPosition().x - (platSpeed * Timer::deltaTime));

			m_register->get<Transform>(p19).SetPositionX(m_register->get<Transform>(p19).GetPosition().x - (platSpeed2 * Timer::deltaTime));

		}		
	}
#pragma endregion
	
#pragma region Death Logic
	if (m_activeScene == m_scenes[3])
	{
		if (m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetColour() == 4 && !begin)
		{
			start = false;
			begin = true;
		}

		if (m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition().y <= -140)
		{
			SceneEditor::ResetEditor();
			m_activeScene->Unload();
			m_scenes[5]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
			m_register = m_scenes[5]->GetScene();
			m_activeScene = m_scenes[5];
			start = false;
			begin = false;
			sndPlaySound("Lose.wav", SND_FILENAME | SND_ASYNC);
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
#pragma region Sprites/Colour BG Movement
	if (m_activeScene == m_scenes[3])
	{
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
		auto entity = scene->GetPlayer();
		vec3 position = m_register->get<Transform>(entity).GetPosition();

		auto redEnt = scene->GetRedBack();
		auto blueEnt = scene->GetBlueBack();
		auto greenEnt = scene->GetGreenBack();

		float speed = 100.f;

		if (Input::GetKey(Key::RightArrow))
		{
			m_register->get<Transform>(entity).SetPositionX(position.x + (speed * Timer::deltaTime));
		}
		else if (Input::GetKey(Key::LeftArrow))
		{
			m_register->get<Transform>(entity).SetPositionX(position.x - (speed * Timer::deltaTime));
		}			

		//Moves the coloured backgrounds
		if (Input::GetKey(Key::A) && allowBlue == false && allowYellow == false)
		{
			allowRed = true;
			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(3);
			ECS::GetComponent<Transform>(redEnt).SetPosition(vec3(0.f, 0.f, 100.f));
		}
		if (Input::GetKey(Key::S) && allowRed == false && allowYellow == false)
		{
			allowBlue = true;
			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(2);
			ECS::GetComponent<Transform>(blueEnt).SetPosition(vec3(0.f, 0.f, 90.f));
		}
		if (Input::GetKey(Key::D) && allowRed == false && allowBlue == false)
		{
			allowYellow = true;
			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(1);
			ECS::GetComponent<Transform>(greenEnt).SetPosition(vec3(0.f, 0.f, 90.f));
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

		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
	}
	//Switches to the game scene
	else if (m_activeScene == m_scenes[0] && Input::GetKeyDown(Key::Enter))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rainbow Runner";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];

		//sndPlaySound("Run2.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
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

		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
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

		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
	}
	//Switches to the rules section
	else if (m_activeScene == m_scenes[1] && Input::GetKeyDown(Key::Enter))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rules";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[4]->GetScene();
		m_activeScene = m_scenes[4];

		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
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

		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
	}
	//Exits the program
	else if (m_activeScene == m_scenes[2] && Input::GetKeyDown(Key::Enter))
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

		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
	}
	else if (m_activeScene == m_scenes[5] && Input::GetKeyDown(Key::Backspace))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Main Menu";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];

		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
	}
	else if (m_activeScene == m_scenes[5] && Input::GetKeyDown(Key::Enter))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rainbow Runner";
		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];

		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
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
		if (Input::GetKeyDown(Key::Space) && !jump)
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
		if (Input::GetKeyDown(Key::DownArrow))
		{
			start = true;
		}
	}
	//Exits fullscreen 
	if (Input::GetKeyDown(Key::Escape))
	{
		exit(1);
	}
}

void Game::KeyboardUp()
{
	RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
	auto redEnt = scene->GetRedBack();
	auto blueEnt = scene->GetBlueBack();
	auto greenEnt = scene->GetGreenBack();
	auto entity = scene->GetPlayer();

	//Hides the coloured backgrounds
	if (m_activeScene == m_scenes[3])
	{
		if (Input::GetKeyUp(Key::P))
		{
			PhysicsBody::SetDraw(!PhysicsBody::GetDraw());
		}
		if (Input::GetKeyUp(Key::A))
		{
			allowRed = false;
			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
			ECS::GetComponent<Transform>(redEnt).SetPosition(vec3(0.f, 0.f, 0.f));

		}
		if (Input::GetKeyUp(Key::S))
		{
			allowBlue = false;
			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
			ECS::GetComponent<Transform>(blueEnt).SetPosition(vec3(0.f, 0.f, 0.f));
		}
		if (Input::GetKeyUp(Key::D))
		{
			allowYellow = false;
			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
			ECS::GetComponent<Transform>(greenEnt).SetPosition(vec3(0.f, 0.f, 0.f));
		}
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