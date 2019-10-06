#pragma once
#include "Singleton.h"
#include "TextComponent.h"

namespace dae {
	class PointsManager : public dae::Singleton<PointsManager>
	{
	public:
		void AddPoints(int points) { m_Points += points; m_Text->SetText("Score:" + std::to_string(m_Points)); m_Text->Update(1.0f); };
		int GetPoints() { return m_Points; }
		void ResetPoints() { m_Points = 0; m_Text->SetText("Score: 0"); m_Text->Update(1.0f); }
		PointsManager();
		~PointsManager() = default;
		void Render() { m_Text->Render(Vector3{200,0,0}); };
	private:
		int m_Points = 0;
		std::shared_ptr<TextComponent> m_Text;
	};
}

