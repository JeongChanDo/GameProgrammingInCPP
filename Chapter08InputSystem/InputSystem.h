#pragma once
#include <SDL_scancode.h>
#include <SDL_gamecontroller.h>
#include <SDL_mouse.h>
#include "Math.h"

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

// Ű���� �Է� ����
class KeyboardState
{
public:
	//friend so inputsystem can easily update it
	friend class InputSystem;
	// get just boolean true/false of key
	bool GetKeyValue(SDL_Scancode keyCode) const;
	//get state based pm cirremt and previus frame
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

// ���콺 �Է� ����
class MouseState
{
public:
	friend class InputSystem;

	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;

private:
	Vector2 mMousePos;
	Vector2 mScrollWheel;
	//store button data
	Uint32 mCurrButtons;
	Uint32 mPrevButtons;
	// are we in relative mouse mode
	bool mIsRelative;
};



//��Ʈ�ѷ� �Է� 

//�Է� ���� ���� �����ϴ� ����
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
};

class InputSystem
{
public:
	bool Initialize();
	void Shutdown();

	//SDL pollevents ���� ������ ȣ��
	void PrepareForUpdate();
	//SDL poll events ���� ���� ȣ��
	void Update();
	// ��ǲ�ý��ۿ��� sdl �̺�Ʈ ó���� ȣ��
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }
	void SetRelativeMouseMode(bool value);
private:
	InputState mState;
};