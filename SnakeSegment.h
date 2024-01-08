#pragma once

#include "Entity.h"

class SnakeSegment : public Entity {
private:
public:
	SnakeSegment(Vector2f p_pos, SDL_Texture* p_texture);
	void setCurrFrame(int x, int y);
};
