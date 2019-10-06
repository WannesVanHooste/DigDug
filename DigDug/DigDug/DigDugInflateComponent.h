#pragma once
#include <Component.h>

namespace dae {
	class DigDugInflateComponent :public Component
	{
	public:
		DigDugInflateComponent();
		virtual ~DigDugInflateComponent() = default;
		DigDugInflateComponent(const DigDugInflateComponent& other) = delete;
		DigDugInflateComponent(DigDugInflateComponent&& other) noexcept = delete;
		DigDugInflateComponent& operator=(const DigDugInflateComponent& other) = delete;
		DigDugInflateComponent& operator=(DigDugInflateComponent&& other) noexcept = delete;
		void Update(float deltaTime) override;
		void Render() override;
		void CalculateScore();
		bool Inflated() {
			if (m_InflateStage == 0) return false;
			return true;
		}
	private:
		bool m_IsDead = false;
		int m_InflateStage = 0;
		float m_AccuSec;
		float m_CheckTime = 0.5f;
	};
}

