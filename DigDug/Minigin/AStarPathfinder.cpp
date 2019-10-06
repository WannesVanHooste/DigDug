#include "MiniginPCH.h"
#include "AStarPathfinder.h"
#include "Connection.h"
#include "Node.h"
#include <algorithm>

//Class from gameplay programming

std::vector<dae::Vector2> dae::AStarPathfinder::FindPath(Node* pStartNode,Node* pEndNode, Heuristics heuristicFunction) {


	std::vector<Vector2> vPath;


	std::vector<Connection*> openList;
	std::vector<Connection*> closedList;

	Connection* pCurrentConnection = nullptr;


	for (auto c : pStartNode->GetConnections())
	{

		CalculateCosts(c, pStartNode, pEndNode, heuristicFunction);

		openList.push_back(c);
	}

	while (!openList.empty())
	{
		float fcost = 100000;
		for (auto element : openList) {
			if (element->GetFCost() < fcost) {
				fcost = element->GetFCost();
				pCurrentConnection = element;
			}
		}

		openList.erase(std::remove(openList.begin(), openList.end(), pCurrentConnection), openList.end());

		closedList.push_back(pCurrentConnection);

		std::vector<Connection*> vpConnections = {};
		for (auto element : pCurrentConnection->GetEndNode()->GetConnections()) {
			vpConnections.push_back(element);
		}

		auto isEnd = [pEndNode](Connection* element) { return element->GetEndNode() == pEndNode; };

		std::vector<Connection*>::iterator result = std::find_if(vpConnections.begin(), vpConnections.end(), isEnd);

		if (result != vpConnections.end())
		{

			(*result)->SetHeadConnection(pCurrentConnection);

			pCurrentConnection = *result;

			break;
		}
		else
		{

			for (auto pC : vpConnections)
			{
				if (std::find(closedList.begin(), closedList.end(), pC) != closedList.end()) {
					continue;
				}
				else if (std::find(openList.begin(), openList.end(), pC) != openList.end()) {
					continue;
				}
				else {
					pC->SetHeadConnection(pCurrentConnection);
					CalculateCosts(pC, pStartNode, pEndNode, heuristicFunction);
					openList.push_back(pC);
				}
			}
		}
	}

	while (pCurrentConnection->GetStartNode() != pStartNode)
	{
		vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());

		pCurrentConnection = pCurrentConnection->GetHeadConnection();
	}

	vPath.push_back(pCurrentConnection->GetEndNode()->GetPosition());
	vPath.push_back(pStartNode->GetPosition());

	std::reverse(vPath.begin(), vPath.end());

	return vPath;
}

void dae::AStarPathfinder::CalculateCosts(Connection* pC, Node* pStartNode,
	Node* pTargetNode, Heuristics heuristicFunction) {
	float currentGCost = 0;
	if (pC->GetHeadConnection() != nullptr)
		currentGCost = pC->GetHeadConnection()->GetGCost();

	Vector2 parentPos = pStartNode->GetPosition();
	if (pC->GetHeadConnection() != nullptr)
		parentPos = pC->GetHeadConnection()->GetStartNode()->GetPosition();

	Vector2 tempV = Vector2{ abs(pC->GetEndNode()->GetPosition().x - parentPos.x), abs(pC->GetEndNode()->GetPosition().y - parentPos.y) };
	float gCost = heuristicFunction(tempV.x, tempV.y);
	pC->SetGCost(currentGCost + gCost);

	tempV = Vector2{ abs(pC->GetEndNode()->GetPosition().x - pTargetNode->GetPosition().x), abs(pC->GetEndNode()->GetPosition().y - pTargetNode->GetPosition().y) };
	float hCost = heuristicFunction(tempV.x, tempV.y);
	pC->SetHCost(hCost);
}
