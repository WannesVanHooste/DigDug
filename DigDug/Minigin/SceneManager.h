#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//scenemanager based on the overlord engine

		void AddScene(const std::shared_ptr<Scene>& pScene);
		void RemoveScene(const std::shared_ptr<Scene>& pScene);
		void NextScene();
		void PreviousScene();
		std::string GetLastActiveScene() { return m_LastActiveScene; }
		std::shared_ptr<Scene> GetActiveScene() const { return m_ActiveScene; }
		void SetActivateScene(const std::string& sceneName);

		void Initialize();
		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::string m_LastActiveScene = "0";
		std::shared_ptr<Scene> m_ActiveScene, m_NewActiveScene;
	};

}
