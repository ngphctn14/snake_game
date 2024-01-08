#include "Snake.h"

Snake::Snake() {}

Snake::Snake(Vector2f p_pos, SDL_Texture* p_texture, SDL_Texture* p_segmentTexture, SDL_Texture* p_tailTexture) : Entity(p_pos, p_texture), 
		xSpeed(50), ySpeed(50), points(0), dead(false), segmentTexture(p_segmentTexture), tailTexture(p_tailTexture), angle(0), lastTime(0), cooldown(7) {
	segments.push_back(SnakeSegment(Vector2f(currFrame.x, currFrame.y), texture));
	segments.push_back(SnakeSegment(Vector2f(currFrame.x - 50, currFrame.y), segmentTexture));
	segments.push_back(SnakeSegment(Vector2f(currFrame.x - 100, currFrame.y), segmentTexture));
	segments.push_back(SnakeSegment(Vector2f(currFrame.x - 150, currFrame.y), tailTexture));
	setDirections(RIGHT);
}

void Snake::setDirections(int num) {
	for (int i = 0; i < NUMBER_OF_DIRECTIONS; i++) {
		if (i == num && i != -1)
			headDirections[i] = true;
		else 
			headDirections[i] = false;
	}
}

void Snake::getInput(SDL_Event& e) {

	Uint32 currentTime = SDL_GetTicks();
	Uint32 deltaTime = currentTime - lastTime;

	if (deltaTime < cooldown)
		return;

	switch (e.key.keysym.sym) {
	case SDLK_w:
		if (!headDirections[DOWN]) {
			setDirections(UP);
			angle = 270;
		}
		break;
	case SDLK_s:
		if (!headDirections[UP]) {
			setDirections(DOWN);
			angle = 90;
		}
		break;
	case SDLK_a:
		if (!headDirections[RIGHT]) {
			setDirections(LEFT);
			angle = 180;
		}
		break;
	case SDLK_d:
		if (!headDirections[LEFT]) {
			setDirections(RIGHT);
			angle = 0;
		}
		break;
	default:
		break;
	}

	lastTime = currentTime;
}

void Snake::update() {
	Vector2f lastPos(currFrame.x, currFrame.y);

	for (int i = 1; i < segments.size(); i++) {
		Vector2f lastPos1(segments[i].getCurrentFrame().x, segments[i].getCurrentFrame().y);
		segments[i].setCurrFrame(lastPos.x, lastPos.y);
		lastPos = lastPos1;
	}

	if (currFrame.x <= 0 && headDirections[LEFT]) {
		currFrame.x = Resolution::WIDTH;
	}
	if (currFrame.x >= Resolution::WIDTH - currFrame.w && headDirections[RIGHT]) {
		currFrame.x = -currFrame.w;
	}
	if (currFrame.y <= 50 && headDirections[UP]) {
		currFrame.y = Resolution::HEIGHT;
	}
	if (currFrame.y >= Resolution::HEIGHT - currFrame.h && headDirections[DOWN]) {
		currFrame.y = 0;
	}

	if (headDirections[UP]) {
		ySpeed = ySpeed < 0 ? ySpeed : -ySpeed;
		currFrame.y += ySpeed;
		segments.front().setCurrFrame(currFrame.x, currFrame.y);
	}
	else if (headDirections[DOWN]) {
		ySpeed = ySpeed < 0 ? -ySpeed : ySpeed;
		currFrame.y += ySpeed;
		segments.front().setCurrFrame(currFrame.x, currFrame.y);
	}
	else if (headDirections[LEFT]) {
		xSpeed = xSpeed < 0 ? xSpeed : -xSpeed;
		currFrame.x += xSpeed;
		segments.front().setCurrFrame(currFrame.x, currFrame.y);
	}
	else if (headDirections[RIGHT]) {
		xSpeed = xSpeed < 0 ? -xSpeed : xSpeed;
		currFrame.x += xSpeed;
		segments.front().setCurrFrame(currFrame.x, currFrame.y);
	}

	checkIfDead();
}

std::vector<SnakeSegment> Snake::getSnakeSegments() {
	return segments;
}

void Snake::checkIfDead() {
	for (int i = 1; i < segments.size(); i++) {
		if (segments.front().getCurrentFrame().x == segments[i].getCurrentFrame().x && segments.front().getCurrentFrame().y == segments[i].getCurrentFrame().y) {
			dead = true;
			break;
		}
	}
}

bool Snake::isDead() {
	return dead;
}

void Snake::setDead(bool state) {
	dead = state;
}

int Snake::getHeadAngle() {
	return angle;
}

int Snake::getTailAngle() {
	Vector2f pos1(segments.back().getCurrentFrame().x, segments.back().getCurrentFrame().y);
	Vector2f pos2(segments[segments.size()-2].getCurrentFrame().x, segments[segments.size()-2].getCurrentFrame().y);
	if (pos1.x + 50 == pos2.x && pos1.y == pos2.y)
		return 0;
	else if (pos1.x == pos2.x && pos1.y + 50 == pos2.y)
		return 90;
	else if (pos1.x - 50 == pos2.x && pos1.y == pos2.y)
		return 180;
	else
		return 270;
}

void Snake::grow() {
	Vector2f pos1(segments.back().getCurrentFrame().x, segments.back().getCurrentFrame().y);
	Vector2f pos2(segments[segments.size()-2].getCurrentFrame().x, segments[segments.size()-2].getCurrentFrame().y);
	segments.back().setTexture(segmentTexture);
	if (pos1.x + 50 == pos2.x && pos1.y == pos2.y) {
		segments.push_back(SnakeSegment(Vector2f(pos1.x - 50, pos2.y), tailTexture));
	}
	else if (pos1.x == pos2.x && pos1.y + 50 == pos2.y) {
		segments.push_back(SnakeSegment(Vector2f(pos1.x, pos2.y - 50), tailTexture));
	}
	else if (pos1.x - 50 == pos2.x && pos1.y == pos2.y) {
		segments.push_back(SnakeSegment(Vector2f(pos1.x + 50, pos2.y), tailTexture));
	}
	else {
		segments.push_back(SnakeSegment(Vector2f(pos1.x, pos2.y + 50), tailTexture));
	}
	points++;
}

int Snake::getPoints() {
	return points;
}
