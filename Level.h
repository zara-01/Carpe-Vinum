#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include "Map.h"
#include "Gladiator.h"
#include "WineCollectable.h"
#include "FullWineCollectable.h"
#include "Enemy.h"




class Level {
public:
	// constructor& destructor
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	// handleInput, update, render & reset
	void handleInput(float dt);
	void update(float dt);
	void render();
	void reset();

	//get the player's points
	int getPlayerPoints();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
	void textSetup();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	//textures
	sf::Texture texture;
	sf::Texture backdrop;
	sf::Texture arena_floor;

	sf::RectangleShape map;
	Map arenaFloor;

	// level objects
	sf::Texture gladiatorTexture;
	Gladiator gladiator;

	sf::Texture wineTexture;
	WineCollectable wine;

	sf::Texture fullWineTexture;
	FullWineCollectable fullWine;

	sf::Texture enemyTexture;
	Enemy enemy;

	//initialise text
	sf::Text playerHealth;
	sf::Text playerPoints;
	sf::Text enemyHealth;
	sf::Text buffDisplay;
	sf::Font font;
	//level variables 
	float timeCount; //timer
	bool playerBuffed; //keeps track if the player is buffed 
	

};