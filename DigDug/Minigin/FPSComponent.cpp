#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<Font> font, Vector3 color) {
	m_TextComp = std::make_shared<TextComponent>( "FPS:", font, color);
}

void dae::FPSComponent::Update(float deltaTime) {
	m_FpsUpdateDelay -= deltaTime;
	if (m_FpsUpdateDelay <= 0)
	{
		m_TextComp->SetText("FPS: " + std::to_string(int(1.0f / deltaTime)));
		m_FpsUpdateDelay = 1.0f;
		m_TextComp->Update(deltaTime);
	}
}

void dae::FPSComponent::Render() {
	m_TextComp->Render(GetGameObject()->GetTransform()->GetPosition());
}
