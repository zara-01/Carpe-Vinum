#include "WinScreen.h"

WinScreen::WinScreen(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	// init pointers 
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	
	//load in font 
	if (!font.loadFromFile("font/Super Mario Bros. 2.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	// set the font
	finalPoints.setFont(font);

	// initialise game objects and textures 
	winTexture.loadFromFile("gfx/winScreen.png");

	winScreen.setTexture(&winTexture);
	winScreen.setSize(sf::Vector2f(1024, 768));
	winScreen.setPosition(0, 0);

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

	// set default variables
	replay = false; // not replaying 
	
}

WinScreen::~WinScreen()
{
	//destructor 
}

void WinScreen::reset()
{
	replay = false;
}

// returns the replay boolean 
bool WinScreen::getReplay()
{
	return replay; //return replay 
}

//set the final points to a value passed in from level
void WinScreen::setFinalPoints(int p)
{
	playerPoints = p; // set the player points 
}

//handle input 
void WinScreen::handleInput(float dt)
{
	// if the replay button is clicked 
	if (replayButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		if (input->isMouseLDown())
		{
			replay = true; // set replay to true 
			audio->playSoundbyName("pickup"); // play the pickup sound
			audio->playMusicbyName("sailor"); // play the level music 
			gameState->setCurrentState(State::LEVEL); // switch to level state
		}

	}

	// if the quit button is clicked 
	if (quitButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play pickup sound 
			audio->playMusicbyName("grassyWorld"); // play menu music
			gameState->setCurrentState(State::MENU); // switch to level state
		}

	}
}

// update
void WinScreen::update(float dt)
{
	//set the playerpoints to string 
	std::string x_string = std::to_string(playerPoints); // convert to string
	finalPoints.setString( x_string );
	finalPoints.setCharacterSize(30); //set size
	finalPoints.setFillColor(sf::Color::Yellow); // set colour
	finalPoints.setPosition(935, 655); // set pos 
	// set view 
	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768)));

}

// render 
void WinScreen::render()
{
	beginDraw();
	window->draw(winScreen);
	window->draw(finalPoints);
	endDraw();
}

void WinScreen::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void WinScreen::endDraw()
{
	window->display();
}
