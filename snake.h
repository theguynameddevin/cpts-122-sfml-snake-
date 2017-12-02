#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


class Snake : public sf::RectangleShape
{

public:
	
	Snake(sf::Color const &newColor, sf::Vector2f const &size, sf::Vector2f const &pos)
	{
		this->setFillColor(newColor);
		this->setSize(size);
		this->setPosition(pos);
	}
};


