#pragma once
#include "MapComponent.h"
#include "FallingComponent..h"

namespace dae {
	class DigDugMapComponent final :public MapComponent
	{
	public:
		DigDugMapComponent(const std::string& filePath, int rows, int cols, float tileSize, float startPositionX, float startPositionY, float textureOffset);
		virtual ~DigDugMapComponent() = default;
		DigDugMapComponent(const MapComponent& other) = delete;
		DigDugMapComponent(DigDugMapComponent&& other) noexcept = delete;
		DigDugMapComponent& operator=(const DigDugMapComponent& other) = delete;
		DigDugMapComponent& operator=(DigDugMapComponent&& other) noexcept = delete;
	private:
		std::vector<std::shared_ptr<FallingComponent>> m_Rocks;
		std::shared_ptr<GameObject> m_Versus;

		void Update(float deltaTime) override;
		void Render() override;
	};
}

