#pragma once
#include "Command.h"
#include "MovementComponent.h"
#include "ButtonComponent.h"
#include "DigDugWeaponComponent.h"

namespace dae {

	class MoveRightCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveRight();
				//object->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 0, 2);

			}
		}
	};
	class MoveLeftCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveLeft();
				//object->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 1, 2);
			}
		}
	};

	class MoveUpCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveUp();
				//object->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 5, 2);
			}
		}
	};

	class MoveDownCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override
		{
			if (object->HasComponent<MovementComponent>())
			{
				object->GetComponent<MovementComponent>()->MoveDown();
				//object->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 3, 2);
			}
		}
	};

	class ButtonActivateCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override {
			if (object->HasComponent<ButtonComponent>()) {
				object->GetComponent<ButtonComponent>()->Activate();
			}
		}
	};

	class ShootCommand final : public Command {
	public:
		void Execute(std::shared_ptr<GameObject>& object) override {
			if (object->HasComponent<DigDugWeaponComponent>()) {
				object->GetComponent<DigDugWeaponComponent>()->Activate();
			}
		}
	};
}
