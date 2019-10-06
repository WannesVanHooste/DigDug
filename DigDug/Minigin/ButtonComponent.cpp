#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "Font.h"

dae::ButtonComponent::ButtonComponent(const std::string& text, const std::shared_ptr<Font>& font, Vector3 color, void(*f)(), Vector3 position)
	:m_Function(f)
    ,m_Position(position)
	, m_FocusColor(Vector3{ 255.0f,255.0f,255.0f })
    ,m_NormalColor(color)
{
	m_Text = std::make_shared<TextComponent>(std::move(text), font,color);
}

void dae::ButtonComponent::Focus() {
	m_Text->SetColor(m_FocusColor);
}

void dae::ButtonComponent::Unfocus() {
	m_Text->SetColor(m_NormalColor);
}

void dae::ButtonComponent::Activate() {
	m_Function();
}

void dae::ButtonComponent::Render() {
	m_Text->Render(m_Position);
}
void dae::ButtonComponent::Update(float deltaTime) {
	m_Text->Update(deltaTime);
}

