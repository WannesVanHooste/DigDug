#pragma once
#include "Component.h"
#include "Block.h"

namespace dae {
	class Texture2D;
	class TextureComponent;
	//class RockComponent;
	class MapComponent : public Component
	{
	public:
		virtual ~MapComponent() = default;
		MapComponent(const MapComponent& other) = delete;
		MapComponent(MapComponent&& other) noexcept = delete;
		MapComponent& operator=(const MapComponent& other) = delete;
		MapComponent& operator=(MapComponent&& other) noexcept = delete;
		MapComponent(int rows, int cols, float tileSize,float startPositionX, float startPositionY, float textureOffset);
		void AddDigger(const std::shared_ptr<GameObject>& digger);
		static std::vector<std::shared_ptr<Block>>& GetBlocks() { return m_Blocks; };
	protected:
		static std::vector<std::shared_ptr<Block>> m_Blocks;
		std::vector<std::shared_ptr<GameObject>> m_Diggers;
		//std::vector<std::shared_ptr<RockComponent>> m_Rocks;
		int m_Rows;
		int m_Cols;
		float m_TileSize;
		float m_StartPositionX;
		float m_StartPositionY;
		float m_TextureOffset;

		void Update(float deltaTime) override;
		void Render() override;
	};
}

