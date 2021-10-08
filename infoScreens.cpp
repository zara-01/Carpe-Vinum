#include "infoScreens.h"

infoScreens::infoScreens(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	// init pointers 
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// set textures
	infoScreen1Texture.loadFromFile("gfx/introScreenOne.png");
	infoScreen2Texture.loadFromFile("gfx/introScreenTwo.png");

	// init objects 

	infoScreen1.setTexture(&infoScreen1Texture);
	infoScreen1.setSize(sf::Vector2f(1024, 768));
	infoScreen1.setPosition(0, 0);

	infoScreen2.setTexture(&infoScreen2Texture);
	infoScreen2.setSize(sf::Vector2f(1024, 768));
	infoScreen2.setPosition(0, 0);

	//set default variables
	spaceTimes = 0;
	switchScreen = false;

}

infoScreens::~infoScreens() {} // destructor

// reset variable values 
void infoScreens::reset()
{
	spaceTimes = 0;
	switchScreen = false;
}

// handle inout 
void infoScreens::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Space)) // when space is pressed
	{
		input->setKeyUp(sf::Keyboard::Space); //set the button up
		audio->playSoundbyName("pickup"); // play the pickup noise 
		spaceTimes++; // increment space times
		switchScreen = true; // set switch screen to true
	}
	
}

// update 
void infoScreens::update(float dt)
{
	if (spaceTimes >= 2) // when space has bit hit more than twice (seen both screens)
	{
		gameState->setCurrentState(State::LEVEL); // enter level 
	}

	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768))); // set the view 
}

// render everything 
void infoScreens::render()
{
	beginDraw();
	if (spaceTimes < 1)
	{
		window->draw(infoScreen1);
	}
	else
	{
		window->draw(infoScreen2);
	}
	
	endDraw();
}

void infoScreens::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void infoScreens::endDraw()
{
	window->display();
}
