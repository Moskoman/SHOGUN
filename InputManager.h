#pragma once
#include <SDL.h>
#include <unordered_map>


class InputManager
{
private:
	bool mouseState[6];
	int mouseUpdate[6];

	bool quitRequested;
	int mouseX;
	int mouseY;
	int updateCounter;
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

public:
	
	InputManager() : quitRequested(false), mouseX(0), mouseY(0), updateCounter(0) {
		for (int i = 0; i < 6; i++)
			mouseState[i] = mouseUpdate[i] = 0;
	}

	~InputManager() {
	}

	static InputManager& GetInstance() {
		static InputManager inputManager;
		return inputManager;
	}

	void Update() {

		SDL_Event event;
		SDL_GetMouseState(&mouseX, &mouseY);
		quitRequested = false;
		updateCounter++;

		// SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
		while (SDL_PollEvent(&event)) {
			// Se o evento for quit, setar a flag para terminação
			if (event.type == SDL_QUIT) {
				quitRequested = true;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			}
			if (!event.key.repeat) {
				if (event.type == SDL_KEYDOWN) {
					keyState[event.key.keysym.sym] = true;
					keyUpdate[event.key.keysym.sym] = updateCounter;
				}
			}
			if (event.type == SDL_KEYUP) {
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
		}
	}

	bool KeyPress(int key) {
		return keyUpdate[key] == updateCounter && keyState[key];

	}

	bool KeyRelease(int key) {
		return keyUpdate[key] == updateCounter && !keyState[key];
	}

	bool IsKeyDown(int key) {
		return  keyState[key];
	}

	bool MousePress(int key) {
		return mouseUpdate[key] == updateCounter && mouseState[key];
	}

	bool MouseRelease(int key) {
		return mouseUpdate[key] == updateCounter && !mouseState[key];
	}

	bool IsMouseDown(int key) {
		return mouseState[key];
	}

	int GetMouseX() {
		return mouseX;
	}

	int GetMouseY() {
		return mouseY;
	}

	bool QuitRequested() {
		return quitRequested;
	}

};

