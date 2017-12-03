#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

using namespace sf;

class Snake : public sf::CircleShape
{
private:
	Vector2f oldPosition;

public:
	
	Snake(sf::Color const &newColor, float radius, sf::Vector2f const &pos)
	{
		this->setFillColor(newColor);
		this->setRadius(radius);
		this->setPosition(pos);
	}

	void setOldPosition(Vector2f vector)
	{
		this->oldPosition = vector;

	}
	Vector2f getOldPosition()
	{
		return this->oldPosition;
	}
};  
