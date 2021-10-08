#include "DeathScreen.h"

DeathScreen::DeathScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	//pointers
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	//load the font
	if (!font.loadFromFile("font/Super Mario Bros. 2.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	// initialise objects
	finalPoints.setFont(font); //set the font 
	deathTexture.loadFromFile("gfx/loseScreen.png"); //set the screen texture

	deathScreen.setTexture(&deathTexture);
	deathScreen.setSize(sf::Vector2f(1024, 768));
	deathScreen.setPosition(0, 0);

	// set up the buttons 

	replayButton.setSize(sf::Vector2f(357, 72));
	replayButton.setPosition(346, 503);
	replayButton.setFillColor(sf::Color::Transparent);
	replayButton.setOutlineColor(sf::Color::Red);
	replayButton.setOutlineThickness(2.f);

	quitButton.setSize(sf::Vector2f(662, 68));
	quitButton.setPosition(341, 425);
	quitButton.setFillColor(sf::Color::Transparent);
	quitButton.setOutlineColor(sf::Color::Red);
	quitButton.setOutlineThickness(2.f);


	replay = false; // set replay to false 

}

DeathScreen::~DeathScreen() {} // destructor 

void DeathScreen::reset()
{
	replay = false;
}

bool DeathScreen::getReplay() // returns the replay bool
{
	return replay;
}

void DeathScreen::setFinalPoints(int p) // set the points to the value passed in through level
{
	playerPoints = p;
}

void DeathScreen::handleInput(float dt) // handlles the button clicks 
{

	if (replayButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) //collision check between mouse and button by using globalbounds
	{
		if (input->isMouseLDown()) // if the mouse is clicked
		{
			replay = true; // set replay to true 
			audio->playSoundbyName("pickup"); // play the pickup sound
			audio->playMusicbyName("sailor"); // play the level music
			gameState->setCurrentState(State::LEVEL); // switch to the level state
		}

	}

	if (quitButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) //collision check between mouse and button by using globalbounds
	{
		if (input->isMouseLDown()) // if the mouse is clicked
		{
			audio->playSoundbyName("pickup"); // play the pickup sound
			audio->playMusicbyName("grassyWorld");
			gameState->setCurrentState(State::MENU); // switch to the menu state
		}

	}
}

void DeathScreen::update(float dt) // update
{
	std::string x_string = std::to_string(playerPoints); // convert integer to string

	finalPoints.setString(x_string); // set the string 
	finalPoints.setCharacterSize(30); // set the size
	finalPoints.setFillColor(sf::Color::Yellow); // set the colour 
	finalPoints.setPosition(910, 655); // set the position 
	
	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768))); //set the view 
}

void DeathScreen::render() // draw to screen 
{
	beginDraw();
	window->draw(deathScreen);
	window->draw(finalPoints);
	endDraw();
}

void DeathScreen::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void DeathScreen::endDraw()
{
	window->display();
}
