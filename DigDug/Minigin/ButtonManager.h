#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace dae {

	class ButtonManager final
	{
	public:
		ButtonManager() = default;
		void AddButton(const std::shared_ptr<GameObject>& button);
		void NextButton();
		void PreviousButton();
		void Update(float deltaTime);
		std::shared_ptr<GameObject> GetActiveButton();
		void SetActiveButtonByIndex(int i) { m_pActiveButton = m_pButtons[i]; }
	private:
		std::vector<std::shared_ptr<GameObject>> m_pButtons;

		std::shared_ptr<GameObject> m_pActiveButton;
		float m_ElapsedSec;
	};
}

