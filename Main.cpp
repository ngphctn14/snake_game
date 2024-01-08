#include <iostream>
#include <string>
#include <SDL_ttf.h>
#include <windows.h>

#include "RenderWindow.h"
#include "Entity.h"
#include "Snake.h"
#include "Food.h"
#include "Resolution.h"

constexpr float FPS = 10;
constexpr float FRAME_TIME = 1000.0f / FPS;

void clean(SDL_Texture*);

int main(int argc, char* argv[]) {
	RenderWindow window = RenderWindow("Snake Game", Resolution::WIDTH, Resolution::HEIGHT);

	SDL_Texture* snakeHead = window.loadTexture("res/head.png");
	SDL_Texture* snakeSkin = window.loadTexture("res/segment.jpg");
	SDL_Texture* snakeTail = window.loadTexture("res/tail.png");
	SDL_Texture* gameOverScreen = window.loadTexture("res/game_over.png");
	SDL_Texture* startScreen = window.loadTexture("res/start.png");
	SDL_Texture* background = window.loadTexture("res/background.jpg");
	SDL_Texture* foodTexture = window.loadTexture("res/food.png");

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("res/SVN-MoneyGame.ttf", 20);
	SDL_Color Black = { 0, 0, 0 };

	SDL_Surface* surfacePoints = NULL;
	SDL_Texture* message = NULL;

	Snake snake = Snake(Vector2f(300, 300), snakeHead, snakeSkin, snakeTail);
	Food food = Food(Vector2f(500, 300), foodTexture);

	SDL_Event e;
	bool quit = false, flag = false, start = false, grown = false;
	Uint32 currentTime = 0, deltaTime = 0;
	while (!quit) {
		currentTime = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				if (!start && e.key.keysym.sym == SDLK_SPACE) {
					snake.setDead(true);
					start = true;
				}
				if (snake.isDead()) {
					if (e.key.keysym.sym == SDLK_SPACE) {
						snake = Snake(Vector2f(300, 300), snakeHead, snakeSkin, snakeTail);
						food = Food(Vector2f(500, 300), foodTexture);
						flag = false;
					}
				}
				else {
					snake.getInput(e);
					flag = true;
				}
			}
		}
		window.clear();
		if (!start) {
			window.render(startScreen);
		}
		if (!snake.isDead() && start) {
			grown = false;
			window.render(background);
	
			surfacePoints = TTF_RenderText_Solid(font, "Points: ", Black);
			message = SDL_CreateTextureFromSurface(window.getRenderer(), surfacePoints);
			window.render(message, 0, 0, 150, 50);

			SDL_FreeSurface(surfacePoints);
			clean(message);

			surfacePoints = TTF_RenderText_Solid(font, (std::to_string(snake.getPoints()).c_str()), Black);
			message = SDL_CreateTextureFromSurface(window.getRenderer(), surfacePoints);
			window.render(message, 150, 0, 40, 50);

			SDL_FreeSurface(surfacePoints);
			clean(message);

			if (flag)
				snake.update();
			if (snake.getSnakeSegments().front().getCurrentFrame().x == food.getCurrentFrame().x && snake.getSnakeSegments().front().getCurrentFrame().y == food.getCurrentFrame().y) {
				do {
					food.update();
				} while (food.collisionWithSnakeSegments(snake));
				grown = true;
			}
			window.render(food);
			for (int i = 0; i < snake.getSnakeSegments().size(); i++) {
				if (i == 0)
					window.renderSnake(snake.getSnakeSegments()[i], snake.getHeadAngle());
				else if (i == snake.getSnakeSegments().size() - 1)
					window.renderSnake(snake.getSnakeSegments()[i], snake.getTailAngle());
				else
					window.render(snake.getSnakeSegments()[i]);
			}
			if (grown)
				snake.grow();
		}
		else if (snake.isDead() && start) {
			window.render(gameOverScreen);
		}
		window.display();
		deltaTime = SDL_GetTicks() - currentTime;
		if (deltaTime < FRAME_TIME)
			SDL_Delay(static_cast<Uint32>(FRAME_TIME) - deltaTime);
	}
	TTF_CloseFont(font);
	SDL_FreeSurface(surfacePoints);
	clean(message);
	clean(snakeHead);
	clean(snakeSkin);
	clean(snakeTail);
	clean(gameOverScreen);
	clean(startScreen);
	clean(background);
	clean(foodTexture);
	TTF_Quit();
	return 0;
}

void clean(SDL_Texture* texture) {
	SDL_DestroyTexture(texture);
	texture = NULL;
}
