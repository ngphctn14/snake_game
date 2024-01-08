#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.h"
#include "SnakeSegment.h"
#include "Resolution.h"

enum Directions {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NUMBER_OF_DIRECTIONS
};

class Snake : public Entity {
private:
	SDL_Texture* segmentTexture;
	SDL_Texture* tailTexture;
	int xSpeed, ySpeed;
	int points;
	int angle;
	bool headDirections[NUMBER_OF_DIRECTIONS];
	bool dead;
	std::vector<SnakeSegment> segments;
	void checkIfDead();
	void setDirections(int num);
	Uint32 lastTime;
	Uint32 cooldown;

public:
	Snake();
	Snake(Vector2f p_pos, SDL_Texture* p_texture, SDL_Texture* p_segmentTexture, SDL_Texture* p_tailTexture);
	void getInput(SDL_Event& e);
	void update();
	std::vector<SnakeSegment> getSnakeSegments();
	bool isDead();
	void setDead(bool state);
	void grow();
	int getHeadAngle();
	int getTailAngle();
	int getPoints();
};
