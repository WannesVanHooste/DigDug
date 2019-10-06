#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename)
	:m_Texture{ ResourceManager::GetInstance().LoadTexture(filename) }
    ,m_IsWidthHeight{false}
    ,m_IsSourceRect{false}
    ,m_Height{0}
    ,m_Width{0}
{

}

dae::TextureComponent::TextureComponent(const std::string& filename, float width, float height)
	: m_Texture{ ResourceManager::GetInstance().LoadTexture(filename) }
    , m_IsWidthHeight{ true }
    ,m_IsSourceRect{false}
	, m_Height{ height }
	, m_Width{ width }
{
	
}

dae::TextureComponent::TextureComponent(const std::string& filename, float width, float height, SDL_Rect sourceRect)
	: m_Texture{ ResourceManager::GetInstance().LoadTexture(filename) }
	, m_IsWidthHeight{ true }
	, m_IsSourceRect{ true }
	, m_Height{ height }
	, m_Width{ width }
    , m_SourceRect{ sourceRect } {
	
}

dae::TextureComponent::TextureComponent(const std::shared_ptr<Texture2D>& texture)
	:m_Texture(std::move(texture))
,m_IsWidthHeight(false)
,m_IsSourceRect(false)
{
	
}

void dae::TextureComponent::Render() {
	auto pos = m_pGameObject->GetTransform()->GetPosition();
	if(m_IsSourceRect) {
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height, m_SourceRect);
	}
	else if (m_IsWidthHeight)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height);
	}
	else if(!m_IsWidthHeight) {
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextureComponent::Render(Vector3 pos) const{
	if (m_IsSourceRect) {
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height, m_SourceRect);
	}
	else if (m_IsWidthHeight)
	{
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Width, m_Height);
	}
	else if (!m_IsWidthHeight) {
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
void dae::TextureComponent::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
}
