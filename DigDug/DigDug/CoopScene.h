#pragma once
#include "Scene.h"
#include "GameObject.h"

namespace dae {
	class CoopScene :
		public Scene
	{
	public:
		CoopScene();
		~CoopScene() = default;
		CoopScene(const CoopScene& other) = delete;
		CoopScene(CoopScene&& other) noexcept = delete;
		CoopScene& operator=(const CoopScene& other) = delete;
		CoopScene& operator=(CoopScene&& other) noexcept = delete;

		void ReInitialize();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		int m_Level = 1;
	};
}

