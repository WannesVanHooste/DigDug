#pragma once
#include "Component.h"
#include <map>


namespace dae {
	struct Rectangle {
		float xPos;
		float yPos;
		float Widht;
		float height;
	};

	class CollisionComponent final:public Component
	{
	public:
		CollisionComponent(float Width, float Height, const std::string& tag, int textureOffset);
		void AllowCollisionWithTag(const std::string& tag);
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
		virtual ~CollisionComponent() = default;
		bool CheckCollision(Rectangle other);
		bool GetColliding() { return m_IsColliding; }
		std::string GetTag() { return m_Tag; }
		std::string GetLastCollidedTag() { return m_CollidingTag; }
		static void ClearCollisions() { m_Colliders.clear(); }
		void Render() override;
		void Update(float deltaTime) override;
		void Update(float posX, float posY);
		void SetActive(bool active) { m_Active = active; }
	private:
		void CheckCollisionWithTags();
		bool m_IsColliding = false;
		bool m_Active = true;
		int m_TextureOffset;
		std::string m_Tag;
		std::string m_CollidingTag;
		Rectangle m_Rect;
		static std::multimap<std::string, CollisionComponent*> m_Colliders;
		std::vector<std::string> m_CollidingTags;
	};
}

