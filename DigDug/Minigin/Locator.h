#pragma once
#include "InputManager.h"
#include "ButtonManager.h"

namespace dae {
	class Locator //class based off Week7 locator
	{
	public:
		static void Initialize() { m_Player1 = m_NullGameObject; m_Player2 = m_NullGameObject; }

		static std::shared_ptr<GameObject>& GetPlayerOne() { return m_Player1; }
		static std::shared_ptr<GameObject>& GetPlayerTwo() { return m_Player2; }
		static std::shared_ptr<ButtonManager>& GetButtonManager() { return m_ButtonManager; }
		static void FlushEnemies() { m_Enemies.clear(); }
		static std::vector<std::shared_ptr<GameObject>>& GetEnemies(){ return m_Enemies; }

		static void ProvideButtonManager(const std::shared_ptr<ButtonManager>& buttonManager) {
			m_ButtonManager = buttonManager;
		}

		static void ProvideEnemy(const std::shared_ptr<GameObject>& enemy) {
			m_Enemies.push_back(enemy);
		}

		static void ProvidePlayerOne(std::shared_ptr<GameObject> service)
		{
			if (service == nullptr)
			{
				m_Player1 = m_NullGameObject;
			}
			else
			{
				m_Player1 = service;
			}
		}
		static void ProvidePlayerTwo(std::shared_ptr<GameObject> service)
		{
			if (service == nullptr)
			{
				m_Player2 = m_NullGameObject;
			}
			else
			{
				m_Player2 = service;
			}
		}

	private:
		static std::shared_ptr<GameObject> m_Player1;
		static std::shared_ptr<GameObject> m_Player2;
		static std::shared_ptr<GameObject> m_NullGameObject;
		static std::shared_ptr<ButtonManager> m_ButtonManager;
		static std::vector<std::shared_ptr<GameObject>> m_Enemies;
	};
}

