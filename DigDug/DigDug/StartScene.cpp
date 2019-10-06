#include "pch.h"
#include "StartScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Command.h"
#include "Locator.h"
#include "ButtonManager.h"
#include "SceneManager.h"
#include "ButtonComponent.h"
#include "InputCommands.h"

dae::StartScene::StartScene()
	:Scene("StartScene")
{
}

void dae::StartScene::Initialize() {

//std::shared_ptr<ButtonActivateCommand> buttonDown = std::make_shared<ButtonActivateCommand>();
//Locator::GetPlayerOneInput()->SetCommandToButton(buttonDown, ControllerButton::ButtonA);

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

auto buttonManager = std::make_shared<ButtonManager>();
auto buttonSolo = std::make_shared<GameObject>();
auto buttonCoop = std::make_shared<GameObject>();
auto buttonVersus = std::make_shared<GameObject>();


auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
ButtonComponent* button = new ButtonComponent("Solo", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("SoloScene"); }, Vector3{ 180.0f,144.0f,0 });
buttonSolo->AddComponent(button);
buttonManager->AddButton(buttonSolo);
Add(buttonSolo);

ButtonComponent* button1 = new ButtonComponent("Co-op", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("CoopScene");}, Vector3{ 180.0f,288.0f,0 });
buttonCoop->AddComponent(button1);
buttonManager->AddButton(buttonCoop);
Add(buttonCoop);

ButtonComponent* button2 = new ButtonComponent("Versus", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("VersusScene");}, Vector3{ 180.0f,432.0f,0 });
buttonVersus->AddComponent(button2);
buttonManager->AddButton(buttonVersus);
Add(buttonVersus);

Locator::ProvideButtonManager(buttonManager);
}

void dae::StartScene::Update(float deltaTime) {
	auto& input = InputManager::GetInstance();
	auto activeButton = Locator::GetButtonManager()->GetActiveButton();
	if(input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(activeButton);
	}
	Locator::GetButtonManager()->Update(deltaTime);
}

void dae::StartScene::Render() {
}
