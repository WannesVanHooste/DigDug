#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SoundEffect.h"

namespace dae {
	class SoundEffect;
	class ButtonManager;
	class StartScene final:public Scene
	{
	public:
		StartScene();
		~StartScene() = default;

		StartScene(const StartScene& other) = delete;
		StartScene(StartScene&& other) noexcept = delete;
		StartScene& operator=(const StartScene& other) = delete;
		StartScene& operator=(StartScene&& other) noexcept = delete;
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
	};
}

