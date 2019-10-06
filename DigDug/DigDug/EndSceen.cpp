#include "pch.h"
#include "EndSceen.h"
#include "InputManager.h"
#include "InputCommands.h"
#include "ResourceManager.h"
#include <unordered_map>
#include "Locator.h"


dae::EndSceen::EndSceen()
	:Scene("EndScene")
{
}

void dae::EndSceen::Initialize() {
	auto& input = InputManager::GetInstance();

	input.AddInputAction(InputAction{ 0,KeyState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne });

	input.AddInputAction(InputAction{ 1,KeyState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne });

	input.AddInputAction(InputAction{ 2,KeyState::Released, 'P', XINPUT_GAMEPAD_START, GamepadIndex::PlayerOne });
	std::shared_ptr<ButtonActivateCommand> press = std::make_shared<ButtonActivateCommand>();
	input.SetCommand(2, press);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto buttonManager = std::make_shared<ButtonManager>();
	auto buttonRestart = std::make_shared<GameObject>();
	auto buttonMenu = std::make_shared<GameObject>();
	auto buttonQuit = std::make_shared<GameObject>();

	ButtonComponent* button = new ButtonComponent("Restart", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene(SceneManager::GetInstance().GetLastActiveScene()); }, Vector3{ 180.0f,144.0f,0 });
	buttonRestart->AddComponent(button);
	buttonManager->AddButton(buttonRestart);
	Add(buttonRestart);

	ButtonComponent* button1 = new ButtonComponent("Menu", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("StartScene"); }, Vector3{ 180.0f,288.0f,0 });
	buttonMenu->AddComponent(button1);
	buttonManager->AddButton(buttonMenu);
	Add(buttonMenu);

	ButtonComponent* button2 = new ButtonComponent("Quit", font, Vector3{ 0.0f,0.0f,0.0f }, []() { InputManager::GetInstance().QuitGame(); }, Vector3{ 180.0f,432.0f,0 });
	buttonQuit->AddComponent(button2);
	buttonManager->AddButton(buttonQuit);
	Add(buttonQuit);

	Locator::ProvideButtonManager(buttonManager);
}
void dae::EndSceen::Update(float deltaTime) {
	auto& input = InputManager::GetInstance();
	auto activeButton = Locator::GetButtonManager()->GetActiveButton();
	if (input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(activeButton);
	}
	Locator::GetButtonManager()->Update(deltaTime);
}
void dae::EndSceen::Render() {}


