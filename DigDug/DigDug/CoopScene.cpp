#include "pch.h"
#include "CoopScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Locator.h"
#include "DigDugMapComponent.h"
#include "InputCommands.h"
#include "DigDugHealthComponent.h"
#include "EnemySpawner.h"
#include "PointsManager.h"

dae::CoopScene::CoopScene()
	:Scene("CoopScene") {
}

void dae::CoopScene::ReInitialize() {
	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	auto level = std::make_shared<GameObject>();
	DigDugMapComponent* map = new DigDugMapComponent{ "level" + std::to_string(m_Level) + ".bin", 15, 14,32, 0,64,16 };
	level->AddComponent(map);
	Add(level);


	MovementComponent* movement = new MovementComponent{ 2.0f,0,64,448, 542,16,32, "CharacterSpriteSheet.png" };
	MovementComponent* movement2 = new MovementComponent{ 2.0f,0,64,448, 542,16,32, "CharacterSpriteSheet2.png" };
	DigDugHealthComponent* health = new DigDugHealthComponent{ 3, Vector3{10,544,0}, "LifeP1.png", Vector3{48,48,0} };
	DigDugHealthComponent* health2 = new DigDugHealthComponent{ 3, Vector3{320,544,0}, "LifeP2.png", Vector3{368,48,0} };
	DigDugWeaponComponent* weapon = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon->AllowCollisionWithTag("Enemy");
	DigDugWeaponComponent* weapon2 = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon2->AllowCollisionWithTag("Enemy");
	CollisionComponent* collision = new CollisionComponent{ 30,30, "Player",16 };
	collision->AllowCollisionWithTag("Enemy");
	collision->AllowCollisionWithTag("Rock");
	CollisionComponent* collision2 = new CollisionComponent{ 30,30, "Player",16 };
	collision2->AllowCollisionWithTag("Enemy");
	collision2->AllowCollisionWithTag("Rock");

	auto player1 = std::make_shared<GameObject>();
	player1->AddComponent(movement);
	player1->AddComponent(health);
	player1->AddComponent(weapon);
	player1->AddComponent(collision);
	player1->GetTransform()->SetPosition(48, 48, 0);
	Add(player1);

	map->AddDigger(player1);

	auto player2 = std::make_shared<GameObject>();
	player2->AddComponent(movement2);
	player2->AddComponent(health2);
	player2->AddComponent(weapon2);
	player2->AddComponent(collision2);
	player2->GetTransform()->SetPosition(368, 48, 0);
	Add(player2);

	map->AddDigger(player2);

	Locator::ProvidePlayerOne(player1);
	Locator::ProvidePlayerTwo(player2);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);


	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", 12, 14));
	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", 2, 12));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", 10, 7));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", 7, 5));
}

void dae::CoopScene::Initialize() {

	//std::shared_ptr<Input> m_Player2 = std::make_shared<Input>();
	//Locator::ProvidePlayerTwoInput(m_Player2);

	auto& input = InputManager::GetInstance();

	input.AddInputAction(InputAction{ 0,KeyState::Down, 'A', XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveLeftCommand> left = std::make_shared<MoveLeftCommand>();
	input.SetCommand(0, left);

	input.AddInputAction(InputAction{ 1,KeyState::Down, 'D', XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveRightCommand> right = std::make_shared<MoveRightCommand>();
	input.SetCommand(1, right);

	input.AddInputAction(InputAction{ 2,KeyState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveUpCommand> up = std::make_shared<MoveUpCommand>();
	input.SetCommand(2, up);

	input.AddInputAction(InputAction{ 3,KeyState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveDownCommand> down = std::make_shared<MoveDownCommand>();
	input.SetCommand(3, down);

	input.AddInputAction(InputAction{ 4,KeyState::Released, VK_SPACE, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne });
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>();
	input.SetCommand(4, shoot);

	input.AddInputAction(InputAction{ 5,KeyState::Down, VK_LEFT, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerTwo });
	left = std::make_shared<MoveLeftCommand>();
	input.SetCommand(5, left);

	input.AddInputAction(InputAction{ 6,KeyState::Down, VK_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerTwo });
	right = std::make_shared<MoveRightCommand>();
	input.SetCommand(6, right);

	input.AddInputAction(InputAction{ 7,KeyState::Down, VK_UP, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerTwo });
	up = std::make_shared<MoveUpCommand>();
	input.SetCommand(7, up);

	input.AddInputAction(InputAction{ 8,KeyState::Down, VK_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerTwo });
	down = std::make_shared<MoveDownCommand>();
	input.SetCommand(8, down);

	input.AddInputAction(InputAction{ 9,KeyState::Released, VK_SHIFT, XINPUT_GAMEPAD_A, GamepadIndex::PlayerTwo });
	shoot = std::make_shared<ShootCommand>();
	input.SetCommand(9, shoot);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	auto level = std::make_shared<GameObject>();
	DigDugMapComponent* map = new DigDugMapComponent{ "level" + std::to_string(m_Level) + ".bin", 15, 14,32, 0,64,16 };
	level->AddComponent(map);
	Add(level);


	MovementComponent* movement = new MovementComponent{ 2.0f,0,64,448, 542,16,32, "CharacterSpriteSheet.png" };
	MovementComponent* movement2 = new MovementComponent{ 2.0f,0,64,448, 542,16,32, "CharacterSpriteSheet2.png" };
	DigDugHealthComponent* health = new DigDugHealthComponent{ 3, Vector3{10,544,0}, "LifeP1.png", Vector3{48,48,0} };
	DigDugHealthComponent* health2 = new DigDugHealthComponent{ 3, Vector3{320,544,0}, "LifeP2.png", Vector3{368,48,0} };
	DigDugWeaponComponent* weapon = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon->AllowCollisionWithTag("Enemy");
	DigDugWeaponComponent* weapon2 = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon2->AllowCollisionWithTag("Enemy");
	CollisionComponent* collision = new CollisionComponent{ 30,30, "Player",16 };
	collision->AllowCollisionWithTag("Enemy");
	collision->AllowCollisionWithTag("Rock");
	CollisionComponent* collision2 = new CollisionComponent{ 30,30, "Player",16 };
	collision2->AllowCollisionWithTag("Enemy");
	collision2->AllowCollisionWithTag("Rock");

	auto player1 = std::make_shared<GameObject>();
	player1->AddComponent(movement);
	player1->AddComponent(health);
	player1->AddComponent(weapon);
	player1->AddComponent(collision);
	player1->GetTransform()->SetPosition(48, 48, 0);
	Add(player1);

	map->AddDigger(player1);

	auto player2 = std::make_shared<GameObject>();
	player2->AddComponent(movement2);
	player2->AddComponent(health2);
	player2->AddComponent(weapon2);
	player2->AddComponent(collision2);
	player2->GetTransform()->SetPosition(368, 48, 0);
	Add(player2);

	map->AddDigger(player2);

	Locator::ProvidePlayerOne(player1);
	Locator::ProvidePlayerTwo(player2);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);


	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", 1, 11));
	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", 7, 6));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", 9, 9));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", 11, 11));


}

void dae::CoopScene::Update(float) {
	auto& input = InputManager::GetInstance();

	if (input.IsActionTriggered(4)) {
		input.GetCommand(4)->Execute(Locator::GetPlayerOne());
	}
	if (input.IsActionTriggered(0)) {
		input.GetCommand(0)->Execute(Locator::GetPlayerOne());
	}
	else if (input.IsActionTriggered(1)) {
		input.GetCommand(1)->Execute(Locator::GetPlayerOne());
	}
	else if (input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(Locator::GetPlayerOne());
	}
	else if (input.IsActionTriggered(3)) {
		input.GetCommand(3)->Execute(Locator::GetPlayerOne());
	}

	if (input.IsActionTriggered(9)) {
		input.GetCommand(9)->Execute(Locator::GetPlayerTwo());
	}

	if (input.IsActionTriggered(5)) {
		input.GetCommand(5)->Execute(Locator::GetPlayerTwo());
	}
	else if (input.IsActionTriggered(6)) {
		input.GetCommand(6)->Execute(Locator::GetPlayerTwo());
	}
	else if (input.IsActionTriggered(7)) {
		input.GetCommand(7)->Execute(Locator::GetPlayerTwo());
	}
	else if (input.IsActionTriggered(8)) {
		input.GetCommand(8)->Execute(Locator::GetPlayerTwo());
	}


	int i{ 0 };
	for (auto elements : Locator::GetEnemies()) {
		if (elements->GetComponent<AIComponent>()->IsDead()) {
			++i;
		}
	}

	if (i == int(Locator::GetEnemies().size())) {
		++m_Level;
		AIComponent::ResetCount();
		Locator::FlushEnemies();
		ClearScene();
		ReInitialize();
	}

	if ((i == int(Locator::GetEnemies().size()) && m_Level > 2) || (Locator::GetPlayerOne()->GetComponent<DigDugHealthComponent>()->GetLives() <= 0 && Locator::GetPlayerTwo()->GetComponent<DigDugHealthComponent>()->GetLives() <= 0)) {
		m_Level = 1;
		AIComponent::ResetCount();
		Locator::FlushEnemies();
		ClearScene();
		SceneManager::GetInstance().SetActivateScene("EndScene");
	}
}

void dae::CoopScene::Render() {
	PointsManager::GetInstance().Render();
}