#pragma once
#include "Component.h"
#include "Vector3.h"

namespace dae
{
	class TextComponent;
	class Font;

	class FPSComponent final: public Component
	{
	public:
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		FPSComponent(std::shared_ptr<Font> font, Vector3 color);
		virtual ~FPSComponent() = default;
	protected:
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<TextComponent> m_TextComp;
		float m_FpsUpdateDelay;
	};
}
