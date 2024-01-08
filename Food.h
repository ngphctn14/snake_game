#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <random>

#include "Entity.h"
#include "Snake.h"

class Food : public Entity {
public:
	Food(Vector2f p_pos, SDL_Texture* p_texture);
	void update();
	bool collisionWithSnakeSegments(Snake& snake);
};
