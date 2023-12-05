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

// 키보드 입력 핼퍼
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

// 마우스 입력 헬퍼
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



//컨트롤러 입력 

//입력 현재 상태 포함하는 래퍼
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

	//SDL pollevents 루프 직전에 호출
	void PrepareForUpdate();
	//SDL poll events 루프 직후 호출
	void Update();
	// 인풋시스템에서 sdl 이벤트 처리시 호출
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }
	void SetRelativeMouseMode(bool value);
private:
	InputState mState;
};