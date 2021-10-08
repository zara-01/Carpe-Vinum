#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Gladiator.h"
#include <string>
#include <iostream>

class OptionMenu
{
public:
	//construcot&destructor
	OptionMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~OptionMenu();

	// handleInput, update & reset
	void handleInput(float dt);
	void update(float dt);
	void render();

	// track if music is on/off
	bool isMusicEnabled();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	bool musicOn; //boolean to track if music is on or off

	float cooldown; // cooldown timer

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;

	//objects and textures
	sf::Texture gladiatorTexture;
	Gladiator soundGladiator;

	sf::RectangleShape optionScreen;

	sf::RectangleShape backButton;

	sf::Texture optionTexture;

};

