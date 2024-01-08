#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int w, int h) : window(NULL), renderer(NULL) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to create a window. SDL Error: " << SDL_GetError() << '\n';
	}
	else {
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Renderer* RenderWindow::getRenderer() {
	return renderer;
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);
	if (texture == NULL) {
		std::cout << "Failed to load texture. SDL Error: " << SDL_GetError() << '\n';
	}
	return texture;
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void RenderWindow::renderSnake(Entity& entity, int angle) {
	SDL_Rect dest;
	dest.x = entity.getCurrentFrame().x;
	dest.y = entity.getCurrentFrame().y;
	dest.w = entity.getCurrentFrame().w;
	dest.h = entity.getCurrentFrame().h;
	SDL_RenderCopyEx(renderer, entity.getTexture(), NULL, &dest, static_cast<double>(angle), NULL, SDL_FLIP_NONE);
}

void RenderWindow::render(Entity& entity) {
	SDL_Rect dest;
	dest.x = entity.getCurrentFrame().x;
	dest.y = entity.getCurrentFrame().y;
	dest.w = entity.getCurrentFrame().w;
	dest.h = entity.getCurrentFrame().h;
	SDL_RenderCopy(renderer, entity.getTexture(), NULL, &dest);
}

void RenderWindow::render(SDL_Texture* p_texture) {
	SDL_Point size;
	SDL_QueryTexture(p_texture, NULL, NULL, &size.x, &size.y);
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = size.x;
	dest.h = size.y;
	SDL_RenderCopy(renderer, p_texture, NULL, &dest);
}

void RenderWindow::render(SDL_Texture* p_texture, Uint32 x, Uint32 y, Uint32 w, Uint32 h) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;
	SDL_RenderCopy(renderer, p_texture, NULL, &dest);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

RenderWindow::~RenderWindow() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();
}
