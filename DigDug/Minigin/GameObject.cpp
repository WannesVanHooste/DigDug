#include "MiniginPCH.h"
#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"

dae::GameObject::GameObject() 
:m_pTransform(nullptr){
	m_pTransform = new TransformComponent();
	AddComponent(m_pTransform);
}


dae::GameObject::~GameObject() {
	for(unsigned int i{}; i < m_pComponents.size(); ++i) {
		delete m_pComponents[i];
	}
}

void dae::GameObject::Update(float deltaTime) {
	for(auto element: m_pComponents) {
		element->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (auto element : m_pComponents) {
		element->Render();
	}
}

void dae::GameObject::AddComponent(Component* component) {

	for (Component* element : m_pComponents)
	{
		if (element == component)
		{
			std::cout << "Component already excists!!!\n";
			return;
		}
	}

	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(Component* component) {
	auto iterator = std::find(m_pComponents.begin(), m_pComponents.end(), component);

	if (iterator == m_pComponents.end())
	{
		std::cout << "GameObject doesn't have this component!!!\n";
		return;
	}

	m_pComponents.erase(iterator);
	component->m_pGameObject = nullptr;
}
