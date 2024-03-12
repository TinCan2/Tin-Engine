#pragma once

typedef unsigned char UInt8;

class InputManager {
	public:
	static InputManager* GetCurrentManager();

	InputManager(const InputManager&) = delete;

	enum class Keys;

	bool GetKeyState(Keys targetKey);

	private:
	InputManager();
	~InputManager();

	void UpdateKeyStates();

	friend class GameManager;

	const UInt8* KeyStates;

	static InputManager* currentManager;
};