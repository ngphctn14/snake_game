#include "Food.h"

Food::Food(Vector2f p_pos, SDL_Texture* p_texture) : Entity(p_pos, p_texture) {}

void Food::update() {
	Vector2f pos(currFrame.x, currFrame.y);

	// wtf is this? only for a randomly generated number i love c++ so much omg
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<Uint32> distr(0, 18);

	do {
		currFrame.x = distr(generator) * 50;
		currFrame.y = distr(generator) * 50;
		if (currFrame.y <= 0)
			currFrame.y = 50;
		if (currFrame.y >= 900)
			currFrame.y = 850;
		if (currFrame.x >= 900)
			currFrame.x = 850;
	} while (pos.x == currFrame.x && pos.y == currFrame.y);
}

bool Food::collisionWithSnakeSegments(Snake& snake) {
	Vector2f pos(currFrame.x, currFrame.y);
	for (int i = 1; i < snake.getSnakeSegments().size(); i++) {
		if (pos.x == snake.getSnakeSegments()[i].getCurrentFrame().x && pos.y == snake.getSnakeSegments()[i].getCurrentFrame().y)
			return true;
	}
	return false;
}