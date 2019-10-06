#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

//THIS CLASS IS BASED OFF THE OVERLORD INPUT MANAGER. I DO NOT TAKE CREDIT FOR THIS
bool dae::InputManager::ProcessInput() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}
	Update();
	//for(auto elements: m_Commands) {
	//	if(IsActionTriggered(elements.first)) {
	//		elements.second->Execute();
	//	}
	//}

	return m_Playing;
}

dae::InputManager::~InputManager() {
	if (m_pKeyboardState0 != nullptr)
	{
		delete[] m_pKeyboardState0;
		delete[] m_pKeyboardState1;

		m_pKeyboardState0 = nullptr;
		m_pKeyboardState1 = nullptr;
		m_pCurrKeyboardState = nullptr;
		m_pOldKeyboardState = nullptr;
	}
}

void dae::InputManager::ClearAllActionsAndCommands() {
	m_Commands.clear();
	m_InputActions.clear();
}

void dae::InputManager::Initialize() {
	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];

	GetKeyboardState(m_pKeyboardState0);
	GetKeyboardState(m_pKeyboardState1);

	RefreshControllers();
	m_IsInitialized = true;
}

void dae::InputManager::QuitGame() {
	m_Playing = false;
}

bool dae::InputManager::SetCommand(int inputId, const std::shared_ptr<Command>& command) {
	auto it = m_InputActions.find(inputId);
	if (it == m_InputActions.end()) return false;

	m_Commands[inputId] = command;

	return true;
}

bool dae::InputManager::AddInputAction(InputAction action)
{
	//if the ID is not taken yet add the action

	//for(auto element : m_InputActions) {
	//	if(element.second.ActionID == action.ActionID) {
	//		return false;
	//	}
	//}

	auto it = m_InputActions.find(action.ActionID);
	if (it != m_InputActions.end()) return false;

	m_InputActions[action.ActionID] = action;



	return true;
}

bool dae::InputManager::IsActionTriggered(int actionID)
{
	return m_InputActions[actionID].IsTriggered;
}

std::shared_ptr<dae::Command> dae::InputManager::GetCommand(int inputId) {
	auto it = m_InputActions.find(inputId);
	if (it == m_InputActions.end()) return nullptr;

	return m_Commands[inputId];
}

void dae::InputManager::RefreshControllers()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

void dae::InputManager::UpdateGamepadStates()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		m_OldGamepadState[i] = m_CurrGamepadState[i];

		const DWORD dwResult = XInputGetState(i, &m_CurrGamepadState[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

bool dae::InputManager::UpdateKeyboardStates()
{
	//Get Current KeyboardState and set Old KeyboardState
	BOOL getKeyboardResult;
	if (m_KeyboardState0Active)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

	return getKeyboardResult > 0;
}

void dae::InputManager::Update()
{

	UpdateKeyboardStates();
	UpdateGamepadStates();

	//Reset previous InputAction States
	for (auto it = m_InputActions.begin(); it != m_InputActions.end(); ++it)
	{
		auto currAction = &(it->second);

		//Reset the previous state before updating/checking the new state
		currAction->IsTriggered = false;

		switch (currAction->KeyState)
		{
		case KeyState::Pressed:
			if (currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
				if (!IsKeyDown(currAction->KeyboardCode, true) && IsKeyDown(currAction->KeyboardCode))
					currAction->IsTriggered = true;

			if (!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
				if (!IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
					currAction->IsTriggered = true;

			break;

		case KeyState::Down:
			if (currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
				if (IsKeyDown(currAction->KeyboardCode, true) && IsKeyDown(currAction->KeyboardCode))
					currAction->IsTriggered = true;

			if (!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
				if (IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
					currAction->IsTriggered = true;
			break;

		case KeyState::Released:
			if (currAction->KeyboardCode > 0x07 && currAction->KeyboardCode <= 0xFE)
				if (IsKeyDown(currAction->KeyboardCode, true) && !IsKeyDown(currAction->KeyboardCode))
					currAction->IsTriggered = true;

			if (!currAction->IsTriggered && currAction->GamepadButtonCode > 0x0 && currAction->GamepadButtonCode <= 0x8000)
				if (IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex, true) && !IsButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
					currAction->IsTriggered = true;
			break;
		}
	}
}

bool dae::InputManager::IsKeyDown(int key, bool previousFrame)
{
	if (!m_pCurrKeyboardState || !m_pOldKeyboardState)
		return false;

	if (key > 0x07 && key <= 0xFE)
	{
		if (previousFrame)
			return (m_pOldKeyboardState[key] & 0xF0) != 0;
		else
			return (m_pCurrKeyboardState[key] & 0xF0) != 0;
	}
	return false;
}

bool dae::InputManager::IsButtonDown(WORD button, GamepadIndex playerIndex, bool previousFrame)
{
	if (button > 0x0000 && button <= 0x8000)
	{
		if (!m_ConnectedGamepads[playerIndex])
			return false;

		if (previousFrame)
			return (m_OldGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
		return (m_CurrGamepadState[playerIndex].Gamepad.wButtons&button) != 0;
	}
	return false;
}
