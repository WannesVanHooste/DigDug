#include "MiniginPCH.h"
#include "Locator.h"

std::shared_ptr<dae::GameObject> dae::Locator::m_Player1;
std::shared_ptr<dae::GameObject> dae::Locator::m_Player2;
std::shared_ptr<dae::GameObject> dae::Locator::m_NullGameObject = std::make_shared<GameObject>();
std::shared_ptr<dae::ButtonManager> dae::Locator::m_ButtonManager;
std::vector<std::shared_ptr<dae::GameObject>> dae::Locator::m_Enemies;
