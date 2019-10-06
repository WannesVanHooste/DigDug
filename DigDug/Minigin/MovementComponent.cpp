#include "pch.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

dae::MovementComponent::MovementComponent(float speed, float minX, float minY,float maxX, float maxY, float textureOffset, float tileSize ,const std::string& filePath)
:m_Speed(speed)
,m_MaxY(maxY)
,m_MaxX(maxX)
,m_MinX(minX)
,m_MinY(minY)
,m_CurrentDirection(Direction::Right)
,m_PreviousDirection(Direction::Right)
,m_CanMoveUpDown(true)
,m_CanMoveLeftRight(true)
,m_TextureOffset(textureOffset)
,m_TileSize(tileSize)
{
	m_Sprite = std::make_shared<SpriteComponent>(filePath, 112.0f, 112.0f);
	m_Sprite->SetSpriteInfo(7, 7, 0, 2, 0, 2);
}

dae::MovementComponent::Direction dae::MovementComponent::GetDirection() {
	return m_CurrentDirection;
}

void dae::MovementComponent::LockMovement(bool lock) {
	m_Blocked = lock;
}

void dae::MovementComponent::MoveUp() {
	if (!m_Blocked)
	{
		m_PreviousDirection = m_CurrentDirection;
		m_CurrentDirection = Direction::Up;
		if (m_CanMoveUpDown)
		{
			if (!m_GhostMode)
			{
				m_Sprite->SetSpriteInfo(7, 7, 0, 2, 5, 2);
			}

			if (m_pGameObject->GetTransform()->GetPosition().y + m_Speed >= m_MinY + m_TextureOffset)
			{
				m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
				m_CanMoveLeftRight = false;
			}
		}
	}
}
void dae::MovementComponent::MoveDown(){
	if (!m_Blocked)
	{
		m_PreviousDirection = m_CurrentDirection;
		m_CurrentDirection = Direction::Down;
		if (m_CanMoveUpDown)
		{
			if (!m_GhostMode)
			{
				m_Sprite->SetSpriteInfo(7, 7, 0, 2, 3, 2);
			}

			if (m_pGameObject->GetTransform()->GetPosition().y - m_Speed <= m_MaxY - m_TextureOffset)
			{
				m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
				m_CanMoveLeftRight = false;
			}
		}
	}
}
void dae::MovementComponent::MoveRight(){
	if (!m_Blocked)
	{
		m_PreviousDirection = m_CurrentDirection;
		m_CurrentDirection = Direction::Right;
		if (m_CanMoveLeftRight)
		{
			if (!m_GhostMode)
			{
				m_Sprite->SetSpriteInfo(7, 7, 0, 2, 0, 2);
			}

			if (m_pGameObject->GetTransform()->GetPosition().x + m_Speed <= m_MaxX - m_TextureOffset)
			{
				m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
				m_CanMoveUpDown = false;
			}
		}
	}
}
void dae::MovementComponent::MoveLeft() {
	if (!m_Blocked)
	{
		m_PreviousDirection = m_CurrentDirection;
		m_CurrentDirection = Direction::Left;
		if (m_CanMoveLeftRight)
		{
			if (!m_GhostMode)
			{
				m_Sprite->SetSpriteInfo(7, 7, 0, 2, 1, 2);
			}

			if (m_pGameObject->GetTransform()->GetPosition().x - m_Speed >= m_MinX + m_TextureOffset)
			{
				m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
				m_CanMoveUpDown = false;
			}
		}
	}
}

void dae::MovementComponent::SetSpriteInfo(int rows, int cols, int xOffset1, int xOffset2, int yOffset, float size)
{
	m_Sprite->SetSpriteInfo(rows, cols, xOffset1, xOffset2, yOffset, size);
}

void dae::MovementComponent::Render() {
	m_Sprite->Render(GetGameObject()->GetTransform()->GetPosition());
}
void dae::MovementComponent::Update(float deltaTime) {
	m_Sprite->Update(deltaTime);
	//this makes sure you stay locked on the grid
	if (!m_Blocked)
	{
		if (!m_CanMoveUpDown) //Check for up down movement
		{
			if (m_CurrentDirection == Direction::Up && m_PreviousDirection == Direction::Right) {
				m_Corrections[0] = true;
			}
			else if (m_CurrentDirection == Direction::Up && m_PreviousDirection == Direction::Left) {
				m_Corrections[1] = true;
			}
			else if (m_CurrentDirection == Direction::Down && m_PreviousDirection == Direction::Right) {
				m_Corrections[2] = true;
			}
			else if (m_CurrentDirection == Direction::Down && m_PreviousDirection == Direction::Left) {
				m_Corrections[3] = true;
			}
		}
		if (!m_CanMoveLeftRight) {
			if (m_CurrentDirection == Direction::Left && m_PreviousDirection == Direction::Up) {
				m_Corrections[4] = true;
			}
			else if (m_CurrentDirection == Direction::Left && m_PreviousDirection == Direction::Down) {
				m_Corrections[5] = true;
			}
			else if (m_CurrentDirection == Direction::Right && m_PreviousDirection == Direction::Up) {
				m_Corrections[6] = true;
			}
			else if (m_CurrentDirection == Direction::Right && m_PreviousDirection == Direction::Down) {
				m_Corrections[7] = true;
			}
		}

		for (int i{}; i < 8; ++i) {
			if (m_Corrections[i])
			{
				if (i < 4) {
					if (i % 2 == 0) {
						if (int(m_pGameObject->GetTransform()->GetPosition().x - m_TextureOffset) % int(m_TileSize) == 0) {
							m_CanMoveUpDown = true;
							m_Corrections[i] = false;
						}
						else {
							m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
						}
					}
					else if (i % 2 == 1) {
						if (int(m_pGameObject->GetTransform()->GetPosition().x - m_TextureOffset) % int(m_TileSize) == 0) {
							m_CanMoveUpDown = true;
							m_Corrections[i] = false;
						}
						else {
							m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
						}
					}
				}
				else {
					if (i % 2 == 0) {
						if (int(m_pGameObject->GetTransform()->GetPosition().y - m_TextureOffset) % int(m_TileSize) == 0) {
							m_CanMoveLeftRight = true;
							m_Corrections[i] = false;
						}
						else {
							m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
						}
					}
					else if (i % 2 == 1) {
						if (int(m_pGameObject->GetTransform()->GetPosition().y - m_TextureOffset) % int(m_TileSize) == 0) {
							m_CanMoveLeftRight = true;
							m_Corrections[i] = false;
						}
						else {
							m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
						}
					}
				}
			}
		}
	}
}
