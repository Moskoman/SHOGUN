#pragma once
#include <SDL.h>
#include <string>
#include <stack>
#include "State.h"
#include <GL\glew.h>


using namespace std;

class Game
{
private:
	float dt;
	int frameStart;
	SDL_GLContext context;	

	//aiLogStream logStream;
	State* newState;
	stack<State*> states;
	static Game* instance;
	void CalculateDeltaTime();

public:
	int WIDTH, HEIGHT;

	SDL_Window * window;
	SDL_Renderer* renderer;
			
	Game(string nome, int w, int h);
	~Game();
	void Run();
	SDL_GLContext GetContext();
	void AddState(State* toAdd);
	State* GetState();
	static Game* GetInstance();
	float GetDeltaTime();
};

