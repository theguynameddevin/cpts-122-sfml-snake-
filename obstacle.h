#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

class Obstacle : public sf::RectangleShape {
	public:
		Obstacle(Color const &newColor, Vector2f const &newSize, Vector2f const &pos) {
			this->setFillColor(newColor);
			this->setSize(newSize);
			this->setPosition(pos);
		}
	
};
