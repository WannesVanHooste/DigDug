#pragma once
#include "GameObject.h"

//implemented as seen in the lesson
//http://gameprogrammingpatterns.com/observer.html

namespace dae {
	class Observer
	{
	public:
		virtual ~Observer() {}
		virtual void onNotify(const GameObject& gameObject, const std::string& event) = 0;
	};

	class Subject {
	public:
		void notify(const GameObject& gameObject, const std::string& event)
		{
			for (unsigned int i = 0; i < m_observers.size(); i++)
			{
				m_observers[i]->onNotify(gameObject, event);
			}
		}
		void addObserver(const std::shared_ptr<Observer>& observer)
		{
			m_observers.push_back(observer);
		}
	private:
		std::vector<std::shared_ptr<Observer>> m_observers;
	};
}

