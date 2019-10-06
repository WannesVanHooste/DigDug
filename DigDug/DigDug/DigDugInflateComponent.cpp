#include "pch.h"
#include "DigDugInflateComponent.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "DigDugHealthComponent.h"
#include "TransformComponent.h"
#include "PointsManager.h"

dae::DigDugInflateComponent::DigDugInflateComponent()
	:m_AccuSec(0)
{
}

void dae::DigDugInflateComponent::Update(float deltaTime) {
	if (!m_IsDead)
	{
		m_AccuSec += deltaTime;
		if (m_AccuSec >= m_CheckTime) {
			if (m_pGameObject->GetComponent<CollisionComponent>()->GetColliding() && m_pGameObject->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Weapon") {
				++m_InflateStage;
				m_pGameObject->GetComponent<MovementComponent>()->LockMovement(true);
				m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
				m_AccuSec = 0.0;
				if (m_InflateStage == 3) {
					m_IsDead = true;
					m_AccuSec = 0;
				}
			}
			else {
				if (m_InflateStage != 0) {
					--m_InflateStage;
					m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
					m_AccuSec = 0.0;
				}
				else {
					m_pGameObject->GetComponent<MovementComponent>()->LockMovement(false);
				}
			}
		}
	}

	if(m_IsDead) {
		m_InflateStage = 0;
		m_AccuSec = 0;
		m_pGameObject->GetComponent<MovementComponent>()->LockMovement(false);
		m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 0, 2);
	    m_pGameObject->GetComponent<DigDugHealthComponent>()->RemoveLife();
		Vector3 SpawnPos = m_pGameObject->GetComponent<DigDugHealthComponent>()->GetSpawnPoint();
		CalculateScore();
		m_pGameObject->GetTransform()->SetPosition(SpawnPos.x, SpawnPos.y, SpawnPos.z);
		m_IsDead = false;
	}
}

void dae::DigDugInflateComponent::Render() {
	
}

void dae::DigDugInflateComponent::CalculateScore() {
	float yPos = m_pGameObject->GetTransform()->GetPosition().y;
	if(yPos <= 192) {
		PointsManager::GetInstance().AddPoints(400);
	}
	else if(yPos > 192 && yPos <= 320) {
		PointsManager::GetInstance().AddPoints(600);
	}
	else if (yPos > 320 && yPos <= 448) {
		PointsManager::GetInstance().AddPoints(800);
	}
	else if (yPos > 448 && yPos <= 576) {
		PointsManager::GetInstance().AddPoints(1000);
	}
}

