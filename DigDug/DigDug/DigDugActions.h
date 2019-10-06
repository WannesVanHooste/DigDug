#pragma once
#include <StateMachine.h>
#include "Locator.h"
#include "AIComponent.h"


namespace dae {
	class InflateAction : public Action
	{
	public:
		void Invoke(int idx, float deltaTime) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->Inflate(deltaTime);
		}
	};

	class DeflateAction : public Action
	{
	public:
		void Invoke(int idx, float deltaTime) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->Deflate(deltaTime);
		}
	};

	class DeadAction : public Action
	{
	public:
		void Invoke(int idx, float) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->Dead();
		}
	};


	class RockAction : public Action
	{
	public:
		void Invoke(int idx, float deltaTime) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->DeadByRock(deltaTime);
		}
	};

	class IdleAction : public Action
	{
	public:
		void Invoke(int idx, float) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->Idle();
		}
	};

	class CreatePathAction : public Action
	{
	public:
		void Invoke(int idx, float) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->CalculatePath();
		}
	};

	class RunToPlayerAction : public Action
	{
	public:
		void Invoke(int idx, float) override {
			Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->RunToPlayer();
		}
	};
}

