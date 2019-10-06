#include "MiniginPCH.h"
#include "MapComponent.h"
#include "Vector3.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "BinaryReader.h"

std::vector<std::shared_ptr<dae::Block>> dae::MapComponent::m_Blocks;

dae::MapComponent::MapComponent(int rows, int cols, float tileSize,float startPositionX, float startPositionY, float textureOffset) 
:m_Rows(rows)
,m_Cols(cols)
,m_StartPositionX(startPositionX)
,m_StartPositionY(startPositionY)
,m_TextureOffset(textureOffset)
,m_TileSize(tileSize)
{
	//map size 210
	for(int i{}; i < rows; ++i) {
		for(int j{}; j < cols; ++j) {
			m_Blocks.push_back(std::make_shared<Block>(Block{ Vector3{j * tileSize + textureOffset + startPositionX,
				textureOffset + startPositionY + (i * tileSize),0 }, false }));
		}
	}
}

void dae::MapComponent::AddDigger(const std::shared_ptr<GameObject>& digger) {
	m_Diggers.push_back(digger);
}

void dae::MapComponent::Update(float) {

	//for every digger, if digger passes a block set it on passed
	for (unsigned int j{}; j < m_Diggers.size(); ++j)
	{
		for (int i{}; i < m_Cols * m_Rows; ++i) {
			if (int(m_Diggers[j]->GetTransform()->GetPosition().x) == m_Blocks[i]->position.x && int(m_Diggers[j]->GetTransform()->GetPosition().y) == m_Blocks[i]->position.y) {
				m_Blocks[i]->isPassed = true;
			}
		}
	}
}

void dae::MapComponent::Render() {
	
}
