#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class infoScreens
{
public:
	//constructor&destructor
	infoScreens(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~infoScreens();

	//handleInput, update, render & reset
	void handleInput(float dt);
	void update(float dt);
	void render();
	void reset();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	//objects and texture
	sf::RectangleShape infoScreen1;
	sf::RectangleShape infoScreen2;
	sf::Texture infoScreen1Texture;
	sf::Texture infoScreen2Texture;

	//variables
	int spaceTimes; //tracks how many times space has been hit
	bool switchScreen; //bool tracks switching between screens 
};