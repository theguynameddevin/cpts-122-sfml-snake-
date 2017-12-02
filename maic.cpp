#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include "snake.h"

using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(VideoMode(400, 200),
		"Hello SFML");

	Color color = Color::Blue;
	Text text;

	text.setPosition(0, 0);
	text.setString("Hello SFML");

	vector<Snake> snake;
	Snake newSnake(Color::Blue, Vector2f(window.getSize().x / 200, window.getSize().y / 100),
		Vector2f(window.getSize().x / 2, window.getSize().y / 2));


	bool up = false, down = false, left = false, right = false;
	snake.push_back(newSnake);
	while (window.isOpen())
	{
		
		window.draw(snake[0]);
		Event event;
		while (window.pollEvent(event))
		{
			

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)	//up
				{
					up = true;
					down = false;
					left = false;
					right = false;
				}
				else if (event.key.code == Keyboard::Down)	//down
				{
					down = true;
					up = false;
					left = false;
					right = false;
				}
				else if (event.key.code == Keyboard::Left)	//left 
				{
					left = true;
					up = false;
					down = false;
					right = false;
				}
				else if (event.key.code == Keyboard::Right)	//right
				{
					up = false;
					down = false;
					left = false;
					right = true;
				}
			}

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Up)	//up
				{
					up = false;
				}
				else if (event.key.code == Keyboard::Down)	//down
				{
					down = false;
				}
				else if (event.key.code == Keyboard::Left)	//left 
				{
					left = false;
				}
				else if (event.key.code == Keyboard::Right)	//right
				{
					right = false;
				}
			}




			if (up == true )	//up
			{
				snake[0].move(0, -1);
			}
			if (down == true)	//down
			{
				snake[0].move(0, 1);
			}
			if (left == true)	//left 
			{
				snake[0].move(-1, 0);
			}
			if (right == true)	//right
			{
				snake[0].move(1, 0);
			}
		}

		window.clear();

		window.draw(text);
		window.draw(snake[0]);
		window.display();

	}

	return 0;
}