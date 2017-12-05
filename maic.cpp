#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "dot.h"

using namespace sf;
using namespace std;


int main()
{
	Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	srand((unsigned int)time(NULL));

	RenderWindow window(VideoMode(600, 600),
		"Hello SFML");

	Color color = Color::Blue;
	
	
	vector<Snake> snake;
	Snake newSnake(Color::Blue, window.getSize().x / 100,
		Vector2f(window.getSize().x / 10, window.getSize().y / 10));
	Dot newDot(Color::Blue, window.getSize().x / 100, Vector2f(12, 12));
	newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));
	int index = 0;
	int snakeSize = 1;
	bool up = false, down = false, left = false, right = false, game = false;
	snake.push_back(newSnake);
	newSnake.setPosition(snake[0].getPosition().x -( 2 * snake[0].getRadius()), snake[0].getPosition().y);
	
	//snake.push_back(newSnake);

	//newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));

	while (window.isOpen())
	{
		Event event;
		/*while (window.pollEvent(event))
		{
			
		
			
		}*/
		Text menuText;
		string Menu = "Snake\nCreated by: Michael Smith, Devin Hollander, Demetrius Anderson\n";
		
		Menu += "Press 1 to play\n Press 2 to view high scores \n press 3 to exit";

		menuText.setString(Menu);

		menuText.setFont(font);
		menuText.setPosition(0, 0);
		window.draw(menuText);
		window.display();

		while (window.pollEvent(event))
		{
			event.type == Event::KeyPressed;
			while (event.key.code != Keyboard::Num1 && event.key.code != Keyboard::Num2 && event.key.code != Keyboard::Num3)
			{
				if (event.key.code == Keyboard::Num1)
				{
					game = true;
				}
				if (event.key.code == Keyboard::Num2)
				{

				}
				if (event.key.code == Keyboard::Num3)
				{
					window.close();
					return 0;
				}
			}
		}
		window.clear();
		snake.push_back(newSnake);
		while (game == true)
		{
			window.draw(newDot);
			window.draw(snake[0]);
			Event event;
			while (window.pollEvent(event))
			{


				if (event.type == Event::Closed)
					window.close();
				//while ()
				{
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
				}

				/*if (event.type == Event::KeyReleased)
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
				*/




			}

			/*int prevX = snake[0].getPosition().x;
			int prevY = snake[0].getPosition().y;*/
			for (int i = 1; i < snakeSize; i++)
			{
				if (snake[0].getPosition() == snake[i].getPosition() && snake[0].getPosition() != newDot.getPosition())
				{
					up = false;
					down = false;
					left = false;
					right = false;
					game = false;
				}
			}

			if (index % 50 == 0)
			{
				for (int i = 0; i < snakeSize; i++)
				{
					snake[i].setOldPosition(snake[i].getPosition());
				}
				for (int i = snakeSize - 1; i > 0; i--)
				{
					snake[i].setPosition(snake[i - 1].getOldPosition());
				}
				if (up == true)	//up
				{
					//snake[1].setPosition(snake[0].getPosition());
					snake[0].move(0, -2 * snake[0].getRadius());

				}
				if (down == true)	//down
				{
					//snake[1].setPosition(snake[0].getPosition());
					snake[0].move(0, 2 * snake[0].getRadius());
				}
				if (left == true)	//left
				{
					//snake[1].setPosition(snake[0].getPosition());
					snake[0].move(-2 * snake[0].getRadius(), 0);
				}
				if (right == true)	//right
				{
					//snake[1].setPosition(snake[0].getPosition());
					snake[0].move(2 * snake[0].getRadius(), 0);
				}

			}
			/*
			if (index % 50 == 0)
			{
				int prevX = snake[0].getPosition().x;
				int prevY = snake[0].getPosition().y;
				if (up == true)	//up
				{
					snake[0].move(0, -2 * snake[0].getRadius());
					snake[1].setPosition(prevX, prevY);
				}
				if (down == true)	//down
				{
					snake[0].move(0, 2 * snake[0].getRadius());
					snake[1].setPosition(prevX, prevY);
				}
				if (left == true)	//left
				{
					snake[0].move(-2 * snake[0].getRadius(), 0);
					snake[1].setPosition(prevX, prevY);
				}
				if (right == true)	//right
				{
					snake[0].move(2 * snake[0].getRadius(), 0);
					snake[1].setPosition(prevX, prevY);
				}
			}*/
			index++;
			window.clear();

			for (int i = 0; i < snakeSize; i++)
			{
				window.draw(snake[i]);
			}
			//window.draw(snake[0]);
			//window.draw(snake[1]);
			window.draw(newDot);
			
			if (snake[0].getPosition().x < 0 || snake[0].getPosition().x > window.getSize().x - (2 * snake[0].getRadius()) ||
				snake[0].getPosition().y < 0 || snake[0].getPosition().y > window.getSize().y - (2 * snake[0].getRadius()))
			{
				up = false;
				down = false;
				left = false;
				right = false;
				game = false;
			}


			if (snake[0].getPosition().x == newDot.getPosition().x && snake[0].getPosition().y == newDot.getPosition().y)
			{

				newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));
				newSnake.setPosition(snake[snakeSize - 1].getOldPosition());
				snake.push_back(newSnake);
				snakeSize++;
			}
			


			window.display();
		}
	
		
		 
		snake.clear();
		

		Text text;
		text.setColor(Color::White);
		text.setPosition(100, 100);
		text.setFont(font);

		string message = "Game over\nYour Score was ";
		message += to_string(snakeSize);
		snakeSize = 1;
		text.setString(message);
		window.draw(text);
		window.display();
		
		while (window.pollEvent(event))
		{
			while (event.key.code != Keyboard::E)
			{

				if (event.key.code == Keyboard::E)
				{
					game = false;
					window.clear();
				}
			}
		}

	}


	return 0;
}

