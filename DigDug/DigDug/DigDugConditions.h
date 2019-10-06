#pragma once
#include <StateMachine.h>
#include "Locator.h"
#include "CollisionComponent.h"
#include "AIComponent.h"
#include "TransformComponent.h"
#include <cmath>

namespace dae {
	class InflateCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if(Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Weapon") {
				return true;
			}
			return false;
		}
	};

	class DeflateCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie doesnt collides with weapon
			if (Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Weapon") {
				return false;
			}
			return true;
		}
	};

	class DeadCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie is gonna explode
			if (Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->GetInflateState() == 3) {
				return true;
			}
			return false;
		}
	};

	class IdleCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie is going idle
			if (Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->GetInflateState() == 0) {
				return true;
			}
			return false;
		}
	};

	class RockCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if (Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetColliding() &&
				Locator::GetEnemies()[idx]->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Rock") {
				return true;
			}
			return false;
		}
	};

	class RunCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if (Locator::GetPlayerTwo() != nullptr && Locator::GetPlayerTwo()->GetComponent<CollisionComponent>()->GetTag() != "Enemy")
			{
				auto enemyPos = Locator::GetEnemies()[idx]->GetTransform()->GetPosition();
				auto player1Pos = Locator::GetPlayerOne()->GetTransform()->GetPosition();
				auto player2Pos = Locator::GetPlayerTwo()->GetTransform()->GetPosition();
				if (sqrt(pow(enemyPos.x - player1Pos.x, 2) + pow(enemyPos.y - player1Pos.y, 2)) < 175) {
					return true;
				}
				if (sqrt(pow(enemyPos.x - player2Pos.x, 2) + pow(enemyPos.y - player2Pos.y, 2)) < 175) {
					return true;
				}
			}
			else {
				auto enemyPos = Locator::GetEnemies()[idx]->GetTransform()->GetPosition();
				auto player1Pos = Locator::GetPlayerOne()->GetTransform()->GetPosition();
				if(sqrt(pow(enemyPos.x - player1Pos.x, 2) + pow(enemyPos.y - player1Pos.y, 2)) < 175) {
					return true;
				}
			}
			return false;
		}
	};

	class TurnIdleCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			//enemie collides with weapon
			if (Locator::GetPlayerTwo() != nullptr && Locator::GetPlayerTwo()->GetComponent<CollisionComponent>()->GetTag() != "Enemy")
			{
				auto enemyPos = Locator::GetEnemies()[idx]->GetTransform()->GetPosition();
				auto player1Pos = Locator::GetPlayerOne()->GetTransform()->GetPosition();
				auto player2Pos = Locator::GetPlayerTwo()->GetTransform()->GetPosition();
				if (sqrt(pow(enemyPos.x - player1Pos.x, 2) + pow(enemyPos.y - player1Pos.y, 2)) > 175 && sqrt(pow(enemyPos.x - player2Pos.x, 2) + pow(enemyPos.y - player2Pos.y, 2)) > 175) {
					return true;
				}
			}
			else {
				auto enemyPos = Locator::GetEnemies()[idx]->GetTransform()->GetPosition();
				auto player1Pos = Locator::GetPlayerOne()->GetTransform()->GetPosition();
				if (sqrt(pow(enemyPos.x - player1Pos.x, 2) + pow(enemyPos.y - player1Pos.y, 2)) > 175) {
					return true;
				}
			}
			return false;
		}
	};

	class UpdatePathCondition :public Condition
	{
	public:
		bool Invoke(int idx) override {
			if (Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->m_UpdatePath)
			{
				Locator::GetEnemies()[idx]->GetComponent<AIComponent>()->m_UpdatePath = false;
				return true;
			}
			return false;
		}
	};

}

