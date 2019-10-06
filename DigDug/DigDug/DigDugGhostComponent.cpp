#include "pch.h"
#include "DigDugGhostComponent.h"
#include "TransformComponent.h"
#include "MapComponent.h"
#include "MovementComponent.h"
#include "DigDugInflateComponent.h"

dae::DigDugGhostComponent::DigDugGhostComponent(int gridSize, int cols)
	:m_GridSize(gridSize)
,m_Cols(cols)
{
}



void dae::DigDugGhostComponent::Update(float) {
	int x = int(m_pGameObject->GetTransform()->GetPosition().x) / m_GridSize;
	int y = int(m_pGameObject->GetTransform()->GetPosition().y - 78) / m_GridSize;

	if(!MapComponent::GetBlocks()[y * m_Cols + x]->isPassed) {
		if(!m_pGameObject->GetComponent<DigDugInflateComponent>()->Inflated())
		m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 2, 4, 1, 2);
		m_pGameObject->GetComponent<MovementComponent>()->SetGhostMode(true);
	}
	else {
		m_pGameObject->GetComponent<MovementComponent>()->SetGhostMode(false);
	}
}

void dae::DigDugGhostComponent::Render() {}
