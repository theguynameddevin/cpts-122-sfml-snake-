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
	string Menu = "Snake\nCreated by: \nMichael Smith:  Section 6\nDevin Hollander:  Section 7\nDemetrius Anderson: Section \n";
	Menu += "Collect as many dots as possible.\n";
	Menu += "If the head of your snake runs off the screen, runs into the body of your snake,\nor hits an obstacle you lose\n";

	Menu += "Press 1 to play\nPress 2 to view high scores \nPress 3 to exit";

	menuText.setString(Menu);

	menuText.setFont(font);
	// added new font size to fit screen
	menuText.setCharacterSize(16);
	menuText.setPosition(0, 0);

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
		if (scoreStr!= "")
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
					// read from file to display high scores
					if (event.key.code == Keyboard::Num2)
					{
						///////////Sorts high Scores////////
						int i, j, temp;
						for (i = 0; i < score.size(); i++)
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
					if (event.key.code == Keyboard::Num3)
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
				overlapping = false;
				if (rand() % 2 == 1) {
					Obstacle newObstacle(Color::Red, Vector2f(window.getSize().x / 60, window.getSize().y / 30), Vector2f(0, 0));
					
					do {
						newObstacle.setPosition(Vector2f(rand() % (window.getSize().x / 12) * 12, rand() % (window.getSize().y / 12) * 12));
						int i = 0;
						while (i < snakeSize && overlapping != true) {
							if (snake[i].getPosition().x == newObstacle.getPosition().x && snake[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							i++;
						}
						i = 0;
						while (i < obstacleAmount && overlapping != true) {
							if (obstacle[i].getPosition().x == newObstacle.getPosition().x && obstacle[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							i++;
						}
						if (newDot.getPosition().x == newObstacle.getPosition().x && newDot.getPosition().y == newObstacle.getPosition().y) {
							overlapping = true;
						}
					} while (overlapping == true);
					Vector2f temp;
					temp.x = newObstacle.getPosition().x;
					temp.y = newObstacle.getPosition().y + (2 * snake[0].getRadius());
					newObstacle.setSecondPosition(temp);
					obstacle.push_back(newObstacle);
					obstacleAmount++;
					//window.draw(newObstacle);
					//window.display();
					obstacleUsed = true;
				}
				else {
					Obstacle newObstacle(Color::Red, Vector2f(window.getSize().x / 30, window.getSize().y / 60), Vector2f(0, 0));
					do {
						newObstacle.setPosition(Vector2f(rand() % (window.getSize().x / 12) * 12, rand() % (window.getSize().y / 12) * 12));
						
						int i = 0;
						while (i < snakeSize && overlapping != true) {
							if (snake[i].getPosition().x == newObstacle.getPosition().x && snake[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							i++;
						}
						i = 0;
						while (i < obstacleAmount && overlapping != true) {
							if (obstacle[i].getPosition().x == newObstacle.getPosition().x && obstacle[i].getPosition().y == newObstacle.getPosition().y) {
								overlapping = true;
							}
							i++;
						}
						if (newDot.getPosition().x == newObstacle.getPosition().x && newDot.getPosition().y == newObstacle.getPosition().y) {
							overlapping = true;
						}
					} while (overlapping == true);
					Vector2f temp;
					temp.x = newObstacle.getPosition().x + (2 * snake[0].getRadius());
					temp.y = newObstacle.getPosition().y;
					newObstacle.setSecondPosition(temp);
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
				if (obstacle[i].getSecondPosition().x == snake[0].getPosition().x && obstacle[i].getSecondPosition().y == snake[0].getPosition().y)
				{
					up = false;
					down = false;
					left = false;
					right = false;
					game = false;
				}
				i++;
			}
			i = 0;
	
			if (index % 250 == 0)
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
				overlapping = false;
				do {
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
		obstacle.clear();

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
		if (snakeSize > score[0])
			score.push_back(snakeSize);
		if (score.size() > 5)
		{
			score.erase(score.begin());
		}

		highScores.open("HighScores.txt");
		for (int i = 0; i < score.size(); i++)
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
