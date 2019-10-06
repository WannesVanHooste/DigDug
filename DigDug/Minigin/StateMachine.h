#pragma once

//STATE MACHINE BASED OFF THE GAMEPLAY PROGRAMMING STATE MACHINE

namespace dae {
	class Action {
	public:
		Action() = default;
		virtual ~Action() = default;
		virtual void Invoke(int idx, float deltaTime) = 0;
	};

	class Condition {
	public:
		Condition() = default;
		virtual ~Condition() = default;
		virtual bool Invoke(int idx) = 0;
	};

	class Action;
	class Transition;
	class State final
	{
	public:
		State() = default;
	/*	virtual ~State()
		{
			m_EntryActions.clear();
			m_ExitActions.clear();
			m_Actions.clear();
			m_Transitions.clear();
		}*/

		//--- Run Actions ---
		void RunActions(int index, float deltaTime) const { for (auto a : m_Actions) a->Invoke(index, deltaTime); }; //The actions that should run when active
		void RunEntryActions(int index, float deltaTime) const { for (auto a : m_EntryActions) a->Invoke(index, deltaTime); }; //The action that should run when entering this state
		void RunExitActions(int index, float deltaTime) const { for (auto a : m_ExitActions) a->Invoke(index, deltaTime); }; //The action that should run when exiting this state

		//--- Setters ---
		void AddEntryActions(std::shared_ptr<Action> entryAction)
		{
			m_EntryActions.push_back(entryAction);
		}
		void AddActions(std::shared_ptr<Action> action)
		{
			m_Actions.push_back(action);
		}
		void AddExitActions(std::shared_ptr<Action> exitAction)
		{
			m_ExitActions.push_back(exitAction);
		}
		void AddTransition(std::shared_ptr<Transition> transition)
		{
			m_Transitions.push_back(transition);
		}

		//--- Getters ---
		std::vector<std::shared_ptr<Transition>> GetTransitions() { return m_Transitions; };

	private:
		//--- Datamembers ---
		std::vector<std::shared_ptr<Action>> m_EntryActions = {};
		std::vector<std::shared_ptr<Action>> m_Actions = {};
		std::vector<std::shared_ptr<Action>> m_ExitActions = {};
		std::vector<std::shared_ptr<Transition>> m_Transitions = {};
	};

	class Transition final
	{
	public:
		//--- Constructor & Destructor ---
		Transition(std::shared_ptr<Condition> condition/*, Action* action*/, State* targetState) :
			m_TargetState(targetState), m_Condition(condition)/*, m_Action(action)*/ {}
		Transition()
		{
			m_Condition = {};
			//m_Action = {};
		}

		//--- Functions ---
		bool IsTriggered(int index) const //Triggered when one of the given conditions is true
		{
			auto r = false;
			if (m_Condition != nullptr)
			{
				r |= m_Condition->Invoke(index);
			}
			else
				r = true;
			return r;
		};
		//void RunActions() const { m_Action->Invoke(); };

		//--- Getters ---
		State* GetTargetState() const { return m_TargetState; };

		//--- Setters ---
		void SetTargetState(State* state)
		{
			m_TargetState = state;
		}
		void SetCondition(std::shared_ptr<Condition> conditions)
		{
			m_Condition = conditions;
		}
	/*	void SetAction(Action* actions)
		{
			m_Action = actions;
		}*/

	private:
		State* m_TargetState = {};
		std::shared_ptr<Condition> m_Condition = {};
		//Action* m_Action = {};
	};


	//states have to be normal pointers to avoid infinite call of destructors resulting in memory leaks

	class StateMachine
	{
	public:
		StateMachine(std::vector<State*> states, State* initialState, int index) :
			m_States(states), m_CurrentState(initialState),m_Index(index) {}

		~StateMachine() {
			for (auto element : m_States)
			{
				delete element;
			}
		}

		//--- Functions ---
		void Start();
		void Update(float deltaTime);
	private:
		std::vector<State*> m_States = {};
		State* m_CurrentState = {};
		int m_Index;
	};
}

