#pragma once
#include "Component.h"
#include "Vector3.h"
#include "CollisionComponent.h"

namespace dae {

	struct Block;
	class TextureComponent;
	class FallingComponent final:public Component
	{
	public:
		FallingComponent(const std::vector<std::shared_ptr<Block>>& blocks,const std::string& texturePath,int row, int col, int rows, int cols, float tileSize, float textureOffset);
		virtual ~FallingComponent() = default;
		FallingComponent(const FallingComponent& other) = delete;
		FallingComponent(FallingComponent&& other) noexcept = delete;
		FallingComponent& operator=(const FallingComponent& other) = delete;
		FallingComponent& operator=(FallingComponent&& other) noexcept = delete;
		void SetDiggers(const std::vector<std::shared_ptr<GameObject>>& diggers) { m_Diggers = diggers; };
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<TextureComponent> m_Texture;
		std::shared_ptr<CollisionComponent> m_Collider;
		int m_Index;
		int m_Rows;
		int m_Cols;
		float m_TileSize;
		float m_TextureOffset;
		float m_EndPosition;
		bool m_IsFalling;
		bool m_CheckRest;
		bool m_IsUnderneath = true;
		bool m_HasFallen = false;
		bool m_Broken = false;
		Vector3 m_Position;
		std::vector<std::shared_ptr<Block>> m_Blocks;
		std::vector<std::shared_ptr<GameObject>> m_Diggers;
	};
}

