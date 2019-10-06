#pragma once
#include "Scene.h"
#include "GameObject.h"


namespace dae {
	class VersusScene :
		public Scene
	{
	public:
		VersusScene();
		~VersusScene() = default;
		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) noexcept = delete;
		VersusScene& operator=(const VersusScene& other) = delete;
		VersusScene& operator=(VersusScene&& other) noexcept = delete;

		void ReInitialize();
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

	private:
		int m_Level = 1;
	};
}

