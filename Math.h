#pragma once

#include <iostream>
#include <SDL.h>

struct Vector2f {
	Uint32 x, y;
	Vector2f() : x(0), y(0) {}
	Vector2f(Uint32 v_x, Uint32 v_y) : x(v_x), y(v_y) {}
	void print();
};
