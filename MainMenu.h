#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>

class MainMenu
{
public:
	// constructor/destructor
	MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~MainMenu();
	// handleInput, update, render & reset
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

	sf::RectangleShape menuScreen; // the menu screen
	sf::Vector2f mousepos; //mouse position variable 

	// buttons 
	sf::RectangleShape playButton;
	sf::RectangleShape optionsButton;
	sf::RectangleShape quitButton;
	sf::Texture mapTexture;

	float cooldown; // a cooldown for the button presses

};