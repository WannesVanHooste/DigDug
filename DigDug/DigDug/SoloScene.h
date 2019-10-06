#pragma once
#include "Scene.h"
#include "GameObject.h"

namespace dae {
	class SoloScene final:public Scene
	{
	public:
		SoloScene();
		~SoloScene() = default;
		SoloScene(const SoloScene& other) = delete;
		SoloScene(SoloScene&& other) noexcept = delete;
		SoloScene& operator=(const SoloScene& other) = delete;
		SoloScene& operator=(SoloScene&& other) noexcept = delete;

		void ReInitialize();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		int m_Level = 1;
	};
}

