#pragma once

typedef unsigned char UInt8;

class InputManager {
	public:
	static InputManager* GetCurrentManager();

	InputManager(const InputManager&) = delete;

	enum class Keys {
		RightArrow = 1073741903,
		LeftArrow = 1073741904,
		DownArrow = 1073741905,
		UpArrow = 1073741906
	};

	bool GetKeyState(Keys targetKey);

	private:
	InputManager();
	~InputManager();

	void UpdateKeyStates();

	friend class GameManager;

	const UInt8* KeyStates;

	static InputManager* currentManager;
};