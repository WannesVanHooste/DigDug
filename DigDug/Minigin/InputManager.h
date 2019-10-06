#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>

namespace dae
{
	enum GamepadIndex : DWORD
	{
		PlayerOne = 0,
		PlayerTwo = 1,
		PlayerThree = 2,
		PlayerFour = 3
	};

	enum KeyState
	{
		Pressed,
		Released,
		Down
	};

	struct InputAction
	{
		InputAction() :
			ActionID(-1),
			KeyState(Pressed),
			KeyboardCode(-1),
			GamepadButtonCode(0),
			PlayerIndex(PlayerOne),
			IsTriggered(false) {}

		InputAction(int actionID, KeyState triggerState = Pressed, int keyboardCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
			ActionID(actionID),
			KeyState(triggerState),
			KeyboardCode(keyboardCode),
			GamepadButtonCode(gamepadButtonCode),
			PlayerIndex(playerIndex),
			IsTriggered(false) {}

		int ActionID; //id of this action
		KeyState KeyState; //pressed,down,up
		int KeyboardCode; //virtual key code
		WORD GamepadButtonCode; //controller codes of XINPUT
		GamepadIndex PlayerIndex; //player
		bool IsTriggered;
	};
	//THIS CLASS IS BASED OFF THE OVERLORD INPUT MANAGER. I DO NOT TAKE CREDIT FOR THIS
		class InputManager final : public Singleton<InputManager>
		{
		public:
			~InputManager();
			void ClearAllActionsAndCommands();
			void Initialize();
			void QuitGame();
			void Update();
			bool ProcessInput();
			bool AddInputAction(InputAction action);
			bool IsActionTriggered(int actionID);
			std::shared_ptr<Command> GetCommand(int inputId);
			void RefreshControllers();
			bool SetCommand(int inputId, const std::shared_ptr<Command>& command);
		private:
			std::map<int, InputAction> m_InputActions;
			std::map<int, std::shared_ptr<Command>> m_Commands;
			//no use of shared pointers because it doesnt work for the "GetKeyboardState function
			BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
			XINPUT_STATE m_OldGamepadState[XUSER_MAX_COUNT], m_CurrGamepadState[XUSER_MAX_COUNT];

			bool m_KeyboardState0Active;
			bool m_IsInitialized;
			bool m_ConnectedGamepads[XUSER_MAX_COUNT];
			bool m_Playing = true;


			void UpdateGamepadStates();
			bool UpdateKeyboardStates();

			bool IsKeyDown(int key, bool previousFrame = false);
			bool IsButtonDown(WORD button, GamepadIndex playerIndex = PlayerOne, bool previousFrame = false);
		};
}
