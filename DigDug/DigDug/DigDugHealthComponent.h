#pragma once
#include "TextureComponent.h"

namespace dae {
	class DigDugHealthComponent final:public Component
	{
	public:
		DigDugHealthComponent(int lives, Vector3 startPos, const std::string& filePath, Vector3 respawnPoint);
		virtual ~DigDugHealthComponent() = default;
		DigDugHealthComponent(const DigDugHealthComponent& other) = delete;
		DigDugHealthComponent(DigDugHealthComponent&& other) noexcept = delete;
		DigDugHealthComponent& operator=(const DigDugHealthComponent& other) = delete;
		DigDugHealthComponent& operator=(DigDugHealthComponent&& other) noexcept = delete;
		void Update(float deltaTime) override;
		void Render() override;
		void RemoveLife();
		Vector3 GetSpawnPoint() { return m_RespawnPoint; }
		int GetLives() { return m_Lives; }
		void SetLives(int lives) { m_Lives = lives; }
	;	private:
		std::vector<std::shared_ptr<TextureComponent>> m_LifeTextures;
		float m_DieTime;
		float m_AccuSec;
		Vector3 m_StartPos;
		Vector3 m_RespawnPoint;
		bool m_IsDying = false;
		int m_Lives = 3;
	};
}

