#pragma once
#include "SDL.h"

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	// Window created by SDL
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	
	// Game should continue to run
	bool mIsRunning;
	int mPaddleDir;
	Uint32 mTicksCount;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
};