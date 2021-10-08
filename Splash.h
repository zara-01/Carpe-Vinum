#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Animation.h"
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Gladiator.h"
#include <string>
#include <iostream>


class Splash
{
public:
	//constructor&destructor
	Splash(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Splash();
	// handleInput, update, render 
	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;

	//objects and textures
	sf::Texture gladiatorTexture;
	Gladiator splashGladiator;

	sf::RectangleShape splashScreen;

	sf::Texture splashTexture;

	// timer variable
	float timer;

};

