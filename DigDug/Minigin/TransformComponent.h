#pragma once
#include "Component.h"
#include "Vector3.h"

namespace dae
{
	class TransformComponent final : public Component
	{
		Vector3 m_Position;
	public:
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
		virtual ~TransformComponent() = default;
		TransformComponent();

		const Vector3& GetPosition() const { return m_Position; }
		void Translate(float x, float y, float z);
		void SetPosition(float x, float y, float z);
	protected:
		void Update(float deltaTime) override;
		void Render() override;
	};
}

