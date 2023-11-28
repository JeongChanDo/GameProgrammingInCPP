#include "Game.h"

const int thickness = 15;
const float paddleH = 100.0f;

Game::Game()
	:mWindow(nullptr)
	,mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, mPaddleDir(0)
{

}

bool Game::Initialize()
{
	// param is bitwise-or of all subsystem Flags
	// SDL INIT VIDEO create a window, interfacing with opengl, and 2d graphics
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
		return false;
	}

	/*
		window creation flags 
		SDL_WINDOW_FULLSCREEN
		SDL_WINDOW_FULLSCREEN_DESKTOP
		SDL_WINDOW_OPENGL
		SDL_WINDOW_RESIZABLE
	*/
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter1)",
		100, //top left x coordinate
		100, //top left y coordinate
		1024, // width of window,
		768, // height of window
		0 // flags(0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
	}

	mPaddlePos.x = 10.f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;
	return true;
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	// while there are still events in the queue
	while (SDL_PollEvent(&event))
	{
		// handle different event types
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	// Get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// if escape is pressed, alose end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	// Update paddle direction based on W/S keys
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}
}

void Game::GenerateOutput()
{
	//draw color to blue
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		//R
		0,		//G
		255,	//B
		255		//A
	);

	//clear back buffer
	SDL_RenderClear(mRenderer);


	//for drawing walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);


	//Draw top wall
	SDL_Rect wall{
		0,
		0,
		1024,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &wall);


	//Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	//Draw right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	//Draw paddle
	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//Draw ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);


	SDL_RenderPresent(mRenderer);
}

void Game::UpdateGame()
{
	// wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// ticks to second from last frame
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	

	// clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	
	// update tick counts
	// SDL_GetTicks() milliseconds elapsed since SDL_Init ccalled
	mTicksCount = SDL_GetTicks();

	// update paddle position based on direction
	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		// Make sure paddle doesn't move off screen
		if (mPaddlePos.y < (paddleH / 2.f + thickness))
		{
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
		{
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
		}
	}
	
	// update ball pos
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// ball, paddle y diff
	float diff = mPaddlePos.y - mBallPos.y;
	// take absolute value of diff
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		diff <= paddleH / 2.0f && // y diff small enough
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && // ball correct x pos
		mBallVel.x < 0.0f // ball moving left
		)
	{
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x <= 0.0f)
	{
		//mIsRunning = false;
		mBallVel.x *= -1.0f;
	}
	else if (mBallPos.x >= (1024.0f - thickness) && mBallVel.x > 0.0f)
	{
		mBallVel.x *= -1.0f;
	}

	//ball hit top wall and check ball moving upward
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f)
	{
		mBallVel.y *= -1;
	}
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f)
	{
		mBallVel.y *= -1;
	}



	
}