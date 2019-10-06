#include "pch.h"
#include "AIComponent.h"
#include "DigDugConditions.h"
#include "DigDugActions.h"
#include "PointsManager.h"
#include "TransformComponent.h"
#include "MapComponent.h"
#include "SpriteComponent.h"
#include "cmath"
#include "AStarPathfinder.h"
#include "Heuristics.h"

int dae::AIComponent::m_index = 0;

dae::AIComponent::AIComponent()
{
	State* idle = new State{};
	State* run = new State{};
	State* inflating = new State{};
	State* deflating = new State{};
	State* dead = new State{};
	State* hitByRock = new State{};

	idle->AddTransition(std::make_shared<Transition>( std::make_shared<InflateCondition>(),inflating ));
	idle->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	idle->AddTransition(std::make_shared<Transition>(std::make_shared<RunCondition>(), run));
	idle->AddActions(std::make_shared<IdleAction>());

	run->AddTransition(std::make_shared<Transition>(std::make_shared<UpdatePathCondition>(), run));
	run->AddTransition(std::make_shared<Transition>(std::make_shared<InflateCondition>(), inflating));
	run->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	run->AddTransition(std::make_shared<Transition>(std::make_shared<TurnIdleCondition>(), idle));
	run->AddEntryActions(std::make_shared<CreatePathAction>());
	run->AddActions(std::make_shared<RunToPlayerAction>());

	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<DeflateCondition>(),deflating ));
	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<DeadCondition>(), dead ));
	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	inflating->AddActions(std::make_shared<InflateAction>());

	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<IdleCondition>(), idle ));
	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<InflateCondition>(), inflating ));
	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	deflating->AddActions(std::make_shared<DeflateAction>());

	dead->AddActions(std::make_shared<DeadAction>());
	hitByRock->AddActions(std::make_shared<RockAction>());
	CalculateGraph();
	//m_pStateMachine = std::make_shared<StateMachine>( std::vector<State*>{idle, inflating, deflating, dead}, idle,m_index );
	m_pStateMachine = new StateMachine{ std::vector<State*>{idle, inflating, deflating, dead, hitByRock,run}, idle,m_index };
	++m_index;
}

dae::AIComponent::~AIComponent() {
	if (m_pStateMachine != nullptr)
		delete m_pStateMachine;
}

void dae::AIComponent::Update(float deltaTime) {
	if (!m_IsDead)
	{
		m_pStateMachine->Update(deltaTime);
	}
}

void dae::AIComponent::Render() {
	
}

void dae::AIComponent::Dead() {
	m_IsDead = true;
	m_pGameObject->GetComponent<SpriteComponent>()->StopRender(true);
	m_pGameObject->GetComponent<CollisionComponent>()->SetActive(false);
	CalculateScore();
}

void dae::AIComponent::DeadByRock(float deltaTime) {
	m_AccuSec += deltaTime;
	m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 0, 5, 6, 2);
	if(m_AccuSec >= m_DeadTime) {
		m_IsDead = true;
		m_pGameObject->GetComponent<SpriteComponent>()->StopRender(true);
		m_pGameObject->GetComponent<CollisionComponent>()->SetActive(false);
		PointsManager::GetInstance().AddPoints(1000);
	}
}

void dae::AIComponent::CalculateScore() {
	float yPos = m_pGameObject->GetTransform()->GetPosition().y;
	if (yPos <= 192) {
		PointsManager::GetInstance().AddPoints(400);
	}
	else if (yPos > 192 && yPos <= 320) {
		PointsManager::GetInstance().AddPoints(600);
	}
	else if (yPos > 320 && yPos <= 448) {
		PointsManager::GetInstance().AddPoints(800);
	}
	else if (yPos > 448 && yPos <= 576) {
		PointsManager::GetInstance().AddPoints(1000);
	}
}

void dae::AIComponent::CalculateGraph() {
	m_Graph.clear();
	auto blocks = MapComponent::GetBlocks();
	for(auto element : blocks) {
		auto node = std::make_shared<Node>(Vector2{ element->position.x, element->position.y });
		node->SetWalkable(true); // everything made walkable to avoid ghost mode hassle
		m_Graph.push_back(node);
	}

	for(unsigned int i{0}; i < m_Graph.size(); ++i) {
		//left connection
		if(i - 1 >= 0 && (i - 1) / m_Cols == i / m_Cols) {
			m_Graph[i]->AddConnection(m_Graph[i - 1].get());
		}
		//right connection
		if (i + 1 < m_Graph.size() && (i + 1) / m_Cols == i / m_Cols) {
			m_Graph[i]->AddConnection(m_Graph[i + 1].get());
		}
		//up connection
		if(int(i - m_Cols) >= 0) {
			m_Graph[i]->AddConnection(m_Graph[i - m_Cols].get());
		}
		//down connection
		if (int(i + m_Cols) < int(m_Graph.size())) {
			m_Graph[i]->AddConnection(m_Graph[i + m_Cols].get());
		}
	}
}

void dae::AIComponent::CalculatePath() {
	m_Path = AStarPathfinder::FindPath(m_Graph[GetEnemyPlayerIndex().first].get(), m_Graph[GetEnemyPlayerIndex().second].get(), Heuristic::Euclidean);
	m_PathIndex = 0;
}

void dae::AIComponent::Idle() {
	int x = int(m_pGameObject->GetTransform()->GetPosition().x) / m_GridSize;
	int y = int(m_pGameObject->GetTransform()->GetPosition().y - 64) / m_GridSize;

	if (!MapComponent::GetBlocks()[y * m_Cols + x]->isPassed && (y * m_Cols + x) >13 ) {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2, 4, 1, 2);
	}
	else {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7,7,0,2,0,2);
	}
}

void dae::AIComponent::RunToPlayer() {
	auto enemyPos = m_pGameObject->GetTransform()->GetPosition();
	if(int(enemyPos.x) != int(m_Path[m_PathIndex].x) || int(enemyPos.y) != int(m_Path[m_PathIndex].y)) {
		//move left-right
		if(enemyPos.y == m_Path[m_PathIndex].y) {
			if(enemyPos.x < m_Path[m_PathIndex].x) {
				m_pGameObject->GetTransform()->Translate(2,0,0);
				DrawCorrectSprite(0);
			}
			else {
				m_pGameObject->GetTransform()->Translate(-2, 0, 0);
				DrawCorrectSprite(1);
			}
		}
		//move up-down
		if(enemyPos.x == m_Path[m_PathIndex].x) {
			if (enemyPos.y < m_Path[m_PathIndex].y) {
				m_pGameObject->GetTransform()->Translate(0, 2, 0);
				DrawCorrectSprite(3);
			}
			else {
				m_pGameObject->GetTransform()->Translate(0, -2, 0);
				DrawCorrectSprite(5);
			}
		}
	}
	else {
		std::cout << "Hey dont skip this\n";
		if ((m_PathIndex + 1) < int(m_Path.size()))
		{
			m_PathIndex += 1;
		}
		else {
			m_UpdatePath = true;
		}
	}
}

void dae::AIComponent::DrawCorrectSprite(int index) {
	int x = int(m_pGameObject->GetTransform()->GetPosition().x) / m_GridSize;
	int y = int(m_pGameObject->GetTransform()->GetPosition().y - 64) / m_GridSize;

	if (!MapComponent::GetBlocks()[y * m_Cols + x]->isPassed && (y * m_Cols + x) > 13) {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2, 4, 1, 2);
		m_pGameObject->GetComponent<CollisionComponent>()->SetActive(false);
	}
	else {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 0, 2, index, 2);
		m_pGameObject->GetComponent<CollisionComponent>()->SetActive(true);
	}
}

std::pair<int, int> dae::AIComponent::GetEnemyPlayerIndex() {
	//enemy index
	int x = int(m_pGameObject->GetTransform()->GetPosition().x) / m_GridSize;
	int y = int(m_pGameObject->GetTransform()->GetPosition().y - 64) / m_GridSize;
	int enemyindex = (y * m_Cols) + x;

	//player index
	Vector3 enemyPos = m_pGameObject->GetTransform()->GetPosition();
	Vector3 player1Pos = Locator::GetPlayerOne()->GetTransform()->GetPosition();
	if(Locator::GetPlayerTwo() != nullptr && Locator::GetPlayerTwo()->GetComponent<CollisionComponent>()->GetTag() != "Enemy") {
		Vector3 player2Pos = Locator::GetPlayerTwo()->GetTransform()->GetPosition();
		float distance1 = sqrt(pow(enemyPos.x - player1Pos.x, 2) + pow(enemyPos.y - player1Pos.y, 2));
		float distance2 = sqrt(pow(enemyPos.x - player2Pos.x, 2) + pow(enemyPos.y - player2Pos.y, 2));
		if(distance1 < distance2) {
			int x1 = int(player1Pos.x) / m_GridSize;
			int y1 = int(player1Pos.y - 64) / m_GridSize;
			auto player1Index = (y1 * m_Cols) + x1;
			return std::make_pair(enemyindex, player1Index);
		}
		else {
			int x2 = int(player2Pos.x) / m_GridSize;
			int y2 = int(player2Pos.y - 64) / m_GridSize;
			auto player2Index = (y2 * m_Cols) + x2;
			return std::make_pair(enemyindex, player2Index);
		}
	}
	else {
		int x1 = int(player1Pos.x) / m_GridSize;
		int y1 = int(player1Pos.y - 64) / m_GridSize;
		auto player1Index = (y1 * m_Cols) + x1;
		return std::make_pair(enemyindex, player1Index);
	}
	//return std::make_pair(0, 0);
}

void dae::AIComponent::Inflate(float deltaTime) {
  	m_AccuSec += deltaTime;
	if (m_AccuSec >= m_CheckTime) {
		++m_InflateStage;
		m_AccuSec = 0;
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
	}
}

void dae::AIComponent::Deflate(float deltaTime) {
	m_AccuSec += deltaTime;
	if (m_AccuSec >= m_CheckTime) {
		--m_InflateStage;
		m_AccuSec = 0;
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
	}
}

