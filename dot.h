#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "snake.h"

using namespace sf;


class Dot : public CircleShape
{
	



public:
	Dot(Color const &newColor, float newRadius, Vector2f const &pos) {
		this->setFillColor(newColor);
		this->setRadius(newRadius);
		this->setPosition(pos);
	}

};
