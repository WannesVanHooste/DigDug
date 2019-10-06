#pragma once
#include <Component.h>
#include "TextureComponent.h"
#include "CollisionComponent.h"

namespace dae {
	class DigDugWeaponComponent :public Component
	{
	public:
		DigDugWeaponComponent(const std::string& filePath, bool friendly);
		virtual ~DigDugWeaponComponent() = default;
		DigDugWeaponComponent(const DigDugWeaponComponent& other) = delete;
		DigDugWeaponComponent(DigDugWeaponComponent&& other) noexcept = delete;
		DigDugWeaponComponent& operator=(const DigDugWeaponComponent& other) = delete;
		DigDugWeaponComponent& operator=(DigDugWeaponComponent&& other) noexcept = delete;
		void AllowCollisionWithTag(const std::string& tag);
		void Update(float deltaTime) override;
		void Render() override;
		void Activate();
		void DeactivateAll();
	private:
		bool m_Active;
		float m_AccuSet;
		float m_FrameTime = 0.3f;
		std::vector<std::shared_ptr<TextureComponent>> m_WeaponTextures;
		std::vector<std::shared_ptr<CollisionComponent>> m_CollisionBoxes;
	};
}

