#pragma once
#include "Component.h"
#include "Vector3.h"

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent final: public Component
	{
	public:
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;
		TextComponent(const std::string& text, const std::shared_ptr<Font>& font, Vector3 color);
		virtual ~TextComponent() = default;
		void SetText(const std::string& text);
		void SetColor(Vector3 color);
		void Update(float deltaTime) override;
		void Render() override;
		void Render(Vector3 pos); //used by the FPSComponent
	private:
		bool mNeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		Vector3 m_Color;
	};
}

