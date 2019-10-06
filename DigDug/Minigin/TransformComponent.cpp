#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Position(Vector3{ 0,0,0 })
{
}

void dae::TransformComponent::Translate(float x, float y, float z) {
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z) {
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::Update(float) {

}
void dae::TransformComponent::Render() {
	
}


