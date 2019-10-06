#pragma once
#include <Component.h>

namespace  dae {
	class DigDugGhostComponent :
		public Component
	{
	public:
		DigDugGhostComponent(int gridSize, int cols);
		virtual ~DigDugGhostComponent() = default;
		DigDugGhostComponent(const DigDugGhostComponent& other) = delete;
		DigDugGhostComponent(DigDugGhostComponent&& other) noexcept = delete;
		DigDugGhostComponent& operator=(const DigDugGhostComponent& other) = delete;
		DigDugGhostComponent& operator=(DigDugGhostComponent&& other) noexcept = delete;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		int m_GridSize;
		int m_Cols;
	};
}

