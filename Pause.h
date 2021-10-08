#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class Pause
{
public:
	//constructor&destructor
	Pause(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Pause();
	// handleInput, update & render
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
	sf::RectangleShape pauseScreen;

	sf::RectangleShape menuButton;
	sf::RectangleShape continueButton;

	sf::Texture pauseTexture;

};