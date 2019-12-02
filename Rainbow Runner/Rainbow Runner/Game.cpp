#include "Game.h"
#include "Sprite.h"
#include "BackEnd.h"
#include "Camera.h"

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
	std::string winName = "Level Cleared";

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
	m_scenes.push_back(new Win(winName));

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
#pragma region Platform Variables
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
		auto p20 = scene->GetPlatform20();
		auto p21 = scene->GetPlatform21();
		auto p22 = scene->GetPlatform22();
		auto p23 = scene->GetPlatform23();
		auto p24 = scene->GetPlatform24();
		auto p25 = scene->GetPlatform25();
		auto p26 = scene->GetPlatform26();
		auto p27 = scene->GetPlatform27();
		auto p28 = scene->GetPlatform28();
		auto p29 = scene->GetPlatform29();
		auto p30 = scene->GetPlatform30();
		auto p31 = scene->GetPlatform31();
		auto p32 = scene->GetPlatform32();
		auto p33 = scene->GetPlatform33();
		auto p34 = scene->GetPlatform34();
		auto p35 = scene->GetPlatform35();
		auto p36 = scene->GetPlatform36();
		auto p37 = scene->GetPlatform37();
		auto p38 = scene->GetPlatform38();
		auto p39 = scene->GetPlatform39();
		auto p40 = scene->GetPlatform40();
		auto p41 = scene->GetPlatform41();
		auto p42 = scene->GetPlatform42();
		auto p43 = scene->GetPlatform43();
		auto p44 = scene->GetPlatform44();
		auto p45 = scene->GetPlatform45();
		auto p46 = scene->GetPlatform46();
		auto p47 = scene->GetPlatform47();
		auto p48 = scene->GetPlatform48();
		auto p49 = scene->GetPlatform49();
		auto p50 = scene->GetPlatform50();
		auto p51 = scene->GetPlatform51();
		auto p52 = scene->GetPlatform52();
		auto p53 = scene->GetPlatform53();
		auto p54 = scene->GetPlatform54();
		auto p55 = scene->GetPlatform55();
		auto p56 = scene->GetPlatform56();
		auto p57 = scene->GetPlatform57();
		auto p58 = scene->GetPlatform58();
		auto p59 = scene->GetPlatform59();
		auto p60 = scene->GetPlatform60();
		auto p61 = scene->GetPlatform61();
		auto p62 = scene->GetPlatform62();
		auto p63 = scene->GetPlatform63();
		auto p64 = scene->GetPlatform64();
		auto p65 = scene->GetPlatform65();
		auto p66 = scene->GetPlatform66();
		auto p67 = scene->GetPlatform67();
		auto p68 = scene->GetPlatform68();
		auto pF = scene->GetPlatform69();
#pragma endregion
	
		float bgSpeed = 120.f;
		float platSpeed = 95.f;

		//Loops the backgrounds
		if (position.x + bgWidth <= 0)
		{
			position.x = position2.x + bgWidth;
		}
		if (position2.x + bgWidth <= 0)
		{
			position2.x = position.x + bgWidth;
		}

#pragma region MOVEMENT
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
			m_register->get<Transform>(p19).SetPositionX(m_register->get<Transform>(p19).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p20).SetPositionX(m_register->get<Transform>(p20).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p21).SetPositionX(m_register->get<Transform>(p21).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p22).SetPositionX(m_register->get<Transform>(p22).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p23).SetPositionX(m_register->get<Transform>(p23).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p24).SetPositionX(m_register->get<Transform>(p24).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p25).SetPositionX(m_register->get<Transform>(p25).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p26).SetPositionX(m_register->get<Transform>(p26).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p27).SetPositionX(m_register->get<Transform>(p27).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p28).SetPositionX(m_register->get<Transform>(p28).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p29).SetPositionX(m_register->get<Transform>(p29).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p30).SetPositionX(m_register->get<Transform>(p30).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p31).SetPositionX(m_register->get<Transform>(p31).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p32).SetPositionX(m_register->get<Transform>(p32).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p33).SetPositionX(m_register->get<Transform>(p33).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p34).SetPositionX(m_register->get<Transform>(p34).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p35).SetPositionX(m_register->get<Transform>(p35).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p36).SetPositionX(m_register->get<Transform>(p36).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p37).SetPositionX(m_register->get<Transform>(p37).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p38).SetPositionX(m_register->get<Transform>(p38).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p39).SetPositionX(m_register->get<Transform>(p39).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p40).SetPositionX(m_register->get<Transform>(p40).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p41).SetPositionX(m_register->get<Transform>(p41).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p42).SetPositionX(m_register->get<Transform>(p42).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p43).SetPositionX(m_register->get<Transform>(p43).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p44).SetPositionX(m_register->get<Transform>(p44).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p45).SetPositionX(m_register->get<Transform>(p45).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p46).SetPositionX(m_register->get<Transform>(p46).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p47).SetPositionX(m_register->get<Transform>(p47).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p48).SetPositionX(m_register->get<Transform>(p48).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p49).SetPositionX(m_register->get<Transform>(p49).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p50).SetPositionX(m_register->get<Transform>(p50).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p51).SetPositionX(m_register->get<Transform>(p51).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p52).SetPositionX(m_register->get<Transform>(p52).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p53).SetPositionX(m_register->get<Transform>(p53).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p54).SetPositionX(m_register->get<Transform>(p54).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p55).SetPositionX(m_register->get<Transform>(p55).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p56).SetPositionX(m_register->get<Transform>(p56).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p57).SetPositionX(m_register->get<Transform>(p57).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p58).SetPositionX(m_register->get<Transform>(p58).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p59).SetPositionX(m_register->get<Transform>(p59).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p60).SetPositionX(m_register->get<Transform>(p60).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p61).SetPositionX(m_register->get<Transform>(p61).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p62).SetPositionX(m_register->get<Transform>(p62).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p63).SetPositionX(m_register->get<Transform>(p63).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p64).SetPositionX(m_register->get<Transform>(p64).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p65).SetPositionX(m_register->get<Transform>(p65).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p66).SetPositionX(m_register->get<Transform>(p66).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p67).SetPositionX(m_register->get<Transform>(p67).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(p68).SetPositionX(m_register->get<Transform>(p68).GetPosition().x - (platSpeed * Timer::deltaTime));
			m_register->get<Transform>(pF).SetPositionX(m_register->get<Transform>(pF).GetPosition().x - (platSpeed * Timer::deltaTime));
		}
#pragma endregion

	}
#pragma endregion
	
#pragma region Death Logic + Win Con
	if (m_activeScene == m_scenes[3])
	{
		if (m_register->get<PhysicsBody>(EntityIdentifier::MainPlayer()).GetColour() == 4 && !begin)
		{
			SceneEditor::ResetEditor();
			m_activeScene->Unload();
			m_scenes[6]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
			m_register = m_scenes[6]->GetScene();
			m_activeScene = m_scenes[6];
			start = false;
			begin = true;
			sndPlaySound("Win.wav", SND_FILENAME | SND_ASYNC);
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
	//XInputManager::Update();

	////Calls all the other input functions
	//GamepadInput();

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

	//Movement of the sprite + Camera
#pragma region Sprites/Colour BG Movement
	if (m_activeScene == m_scenes[3])
	{
		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
		auto entity = scene->GetPlayer();
		auto cam = scene->GetCam();
		vec3 position = m_register->get<Transform>(entity).GetPosition();

		auto redEnt = scene->GetRedBack();
		auto blueEnt = scene->GetBlueBack();
		auto greenEnt = scene->GetGreenBack();

		float speed = 50.f;

		if (Input::GetKey(Key::RightArrow) && start)
		{
			m_register->get<Transform>(entity).SetPositionX(position.x + (speed * Timer::deltaTime));
		}
		else if (Input::GetKey(Key::LeftArrow) && start)
		{
			m_register->get<Transform>(entity).SetPositionX(position.x - (speed * Timer::deltaTime));
		}		

		//Camera Zoom In and Out
		if (Input::GetKey(Key::Z))
		{
			ECS::GetComponent<Camera>(cam).Zoom(2.f);
		}

		if (Input::GetKey(Key::X))
		{
			ECS::GetComponent<Camera>(cam).Zoom(-2.f);
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
		m_clearColor = vec4(0.0f, 0.0f, 0.0f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];

		sndPlaySound("Run2.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
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
	//Goes back to the main menu when player dies
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
	//Restarts the level if the player died
	else if (m_activeScene == m_scenes[5] && Input::GetKeyDown(Key::Enter))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Rainbow Runner";
		m_clearColor = vec4(0.0f, 0.0f, 0.0f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[3]->GetScene();
		m_activeScene = m_scenes[3];

		sndPlaySound("Run2.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	//Goes back to main menu after level cleared
	else if (m_activeScene == m_scenes[6] && Input::GetKeyDown(Key::Backspace))
	{
		SceneEditor::ResetEditor();

		m_activeScene->Unload();

		m_name = "Main Menu";
		m_clearColor = vec4(0.0f, 0.0f, 0.0f, 1.f);
		m_window->SetWindowName(m_name);

		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
		m_register = m_scenes[0]->GetScene();
		m_activeScene = m_scenes[0];

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

//void Game::GamepadInput()
//{
//	XInputController* tempCon;
//	//Gamepad button stroked (pressed)
//	for (int i = 0; i < 3; i++)
//	{
//		if (XInputManager::ControllerConnected(i))
//		{
//			tempCon = XInputManager::GetController(i);
//			tempCon->SetStickDeadZone(0.1f);
//
//			GamepadDown(tempCon);
//			GamepadStick(tempCon);
//			GamepadTrigger(tempCon);
//		}
//	}							
//}
//
//void Game::GamepadDown(XInputController * con)
//{
//	m_activeScene->GamepadDown(con);
//
//	if (m_activeScene == m_scenes[3])
//	{
//		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
//		auto entity = scene->GetPlayer();
//		auto& animController = ECS::GetComponent<AnimationController>(entity);
//		auto& body = ECS::GetComponent<PhysicsBody>(entity);
//
//		auto redEnt = scene->GetRedBack();
//		auto blueEnt = scene->GetBlueBack();
//		auto greenEnt = scene->GetGreenBack();
//		vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();
//
//		//Sets upwards vel + accel to make the sprite "jump"
//		//Changes the corresponding animation
//		if (con->IsButtonPressed(Buttons::A) && !jump)
//		{
//			body.SetAcceleration(vec3(0.f, 85.f, 0.f));
//			body.SetVelocity(vec3(0.f, 85.f, 0.f));
//			jump = true;
//			animController.SetActiveAnim(1);
//			animController.GetAnimation(1).Reset();
//		}
//		//Checks to see if the player can jump again and changes animation
//				//Eliminates double jumping
//		if (body.GetAcceleration().y == 0.f && body.GetVelocity().y == 0.f)
//		{
//			jump = false;
//			animController.SetActiveAnim(0);
//		}
//	}
//}
//
//void Game::GamepadStick(XInputController * con)
//{
//	//Create an array that stores the left and right thumb stick
//	Stick sticks[2];
//	con->GetSticks(sticks);
//	m_activeScene->GamepadStick(con);
//
//	if (m_activeScene == m_scenes[3])
//	{
//		RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
//		auto entity = scene->GetPlayer();
//		vec3 position = m_register->get<Transform>(entity).GetPosition();
//		float speed = 100.f;
//
//		if (sticks[0].x < -0.1f)
//		{
//			m_register->get<Transform>(entity).SetPositionX(position.x - (speed * Timer::deltaTime));
//		}
//
//		if (sticks[0].x > 0.1f)
//		{
//			m_register->get<Transform>(entity).SetPositionX(position.x + (speed * Timer::deltaTime));
//		}
//	}
//
//	//Switches from Main Menu to Game Screen
//	if (m_activeScene == m_scenes[0] && sticks[0].y < -0.5f || con->IsButtonPressed(Buttons::DPAD_DOWN))
//	{
//		sticks[0].y = 0.f;
//
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Rules";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[1]->GetScene();
//		m_activeScene = m_scenes[1];
//
//		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
//	}
//	//Switches to the game scene
//	else if (m_activeScene == m_scenes[0] && con->IsButtonPressed(Buttons::A))
//	{
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Rainbow Runner";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[3]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[3]->GetScene();
//		m_activeScene = m_scenes[3];
//
//		sndPlaySound("Run2.wav", SND_FILENAME | SND_ASYNC | SND_LOOP);
//	}
//	//Swtiches back IF active scene is game screen to Main Menu
//	else if (m_activeScene == m_scenes[1] && sticks[0].y > 0.9f || con->IsButtonPressed(Buttons::DPAD_UP))
//	{
//		sticks[0].y = 0.f;
//
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Main Menu";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[0]->GetScene();
//		m_activeScene = m_scenes[0];
//
//		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
//	}
//	//Switches from rules to exit button
//	else if (m_activeScene == m_scenes[1] && sticks[0].y < -0.7f || con->IsButtonPressed(Buttons::DPAD_DOWN))
//	{
//		sticks[0].y = 0.f;
//
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Exit";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[2]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[2]->GetScene();
//		m_activeScene = m_scenes[2];
//
//		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
//	}
//	//Switches to the rules section
//	else if (m_activeScene == m_scenes[1] && con->IsButtonPressed(Buttons::A))
//	{
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Rules";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[4]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[4]->GetScene();
//		m_activeScene = m_scenes[4];
//
//		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
//	}
//	//Swithces from exit to rules button
//	else if (m_activeScene == m_scenes[2] && sticks[0].y > 0.10f || con->IsButtonPressed(Buttons::DPAD_UP))
//	{
//		sticks[0].y = 0.f;
//
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Rules";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[1]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[1]->GetScene();
//		m_activeScene = m_scenes[1];
//
//		sndPlaySound("MenuSwitch.wav", SND_FILENAME | SND_ASYNC);
//	}
//	//Exits the program
//	else if (m_activeScene == m_scenes[2] && con->IsButtonPressed(Buttons::A))
//	{
//		exit(1);
//	}
//	//Returns to the main menu from the rules section
//	else if (m_activeScene == m_scenes[4] && con->IsButtonPressed(Buttons::B))
//	{
//		SceneEditor::ResetEditor();
//
//		m_activeScene->Unload();
//
//		m_name = "Main Menu";
//		m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);
//		m_window->SetWindowName(m_name);
//
//		m_scenes[0]->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight()));
//		m_register = m_scenes[0]->GetScene();
//		m_activeScene = m_scenes[0];
//
//		sndPlaySound("MenuSelection.wav", SND_FILENAME | SND_ASYNC);
//	}
//}
//
//void Game::GamepadTrigger(XInputController * con)
//{
//	RainbowRunnerGame* scene = (RainbowRunnerGame*)m_activeScene;
//	auto redEnt = scene->GetRedBack();
//	auto blueEnt = scene->GetBlueBack();
//	auto greenEnt = scene->GetGreenBack();
//	auto entity = scene->GetPlayer();
//
//
//	Triggers triggers;
//	con->GetTriggers(triggers);
//	//Hides the coloured backgrounds
//
//	m_activeScene->GamepadTrigger(con);
//
//	if (m_activeScene == m_scenes[3])
//	{
//		if (triggers.LT > 0.f && triggers.RT > 0.f && allowRed == false && allowYellow == false)
//		{
//			allowBlue = true;
//			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(2);
//			ECS::GetComponent<Transform>(blueEnt).SetPosition(vec3(0.f, 0.f, 90.f));
//		}
//		//Moves the coloured backgrounds
//		if (triggers.RT > 0.8f && allowBlue == false && allowYellow == false)
//		{
//			allowRed = true;
//			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(3);
//			ECS::GetComponent<Transform>(redEnt).SetPosition(vec3(0.f, 0.f, 100.f));
//		}
//		if (triggers.LT > 0.8f && allowRed == false && allowBlue == false)
//		{
//			allowYellow = true;
//			ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()).SetColour(1);
//			ECS::GetComponent<Transform>(greenEnt).SetPosition(vec3(0.f, 0.f, 90.f));
//		}
//		if (triggers.RT == 0.f)
//		{
//			allowRed = false;
//			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
//			ECS::GetComponent<Transform>(redEnt).SetPosition(vec3(0.f, 0.f, 0.f));
//
//		}
//		if (triggers.RT == 0.f && triggers.LT == 0.f)
//		{
//			allowBlue = false;
//			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
//			ECS::GetComponent<Transform>(blueEnt).SetPosition(vec3(0.f, 0.f, 0.f));
//		}
//		if (triggers.LT == 0.f)
//		{
//			allowYellow = false;
//			ECS::GetComponent<PhysicsBody>(entity).SetColour(0);
//			ECS::GetComponent<Transform>(greenEnt).SetPosition(vec3(0.f, 0.f, 0.f));
//		}
//	}
//}
