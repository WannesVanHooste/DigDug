#include "pch.h"
#include "DigDugMapComponent.h"
#include "BinaryReader.h"
//#include "RockComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::DigDugMapComponent::DigDugMapComponent(const std::string& filePath, int rows, int cols, float tileSize, float startPositionX,
	float startPositionY, float textureOffset)
	:MapComponent(rows,cols,tileSize,startPositionX,startPositionY,textureOffset)
{
	BinaryReader reader{ "../Data/Levels/" + filePath };
	for (int i{}; i < rows * cols; ++i) {
		if (reader.Read<bool>() == true) {
			m_Blocks[i]->isPassed = true;
		}
		else {
			m_Blocks[i]->isPassed = false;
		}
	}
	reader.CloseFile();
	m_Rocks.push_back(std::make_shared<FallingComponent>(m_Blocks,"rock.png" ,2, 1, rows, cols, tileSize, textureOffset));
	m_Rocks.push_back(std::make_shared<FallingComponent>(m_Blocks,"rock.png",3, 7, rows, cols, tileSize, textureOffset));
	m_Rocks.push_back(std::make_shared<FallingComponent>(m_Blocks,"rock.png",5, 3, rows, cols, tileSize, textureOffset));
}

void dae::DigDugMapComponent::Update(float deltaTime) {
	for (unsigned int j{}; j < m_Diggers.size(); ++j)
	{
		for (int i{}; i < m_Cols * m_Rows; ++i) {
			if (int(m_Diggers[j]->GetTransform()->GetPosition().x) == m_Blocks[i]->position.x && int(m_Diggers[j]->GetTransform()->GetPosition().y) == m_Blocks[i]->position.y) {
				m_Blocks[i]->isPassed = true;
			}
		}
	}
	for (auto element : m_Rocks) {
		element->SetDiggers(m_Diggers);
		element->Update(deltaTime);
	}
}
void dae::DigDugMapComponent::Render() {
	auto& renderer = Renderer::GetInstance();
	for (int i{}; i < (m_Cols * m_Rows); ++i)
	{
		if (m_Blocks[i]->isPassed == true) {
			renderer.RenderQuad(m_Blocks[i]->position.x - m_TextureOffset, m_Blocks[i]->position.y - m_TextureOffset, m_TileSize, m_TileSize);
		}
	}
	for (auto element : m_Rocks) {
		element->Render();
	}
}
