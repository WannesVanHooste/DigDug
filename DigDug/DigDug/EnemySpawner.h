#pragma once
#include "GameObject.h"
#include "Vector3.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "AIComponent.h"
#include "Locator.h"
#include "TransformComponent.h"

namespace dae {
	class EnemySpawner
	{
	public:
		EnemySpawner() = default;
		~EnemySpawner() = default;

		static std::shared_ptr<GameObject> SpawnEnemy(const std::string& spritePath, int col, int row) {
			std::shared_ptr<GameObject> go = std::make_shared<GameObject>();
			AIComponent* aiComp = new AIComponent{};
			CollisionComponent* coll = new CollisionComponent{ 30,30,"Enemy", 16 };
			SpriteComponent* sprite = new SpriteComponent{spritePath , 112.0f,112.0f };
			sprite->SetSpriteInfo(7, 7, 0, 2, 0, 2);
			coll->AllowCollisionWithTag("Weapon");
			coll->AllowCollisionWithTag("Rock");
			coll->AllowCollisionWithTag("Player");

			go->AddComponent(aiComp);
			go->AddComponent(coll);
			go->AddComponent(sprite);
			go->GetTransform()->SetPosition((col* 32.0f) + 16.0f, (row* 32.0f) + 16.0f, 0);

			Locator::ProvideEnemy(go);
			return go;
		}
	};
}

