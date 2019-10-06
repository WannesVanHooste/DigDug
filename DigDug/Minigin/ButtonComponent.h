#pragma once
#include "Component.h"
#include "Vector3.h"

namespace dae {
	
	class Font;
	class TextComponent;
	class ButtonComponent final :public Component
	{
	public:
		ButtonComponent(const std::string& text, const std::shared_ptr<Font>& font, Vector3 color, void (*f)(), Vector3 position);
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;
		virtual ~ButtonComponent() = default;

		void Focus();
		void Unfocus();
		void Activate();
	protected:
		void Render() override;
		void Update(float deltaTime) override;
	private:
		void(*m_Function)();
		std::shared_ptr<TextComponent> m_Text;
		Vector3 m_Position;
		Vector3 m_NormalColor;
		Vector3 m_FocusColor;
	};
}

