#pragma once
#include "Vector3.h"
#include "Connection.h"

//class based off Gameplay Programming
namespace dae {
	class Node
	{
	public:
		Node(const Vector2& position)
			:m_Position(position) {}
		~Node(){
			for (auto element : m_pConnections)
			{
				delete element;
			}
		};

		const Vector2& GetPosition() const { return m_Position; }
		void SetPosition(const Vector2& p) { m_Position = p; }
		bool IsWalkable() const { return m_IsWalkable; }
		void SetWalkable(bool state) { m_IsWalkable = state; }

		void AddConnection(Node* m_pNode)
		{
			Connection* newConnection = new Connection(this, m_pNode);
			m_pConnections.push_back(newConnection);
		}

		std::vector<Connection*> GetConnections() const
		{
			return m_pConnections;
		}

		void ResetCosts()
		{
			for (auto pC : m_pConnections)
			{
				pC->ResetCosts();
			}
		}

	private:
		//--- Datamembers ---
		std::vector<Connection*> m_pConnections;
		Vector2 m_Position = Vector2{0,0};
		bool m_IsWalkable = true;
	};
}

