#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Math.h"

class Entity {
protected:
	Vector2f pos;
	SDL_Rect currFrame;
	SDL_Texture* texture;
public:
	Entity();
	Entity(Vector2f p_pos, SDL_Texture* p_texture);
	Vector2f& getPos();
	SDL_Texture* getTexture();
	void setTexture(SDL_Texture* p_texture);
	SDL_Rect getCurrentFrame();
};
