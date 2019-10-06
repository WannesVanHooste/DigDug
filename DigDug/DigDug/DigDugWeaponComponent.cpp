#include "pch.h"
#include "DigDugWeaponComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "Logger.h"
#include "CollisionComponent.h"

dae::DigDugWeaponComponent::DigDugWeaponComponent(const std::string& filePath, bool friendly)
	:m_Active(false)
{
	for(int i{}; i < 4; ++i) {
		m_WeaponTextures.push_back(std::make_shared<TextureComponent>(filePath, 64.0f, 64.0f, SDL_Rect{i * 64,0,64,64}));
	}
	if (friendly)
	{
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(50.0f, 30.0f, "Weapon", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(50.0f, 30.0f, "Weapon", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(30.0f, 50.0f, "Weapon", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(30.0f, 50.0f, "Weapon", 16));
	}else {
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(50.0f, 30.0f, "Fire", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(50.0f, 30.0f, "Fire", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(30.0f, 50.0f, "Fire", 16));
		m_CollisionBoxes.push_back(std::make_shared<CollisionComponent>(30.0f, 50.0f, "Fire", 16));
	}
	for(auto element : m_CollisionBoxes) {
		element->SetActive(false);
	}
}

void dae::DigDugWeaponComponent::AllowCollisionWithTag(const std::string& tag) {
	for(auto element: m_CollisionBoxes) {
		element->AllowCollisionWithTag(tag);
	}
}

void dae::DigDugWeaponComponent::Update(float deltaTime) {
	if (m_Active)
	{
		m_AccuSet += deltaTime;
		if (m_AccuSet > m_FrameTime)
		{
			m_Active = false;
			for (auto elements : m_CollisionBoxes) {
				elements->SetActive(false);
			}
			m_AccuSet = 0;
		}
	}
	m_CollisionBoxes[0]->Update(m_pGameObject->GetTransform()->GetPosition().x - 64, m_pGameObject->GetTransform()->GetPosition().y);
	m_CollisionBoxes[1]->Update(m_pGameObject->GetTransform()->GetPosition().x+32, m_pGameObject->GetTransform()->GetPosition().y);
	m_CollisionBoxes[2]->Update(m_pGameObject->GetTransform()->GetPosition().x, m_pGameObject->GetTransform()->GetPosition().y - 64);
	m_CollisionBoxes[3]->Update(m_pGameObject->GetTransform()->GetPosition().x, m_pGameObject->GetTransform()->GetPosition().y + 32);
}

void dae::DigDugWeaponComponent::Render() {
	if (m_Active)
	{
		if (m_pGameObject->HasComponent<MovementComponent>()) {
			Vector3 pos{};
			int movementID = int(m_pGameObject->GetComponent<MovementComponent>()->GetDirection());
			if (movementID == 0)
			{
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 64, m_pGameObject->GetTransform()->GetPosition().y - 32, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else if (movementID == 1) {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x, m_pGameObject->GetTransform()->GetPosition().y - 32, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else if (movementID == 2) {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 32, m_pGameObject->GetTransform()->GetPosition().y - 64, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 32, m_pGameObject->GetTransform()->GetPosition().y, m_pGameObject->GetTransform()->GetPosition().z };
			}
			m_WeaponTextures[movementID]->Render(pos);
		}
		else {
			Logger::GetInstance().LogError("This GameObject has no MovementComponent");
		}
	}
	//m_CollisionBoxes[0]->Render();
	//m_CollisionBoxes[1]->Render();
	//m_CollisionBoxes[2]->Render();
	//m_CollisionBoxes[3]->Render();
}

void dae::DigDugWeaponComponent::Activate() {
	m_Active = true;
	for(auto elements: m_CollisionBoxes) {
		elements->SetActive(false);
	}
	int movementID = int(m_pGameObject->GetComponent<MovementComponent>()->GetDirection());
	m_CollisionBoxes[movementID]->SetActive(true);
}

void dae::DigDugWeaponComponent::DeactivateAll() {
	for(auto element : m_CollisionBoxes) {
		element->SetActive(false);
	}
}


