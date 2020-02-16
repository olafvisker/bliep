#pragma once
#include <SDL2/SDL.h>

#include "ecs/component.h"

struct CameraController : bliep::Component {
    unsigned up = SDLK_e;
	unsigned down = SDLK_q;
	unsigned left = SDLK_a;
	unsigned right = SDLK_d;
	unsigned forward = SDLK_w;
	unsigned backward = SDLK_s;

	float movement_speed = 50.0f;
	float rotation_speed = 25.0f;

	float max_pitch = 89.0f;
	float min_pitch = -89.0f;
};