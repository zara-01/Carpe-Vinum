#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "FullWineCollectable.h"
#include <string>
#include <iostream>

class WinScreen
{
public:
	//construcot/destructor
	WinScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~WinScreen();

	// handleInput, update, render & reset
	void handleInput(float dt);
	void update(float dt);
	void render();
	void reset();

	//sets the final points by using a variable passed in from level
	void setFinalPoints(int p);
	//if the game is going to be replayed
	bool getReplay();


private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;

	// objects and textures
	sf::RectangleShape winScreen;

	sf::RectangleShape replayButton;
	sf::RectangleShape quitButton;

	sf::Texture winTexture;

	sf::Text finalPoints;
	sf::Font font;

	//variables
	int playerPoints; // the players final points 
	bool replay; // tracks if the game is going to be replayed 
};

