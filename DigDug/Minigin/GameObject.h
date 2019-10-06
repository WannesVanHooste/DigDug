#pragma once
#include <memory>

#include "SceneObject.h"

namespace dae
{
	class Component;
	class TransformComponent;

	class GameObject final : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		TransformComponent* GetTransform() const { return m_pTransform; }
		void AddComponent(Component* pComp);
		void RemoveComponent(Component* pComp);

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


		template <class T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}

			return nullptr;
		}
	private:
		TransformComponent* m_pTransform;
		std::vector<Component*> m_pComponents;
	};
}
