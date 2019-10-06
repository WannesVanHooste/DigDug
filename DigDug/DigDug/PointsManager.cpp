#include "pch.h"
#include "PointsManager.h"
#include "ResourceManager.h"


dae::PointsManager::PointsManager()
	:m_Points(0)
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	m_Text = std::make_shared<TextComponent>("Score 0", font, Vector3{ 0.0f,0.0f,0.0f });
	m_Text->SetText("Score: 0");
	m_Text->Update(1.0f);
}

