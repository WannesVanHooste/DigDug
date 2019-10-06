#pragma once
#include "Scene.h"
#include "ButtonManager.h"

namespace  dae {
	class EndSceen :
		public Scene
	{
	public:
		EndSceen();
		~EndSceen() = default;
		EndSceen(const EndSceen& other) = delete;
		EndSceen(EndSceen&& other) noexcept = delete;
		EndSceen& operator=(const EndSceen& other) = delete;
		EndSceen& operator=(EndSceen&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	};
}

