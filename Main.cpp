#include "pch.h"
#include "bat.h"
#include "ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;

int main()
{
	// Set window dimensions
	int windowWidth = 1024;
	int windowHeight = 768;

	RenderWindow window(VideoMode(windowWidth, windowHeight), "2 Player Pong");

	int score = 0;
	int lives = 1;
	
	// Initialize objects
	Bat bat(windowWidth * .66, windowHeight - 20);
	Bat bat2(windowWidth / 3, windowHeight - 20); // Second Player
	Ball ball(windowWidth / 2, 1);
	
	// Text to display score
	Text scoreDisplay;
	Font font;
	font.loadFromFile("DS-DIGIT.ttf");
	scoreDisplay.setFont(font);
	scoreDisplay.setCharacterSize(75);
	scoreDisplay.setFillColor(sf::Color::White);

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		// User Inputs
		// Right player
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			bat.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			bat.moveRight();
		}
		// Left Player
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			bat2.moveLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::D))
		{
			bat2.moveRight();
		}
		else if (Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		if (ball.getPosition().top > windowHeight)
		{
			ball.bottom();

			lives--;

			if (lives < 1) {
				score = 0;
				Sleep(2000);
				window.close();
			}

		}

		if (ball.getPosition().top < 0)
		{
			ball.collideBatOrTop();

			score++;

		}

		if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
		{
			ball.collideSides();
		}

		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.collideBatOrTop();
		}
		
		// Update objects' positions
		ball.update();
		bat.update();
		bat2.update();

		std::stringstream ss;
		ss << "Score:" << score;
		scoreDisplay.setString(ss.str());
		
		// Draw each object
		window.clear(Color(26, 0, 0, 255));
		window.draw(bat.getShape());
		window.draw(bat2.getShape());
		window.draw(ball.getShape());
		window.draw(scoreDisplay);
		window.display();
	}

	return 0;
}
