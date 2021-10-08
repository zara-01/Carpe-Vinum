#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class DeathScreen
{
public:
	//constructor&destructor
	DeathScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~DeathScreen();

	//handleInput, update reender & reset
	void handleInput(float dt);
	void update(float dt);
	void render();
	void reset();

	//returns if the player wants to replay or not
	bool getReplay();

	//sets the final points using a value passed in from level
	void setFinalPoints(int p);

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;

	// objects 
	sf::RectangleShape deathScreen;
	sf::RectangleShape replayButton;
	sf::RectangleShape quitButton;
	sf::Texture deathTexture;
	sf::Text finalPoints;
	sf::Font font;

	//points variables 
	int playerPoints;
	//boolean for replay
	bool replay;
};

