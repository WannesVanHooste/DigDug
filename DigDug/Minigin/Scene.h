#pragma once
#include "SceneManager.h"
#include "algorithm"

namespace dae
{
	class SceneObject;
	class Scene
	{

	public:

		void Add(const std::shared_ptr<SceneObject>& object);
		void Remove(const std::shared_ptr<SceneObject>& object) { m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end()); }

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		void RootInitialize();
		void RootUpdate(float deltaTime);
		void RootRender();
		void ClearScene() { m_Objects.clear(); };

		std::string GetSceneName();
		Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private: 
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::string m_Name{};
	};

}
