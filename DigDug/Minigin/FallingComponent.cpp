#include "MiniginPCH.h"
#include "FallingComponent..h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Block.h"
#include <glm/detail/setup.hpp>

dae::FallingComponent::FallingComponent(const std::vector<std::shared_ptr<Block>>& blocks, const std::string& texturePath, int row, int col, int rows, int cols, float tileSize, float textureOffset)
:m_Blocks(std::move(blocks)),m_CheckRest(false),m_IsFalling(false)
,m_Cols(cols)
,m_Rows(rows)
,m_TileSize(tileSize)
,m_TextureOffset(textureOffset)
{
	m_Texture = std::make_shared<TextureComponent>(texturePath);
	m_Collider = std::make_shared<CollisionComponent>(30.0f, 32.0f, "Rock",16);
	m_Collider->AllowCollisionWithTag("Player");
	m_Collider->AllowCollisionWithTag("Enemy");
	m_Collider->SetActive(false);
	m_Index = (row *  cols) + col;
	m_Position = Vector3{ col * tileSize + textureOffset, (tileSize*2 + textureOffset) + (row * tileSize), 0 };
}

void dae::FallingComponent::Update(float) {
	if (!m_Broken)
	{
		m_Collider->Update(m_Position.x, m_Position.y);
		if (m_Blocks[m_Index + m_Cols]->isPassed) {
			m_CheckRest = true;
		}
		else {
			m_CheckRest = false;
		}
		for (int i{ 1 }; i < m_Rows; ++i) {
			if (m_Index + (m_Cols * i) <= int(m_Blocks.size())) {
				if (m_CheckRest) {
					if (m_Blocks[m_Index + (m_Cols * i)]->isPassed) {
						m_EndPosition = m_Blocks[m_Index + (m_Cols * i)]->position.y;
					}
					else {
						m_CheckRest = false;
						m_IsFalling = true;
					}
				}
			}
			else {
				m_IsFalling = true;
			}
		}
		if (m_IsFalling) {
			if (m_Position.y < m_EndPosition) {
				if (m_IsUnderneath)
				{
					for (auto element : m_Diggers) {
						if (element->GetTransform()->GetPosition().x >= m_Position.x - 30 && element->GetTransform()->GetPosition().x <= m_Position.x + 30 && element->GetTransform()->GetPosition().y >= m_Position.y) {
							m_IsUnderneath = true;
							break;
						}
						else {
							m_IsUnderneath = false;
						}
					}
				}
				if (!m_IsUnderneath)
				{
					m_Position.y += 2.f;
					m_Collider->SetActive(true);
					m_HasFallen = true;
				}
			}
			else {
				m_Collider->SetActive(false);
				if (m_HasFallen)
				{
					m_Broken = true;
					m_IsFalling = false;
					m_IsUnderneath = true;;
					m_Collider->SetActive(false);
				}
			}
		}
		else {
			m_Collider->SetActive(false);
		}
	}
}
void dae::FallingComponent::Render() {
	if (!m_Broken)
	{
		m_Texture->Render(Vector3{ m_Position.x - m_TextureOffset, m_Position.y - m_TextureOffset, 0 });
	}
	//m_Collider->Render();
}
