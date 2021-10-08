#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	//init pointers 
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// init game objects

	mapTexture.loadFromFile("gfx/menuScreen.png");
	
	menuScreen.setTexture(&mapTexture);
	menuScreen.setSize(sf::Vector2f(1024, 768));
	menuScreen.setPosition(0, 0);

	playButton.setSize(sf::Vector2f(222, 71));
	playButton.setPosition(395, 429);
	playButton.setFillColor(sf::Color::Transparent);
	playButton.setOutlineColor(sf::Color::Red);
	playButton.setOutlineThickness(2.f);

	optionsButton.setSize(sf::Vector2f(791, 61));
	optionsButton.setPosition(117, 536);
	optionsButton.setFillColor(sf::Color::Transparent);
	optionsButton.setOutlineColor(sf::Color::Red);
	optionsButton.setOutlineThickness(2.f);

	quitButton.setSize(sf::Vector2f(215, 71));
	quitButton.setPosition(398, 643);
	quitButton.setFillColor(sf::Color::Transparent);
	quitButton.setOutlineColor(sf::Color::Red);
	quitButton.setOutlineThickness(2.f);

	//set cooldown to deafult 2
	cooldown = 0;
}

MainMenu::~MainMenu()
{
	// destructor 
}


//reset varibales to default 
void MainMenu::reset()
{
	cooldown = 0;
}

//handleinput 
void MainMenu::handleInput(float dt)
{
	cooldown += dt; // increment cooldown 
	
	//if the quit button is clicked 
	if (quitButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))) && cooldown > 1)
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play pickup sound 
			window->close(); // quit the game 
		}

	}
	
	// if the play button is clicked 
	if (playButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))) && cooldown > 1)
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play pickup sound 
			audio->stopAllMusic();
			audio->playMusicbyName("sailor"); // play the level music 
			gameState->setCurrentState(State::INFO); // go to info state
		}
		
	}

	// if the option button is clicked 
	if (optionsButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))) && cooldown > 1)
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play pickup sound
			gameState->setCurrentState(State::OPTIONS); // go to options state 
		}

	}
}

//update 
void MainMenu::update(float dt)
{
	//play music 
	if (audio->getMusic()->getStatus() == sf::SoundSource::Stopped)
	{
		audio->playMusicbyName("grassyWorld");
	}

	//set music 
	window->setView(sf::View(sf::Vector2f(512,384), sf::Vector2f(1024, 768)));

}

//render 
void MainMenu::render()
{
	beginDraw();
	window->draw(menuScreen);
	//window->draw(playButton);
	endDraw();
}

void MainMenu::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void MainMenu::endDraw()
{
	window->display();
}
