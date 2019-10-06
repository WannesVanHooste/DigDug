#pragma once
#include "Component.h"
#include <SDL.h>

namespace dae{

	class Texture2D;
	struct Vector3;
	class SpriteComponent final:public Component
	{
	public:
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;
		virtual ~SpriteComponent() = default;
		SpriteComponent(const std::string& filename, float width, float height);
		void Render(Vector3 pos);
		void SetSpriteInfo(int rows, int cols, int xOffset1, int xOffset2, int yOffset, float scale);
		void Update(float deltaTime) override;
		void StopRender(bool stopRender) { m_StopRender = stopRender; }
	protected:
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Rect m_SourceRect;
		int m_Rows;
		int m_Cols;
		int m_Xoffset1;
		int m_Xoffset2;
		int m_YOffset;
		int m_ActFrame;
		float m_Height;
		float m_Width;
		float m_Scale;
		float m_FrameSec;
		float m_AccuSet;
		bool m_StopRender = false;

		void Render() override;
	};
}

