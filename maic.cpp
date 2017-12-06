#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "dot.h"
#include "obstacle.h"
#include <iostream>
#include <fstream>
//#include "record.h"
#include <string>
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
	Vector2f otherPosition(0, 0);
	vector<Snake> snake;
	vector<Obstacle> obstacle;
	Snake newSnake(Color::Blue, window.getSize().x / 100,
		Vector2f(window.getSize().x / 10, window.getSize().y / 10));
	Dot newDot(Color::Green, window.getSize().x / 100, Vector2f(12, 12));
	newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));
	int index = 0;
	int snakeSize = 1, obstacleAmount = 0;
	bool up = false, down = false, left = false, right = false, game = false, exit = false, obstacleUsed = false, overlapping = false,
		collision = false;
	snake.push_back(newSnake);
	newSnake.setPosition(snake[0].getPosition().x - (2 * snake[0].getRadius()), snake[0].getPosition().y);

	Text menuText;
	string Menu = "Snake\nCreated by: Michael Smith, Devin Hollander, Demetrius Anderson\n";
	Menu += "Press 1 to play\nPress 2 to view game rules\nPress 3 to view high scores \nPress 4 to exit";
	menuText.setString(Menu);
	menuText.setFont(font);
	// added new font size to fit screen
	menuText.setCharacterSize(16);
	menuText.setPosition(0, 0);

	Text rulesText;
	string rules = "Game Rules\n1. Your snake is blue. Each additional segment that you are trying to add is green.\n2. In order to add that segment to your snake you must direct your snake to collide \nwith the green circle.\n";
	rules += "3. Whenever your snake length reaches a multiple of 5, a red, rectangular obstacle \nwill be added to the window.\n";
	rules += "4. In order to survive your snake must avoid the obstacles, stay within the bounds \nof the screen, and cannot collide with itself.\n";
	rules += "5. That also means you cannot move back on yourself. Meaning if you were traveling \nleft you cannot suddenly go to the right without first having gone up or down.\n";
	rules += "Press 1 to play game, 3 to view high scores, or 4 to exit\n";
	rulesText.setPosition(0, 0);
	rulesText.setFont(font);
	rulesText.setString(rules);
	rulesText.setCharacterSize(16);

	Text text;
	text.setPosition(200, 200);
	text.setFont(font);

	//snake.push_back(newSnake);

	//newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));


	// load high scores
	// note that it crashes if the file is empty.........
	fstream highScores;
	highScores.open("HighScores.txt");
	//vector<Record> records;
	string name;
	string scoreStr;
	vector<int> score;
	while (!highScores.eof())
	{
		/*
		getline(highScores, name);
		getline(highScores, scoreStr);
		score = stoi(scoreStr);
		records.push_back(Record(name, score));
		*/
		getline(highScores, scoreStr);
		if (scoreStr != "")
			score.push_back(stoi(scoreStr));
	}
	highScores.close();
	while (window.isOpen())
	{
		Event event;
		exit = false;
		collision = false;
		/*while (window.pollEvent(event))
		{
		}*/

		window.draw(menuText);
		window.display();
		// this while loop keeps the program from skipping out of the event poll 
		while (game == false) {
			while (window.pollEvent(event))
			{
				// added if statement around this because we forgot it
				if (event.type == Event::KeyPressed) {
					// this while statement was making it impossible to advance to the game
					//while (event.key.code != Keyboard::Num1 && event.key.code != Keyboard::Num2 && event.key.code != Keyboard::Num3)
					//{
					if (event.key.code == Keyboard::Num1)
					{
						game = true;
					}
					if (event.key.code == Keyboard::Num2)
					{
						window.clear();
						window.draw(rulesText);
						window.display();
					}
					// read from file to display high scores
					if (event.key.code == Keyboard::Num3)
					{
						///////////Sorts high Scores////////
						int i, j, temp;
						for (int i = 0; i < score.size(); i++)
						{
							temp = score[i];
							j = i;
							while (j > 0 && score[j] < score[j - 1])
							{
								temp = score[j];
								score[j] = score[j - 1];
								score[j - 1] = temp;
								j--;
							}

						}
						//////////////////////////////////////////////////////
						if (score.size() > 1)		//only displays if there is a high score
						{
							window.clear();
							std::string line = "High Scores\n";

							for (int i = 0; i < 5 && i < score.size() - 1; i++)			//runs 5 times or the amount of items in the vector
							{
								line += std::to_string(i + 1);
								line += ". ";
								line += std::to_string(score[score.size() - (i + 1)]); //starts at the end of the vector and moves down
								line += "\n";
							}
							line += "Press 1 to play";
							text.setString(line);
							window.draw(text);

							window.display();
						}
						else
						{
							string line = "There are no scores Yet";
							text.setString(line);
							window.draw(text);
							window.display();
						}
					}
					if (event.key.code == Keyboard::Num4)
					{
						window.close();
						return 0;
					}
					//}
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
			}
			// adding obstacle 
			if (snakeSize % 5 == 0 && obstacleUsed == false) {
				if (rand() % 2 == 1) {
					Obstacle newObstacle(Color::Red, Vector2f(window.getSize().x / 60, window.getSize().y / 30), Vector2f(0, 0));
					do {
						overlapping = false;
						newObstacle.setPosition(Vector2f(rand() % (window.getSize().x / 12) * 12, rand() % (window.getSize().y / 12) * 12));
						otherPosition = Vector2f(newObstacle.getPosition().x, newObstacle.getPosition().y + 12);
						newObstacle.setOtherPosition(otherPosition);
						int i = 0;
						while (i < snakeSize && overlapping != true) {
							if (snake[i].getPosition().x == newObstacle.getPosition().x && snake[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							if (snake[i].getPosition().x == newObstacle.getOtherPosition().x && snake[i].getPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							i++;
						}
						i = 0;
						while (i < obstacleAmount && overlapping != true) {
							if (obstacle[i].getPosition().x == newObstacle.getPosition().x && obstacle[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							if (obstacle[i].getOtherPosition().x == newObstacle.getPosition().x && obstacle[i].getOtherPosition().y == newObstacle.getPosition().y && overlapping!= true) {
								overlapping = true;
							}
							if (obstacle[i].getPosition().x == newObstacle.getOtherPosition().x && obstacle[i].getPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							if (obstacle[i].getOtherPosition().x == newObstacle.getOtherPosition().x && obstacle[i].getOtherPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							i++;
						}
						if (newDot.getPosition().x == newObstacle.getPosition().x && newDot.getPosition().y == newObstacle.getPosition().y && overlapping != true) {
							overlapping = true;
						}
						if (newDot.getPosition().x == newObstacle.getOtherPosition().x && newDot.getPosition().y == newObstacle.getOtherPosition().y) {
							overlapping = true;
						}
					} while (overlapping == true);
					obstacle.push_back(newObstacle);
					obstacleAmount++;
					//window.draw(newObstacle);
					//window.display();
					obstacleUsed = true;
				}
				else {
					Obstacle newObstacle(Color::Red, Vector2f(window.getSize().x / 30, window.getSize().y / 60), Vector2f(0, 0));
					do {
						overlapping = false;
						newObstacle.setPosition(Vector2f(rand() % (window.getSize().x / 12) * 12, rand() % (window.getSize().y / 12) * 12));
						otherPosition = Vector2f(newObstacle.getPosition().x + 12, newObstacle.getPosition().y);
						newObstacle.setOtherPosition(otherPosition);
						int i = 0;
						while (i < snakeSize && overlapping != true) {
							if (snake[i].getPosition().x == newObstacle.getPosition().x && snake[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							if (snake[i].getPosition().x == newObstacle.getOtherPosition().x && snake[i].getPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							i++;
						}
						i = 0;
						while (i < obstacleAmount && overlapping != true) {
							if (obstacle[i].getPosition().x == newObstacle.getPosition().x && obstacle[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							if (obstacle[i].getOtherPosition().x == newObstacle.getPosition().x && obstacle[i].getOtherPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							if (obstacle[i].getPosition().x == newObstacle.getOtherPosition().x && obstacle[i].getPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							if (obstacle[i].getOtherPosition().x == newObstacle.getOtherPosition().x && obstacle[i].getOtherPosition().y == newObstacle.getOtherPosition().y) {
								overlapping = true;
							}
							i++;
						}
						if (newDot.getPosition().x == newObstacle.getPosition().x && newDot.getPosition().y == newObstacle.getPosition().y) {
							overlapping = true;
						}
						if (newDot.getPosition().x == newObstacle.getOtherPosition().x && newDot.getPosition().y == newObstacle.getOtherPosition().y) {
							overlapping = true;
						}
					} while (overlapping == true);
					obstacle.push_back(newObstacle);
					obstacleAmount++;
					//window.draw(newObstacle);
					//window.display();
					obstacleUsed = true;
				}

			}
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
			// checks for collision with obstacle
			int i = 0;
			while (i < obstacleAmount && collision == false) {
				if (obstacle[i].getPosition().x == snake[0].getPosition().x && obstacle[i].getPosition().y == snake[0].getPosition().y) {
					up = false;
					down = false;
					left = false;
					right = false;
					game = false;
				}
				if (obstacle[i].getOtherPosition().x == snake[0].getPosition().x && obstacle[i].getOtherPosition().y == snake[0].getPosition().y) {
					up = false;
					down = false;
					left = false;
					right = false;
					game = false;
				}
				i++;
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
			index++;
			window.clear();

			for (int i = 0; i < snakeSize; i++)
			{
				window.draw(snake[i]);
			}
			for (int i = 0; i < obstacleAmount; i++) {
				window.draw(obstacle[i]);
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

			// added checks for adding new dot onto a position that already contains an object
			if (snake[0].getPosition().x == newDot.getPosition().x && snake[0].getPosition().y == newDot.getPosition().y)
			{
				do {
					overlapping = false;
					newDot.setPosition(Vector2f((rand() % (window.getSize().x / 12)) * 12, (rand() % (window.getSize().y / 12)) * 12));
					int i = 0;
					while (i < snakeSize && overlapping != true) {
						if (snake[i].getPosition().x == newDot.getPosition().x && snake[i].getPosition().y == newDot.getPosition().y) {
							overlapping = true;
						}
						i++;
					}
					i = 0;
					while (i < obstacleAmount && overlapping != true) {
						if (obstacle[i].getPosition().x == newDot.getPosition().x && obstacle[i].getPosition().y == newDot.getPosition().y) {
							overlapping = true;
						}
						if (obstacle[i].getOtherPosition().x == newDot.getPosition().x && obstacle[i].getOtherPosition().y == newDot.getPosition().y) {
							overlapping = true;
						}
						i++;
					}
				} while (overlapping == true);
				newSnake.setPosition(snake[snakeSize - 1].getOldPosition());
				snake.push_back(newSnake);
				snakeSize++;
				obstacleUsed = false;
			}



			window.display();
		}

		snake.clear();

		string message = "Game over\nYour Score was ";
		message += to_string(snakeSize);
		message += "\nPress E to return to menu";
		window.clear();

		//// checking if high score was beat to prompt new high score
		//for (int i = 0; i < records.size(); i++)
		//{
		//	// score better than i'th place
		//	if (records[i].getScore() < snakeSize)
		//	{
		//		message += "\nNew High Score!";
		//		message += "\nEnter Name: ";

		//		break;
		//	}
		//}
		score.push_back(snakeSize);


		highScores.open("HighScores.txt");
		for (int i = 0; i < score.size() - 1; i++)
		{
			highScores << score[i] << endl;
		}
		highScores.close();

		snakeSize = 1;
		obstacleAmount = 0;
		text.setString(message);
		window.draw(text);
		window.display();

		// this while loop keeps the event polling until the letter e is pressed
		while (exit == false) {
			while (window.pollEvent(event))
			{

				//// stuff for checking for new high score and updating high scores list
				//string newHighScore;
				//for (int i = 0; i < records.size(); i++)
				//{
				//	// score better than i'th place
				//	if (records[i].getScore() < snakeSize)
				//	{
				//		if (event.type == sf::Event::TextEntered)
				//		{
				//			// Handle ASCII characters only
				//			if (event.text.unicode < 128)
				//			{
				//				newHighScore += static_cast<char>(event.text.unicode);
				//				message += newHighScore;
				//				text.setString(message);
				//			}
				//			records[i].setName(newHighScore);
				//			records[i].setScore(snakeSize);
				//		}
				//		// update high scores list
				//		for (int j = i + 1; j < records.size(); j++)
				//		{
				//			records[j] = records[j-1];
				//		}
				//		for (int k = 0; i < records.size(); k++)
				//		{
				//			highScores << records[k].getName() << std::endl;
				//			highScores << records[k].getScore() << std::endl;
				//		}
				//		break;
				//	}
				//}// end high scores stuff

				if (event.type == Event::KeyPressed) {
					//while (event.key.code != Keyboard::E)
					//{

					if (event.key.code == Keyboard::E)
					{

						exit = true;
						window.clear();
					}
					//}
				}
			}
		}

	}
	return 0;
}
