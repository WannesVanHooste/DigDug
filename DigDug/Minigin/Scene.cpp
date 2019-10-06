#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

void dae::Scene::RootInitialize() {
	Initialize();
}
void dae::Scene::RootUpdate(float deltaTime) {
	for (auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}
	Update(deltaTime);
}
void dae::Scene::RootRender() {
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
	Render();
}

std::string dae::Scene::GetSceneName() {
	return m_Name;
}

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

dae::Scene::~Scene() = default;

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}


