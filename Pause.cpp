#include "Pause.h"

Pause::Pause(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	//init pointers 
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	//init game objects
	pauseTexture.loadFromFile("gfx/pauseScreen.png");

	pauseScreen.setTexture(&pauseTexture);
	pauseScreen.setSize(sf::Vector2f(1024, 768));
	pauseScreen.setPosition(0, 0);

	continueButton.setSize(sf::Vector2f(648, 107));
	continueButton.setPosition(180, 65);
	continueButton.setFillColor(sf::Color::Transparent);
	continueButton.setOutlineColor(sf::Color::Red);
	continueButton.setOutlineThickness(2.f);

	menuButton.setSize(sf::Vector2f(310, 94));
	menuButton.setPosition(369, 226);
	menuButton.setFillColor(sf::Color::Transparent);
	menuButton.setOutlineColor(sf::Color::Red);
	menuButton.setOutlineThickness(2.f);

}

Pause::~Pause()
{
	//destructor 
}

void Pause::handleInput(float dt)
{

	// if the continue button us clicked return to level 
	if (continueButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); //play pickup sound 
			gameState->setCurrentState(State::LEVEL); //return to level state 
		}

	}

	// if thhe menu button is clicked return to the menu
	if (menuButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play the pickup sound 
			audio->playMusicbyName("grassyWorld"); // play the menu music 
			gameState->setCurrentState(State::MENU); // return to the menu state 
		}

	}
}

// update 
void Pause::update(float dt)
{
	//set the view 
	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768)));
}

// render 
void Pause::render()
{
	beginDraw();

	window->draw(pauseScreen);

	endDraw();
}

void Pause::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Pause::endDraw()
{
	window->display();
}
