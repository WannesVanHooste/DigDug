#include "MiniginPCH.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"
//#include "Renderer.h"

std::multimap<std::string, dae::CollisionComponent*> dae::CollisionComponent::m_Colliders;

dae::CollisionComponent::CollisionComponent(float Width, float Height, const std::string& tag, int textureOffset)
	:m_Rect(Rectangle{0,0,Width,Height})
,m_TextureOffset(textureOffset)
{
	m_Tag = tag;
	m_Colliders.insert({ tag, this });
}

void dae::CollisionComponent::AllowCollisionWithTag(const std::string& tag) {
	for(auto element : m_CollidingTags)
	{
		if(element == tag) {
			return;
		}
	}
	m_CollidingTags.push_back(tag);
}

bool dae::CollisionComponent::CheckCollision(Rectangle other) {
	//if (m_Rect.xPos < other.xPos + other.Widht && m_Rect.xPos + m_Rect.Widht > other.xPos &&
	//	m_Rect.yPos + m_Rect.height > other.yPos && m_Rect.yPos < other.yPos + other.height) {
	//	return true;
	//}
	//return false;

	if (m_Rect.xPos > other.xPos + other.Widht ||
		other.xPos > m_Rect.xPos + m_Rect.Widht)
		return false;
	if (m_Rect.yPos > other.yPos + other.height ||
		other.yPos > m_Rect.yPos + m_Rect.height)
		return false;
	return true;
}
void dae::CollisionComponent::Render() {
	//if (m_Active)
	//{
	//	auto& rend = Renderer::GetInstance();
	//	rend.RenderQuad(m_Rect.xPos, m_Rect.yPos, m_Rect.Widht, m_Rect.height);
	//}
}

void dae::CollisionComponent::Update(float) {
	m_Rect.xPos = m_pGameObject->GetTransform()->GetPosition().x - m_TextureOffset;
	m_Rect.yPos = m_pGameObject->GetTransform()->GetPosition().y - m_TextureOffset;
	CheckCollisionWithTags();
}

void dae::CollisionComponent::Update(float posX, float posY) {
	m_Rect.xPos = posX - m_TextureOffset;
	m_Rect.yPos = posY - m_TextureOffset;
	CheckCollisionWithTags();
}

void dae::CollisionComponent::CheckCollisionWithTags() {
	if (m_Active)
	{
		for (auto element : m_Colliders) { //for every collider

			if (element.second != this) { //if its not colliding with himself

				for (unsigned int i{}; i < m_CollidingTags.size(); ++i) {
					if (element.first == m_CollidingTags[i]) { //if the collider can collide with the tag
						//Check for collision
						if (CheckCollision(element.second->m_Rect)) { //if you collide with object both are colliding
							if (element.second->m_Active)
							{
								m_CollidingTag = element.second->m_Tag;
								element.second->m_CollidingTag = m_Tag;
								element.second->m_IsColliding = true;
								m_IsColliding = true;
								break; //if you collided with something break
							}
						}
						else { // if you didnt collide with objects
							m_IsColliding = false;
						}
					}
				}
			}
		}
	}
}


