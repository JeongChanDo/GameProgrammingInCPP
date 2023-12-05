#include "InputSystem.h"
#include <SDL.h>
#include <cstring>

bool InputSystem::Initialize()
{
	//keyboard
	// assign curr state pointer
	mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
	// clear prev state memory
	memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

	return true;
}

void InputSystem::PrepareForUpdate()
{
	//copy current state to previous keyboard
	memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrState, SDL_NUM_SCANCODES);
	
	//mouse
	mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
	mState.Mouse.mIsRelative = false;
	mState.Mouse.mScrollWheel = Vector2::Zero;

}

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	return mCurrState[keyCode] == 1;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPrevState[keyCode] == 0)
	{
		if (mCurrState[keyCode] == 0)
		{
			return ENone;
		}
		else
		{
			return EPressed;
		}
	}
	else
	{
		if (mCurrState[keyCode] == 0)
		{
			return EReleased;
		}
		else
		{
			return EHeld;
		}
	}
}

void InputSystem::Shutdown()
{

}

void InputSystem::Update()
{
	// mouse
	int x = 0;
	int y = 0;
	if (mState.Mouse.mIsRelative)
	{
		mState.Mouse.mCurrButtons = SDL_GetRelativeMouseState(&x, &y);
	}
	else
	{
		mState.Mouse.mCurrButtons = SDL_GetMouseState(&x, &y);
	}
	mState.Mouse.mMousePos.x = static_cast<float>(x);
	mState.Mouse.mMousePos.y = static_cast<float>(y);

}

void InputSystem::SetRelativeMouseMode(bool value)
{
	SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
	SDL_SetRelativeMouseMode(set);
	mState.Mouse.mIsRelative = value;
}

void InputSystem::ProcessEvent(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_MOUSEWHEEL:
			mState.Mouse.mScrollWheel = Vector2(
				static_cast<float>(event.wheel.x),
				static_cast<float>(event.wheel.y)
			);
			break;
		default:
			break;
	}
}

bool MouseState::GetButtonValue(int button) const
{
	return (SDL_BUTTON(button) & mCurrButtons) == 1;
}

ButtonState MouseState::GetButtonState(int button) const
{
	int mask = SDL_BUTTON(button);
	if ((mask & mPrevButtons) == 0)
	{
		if ((mask & mCurrButtons) == 0)
		{
			return ENone;
		}
		else
		{
			return EPressed;
		}
	}
	else
	{
		if ((mask & mCurrButtons) == 0)
		{
			return EReleased;
		}
		else
		{
			return EHeld;
		}
	}
}
