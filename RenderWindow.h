#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"

class RenderWindow {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	RenderWindow(const char* title, int w, int h);
	SDL_Texture* loadTexture(const char* filePath);
	SDL_Renderer* getRenderer();
	void clear();
	void renderSnake(Entity& entity, int angle);
	void render(Entity& entity);
	void render(SDL_Texture* texture);
	void render(SDL_Texture* texture, Uint32 x, Uint32 y, Uint32 w, Uint32 h);
	void display();
	~RenderWindow();
};
