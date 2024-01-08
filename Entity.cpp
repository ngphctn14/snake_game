#include "Entity.h"

Entity::Entity() {};

Entity::Entity(Vector2f p_pos, SDL_Texture* p_texture) : pos(p_pos), texture(p_texture) {
	currFrame.x = pos.x;
	currFrame.y = pos.y;
	SDL_Point size;
	SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
	currFrame.w = size.x;
	currFrame.h = size.y;
}

Vector2f& Entity::getPos() {
	return pos;
}

SDL_Rect Entity::getCurrentFrame() {
	return currFrame;
}

SDL_Texture* Entity::getTexture() {
	return texture;
}

void Entity::setTexture(SDL_Texture* p_texture) {
	texture = p_texture;
}
