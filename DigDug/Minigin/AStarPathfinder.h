#pragma once
#include "Vector3.h"

//Class based off Gameplay Programming

namespace dae {
	//Function pointer type to heuristic function
	typedef float(*Heuristics)(float, float);

	class Connection;
	class Node;
	class AStarPathfinder
	{
	public:
		AStarPathfinder();
		~AStarPathfinder() = default;

		static std::vector<dae::Vector2> FindPath(Node* pStartNode, Node* pEndNode,Heuristics heuristicFunction);
		static void CalculateCosts(Connection* pC, Node* pStartNode, Node* pTargetNode, Heuristics heuristicFunction);
	};
}

