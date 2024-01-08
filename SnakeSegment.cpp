#include "SnakeSegment.h"

SnakeSegment::SnakeSegment(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture) {
}

void SnakeSegment::setCurrFrame(int x, int y) {
	currFrame.x = x;
	currFrame.y = y;
}
