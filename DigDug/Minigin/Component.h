#pragma once
#include "GameObject.h"

//class GameObject;

namespace dae
{
	class Component
	{
		friend class GameObject;

	public:
		Component();
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		GameObject* GetGameObject() const{ return m_pGameObject; };


	protected:
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		GameObject* m_pGameObject;
	};
}

