#include "MiniginPCH.h"
#include "StateMachine.h"


void dae::StateMachine::Start()
{}

void dae::StateMachine::Update(float deltaTime)
{
	//Check all transitions for current state and see if we need to transition!
	auto transitions = m_CurrentState->GetTransitions();
	auto transitionTriggered = false;
	std::shared_ptr<Transition> triggeredTransition = {};
	for (auto trans : transitions)
	{
		transitionTriggered = trans->IsTriggered(m_Index);
		if (transitionTriggered)
		{
			triggeredTransition = trans;
			break;
		}
	}

	//If a transition triggered, perform the switching
	if (transitionTriggered)
	{
		//Get target state
		auto targetState = triggeredTransition->GetTargetState();

		//End current state, do transition actions and enter the new state
		m_CurrentState->RunExitActions(m_Index,deltaTime);
		targetState->RunEntryActions(m_Index,deltaTime);

		//Switch
		m_CurrentState = targetState;
	}
	else //Else continue performing the current actions
	{
		m_CurrentState->RunActions(m_Index, deltaTime);
	}
}
