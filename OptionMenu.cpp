#include "OptionMenu.h"

OptionMenu::OptionMenu(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :soundGladiator(aud)
{
	// init pointers 
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// initialise game objects and textures 

	optionTexture.loadFromFile("gfx/optionControlScreen.png");

	optionScreen.setTexture(&optionTexture);
	optionScreen.setSize(sf::Vector2f(1024, 768));
	optionScreen.setPosition(0, 0);

	backButton.setSize(sf::Vector2f(234, 85));
	backButton.setPosition(41, 660);
	backButton.setFillColor(sf::Color::Transparent);
	backButton.setOutlineColor(sf::Color::Red);
	backButton.setOutlineThickness(2.f);

	gladiatorTexture.loadFromFile("gfx/EnemySheet.png");
	soundGladiator.setSize(sf::Vector2f(110, 110));
	soundGladiator.setPosition(853, 220);
	soundGladiator.setTexture(&gladiatorTexture);
	soundGladiator.setSpeed(0);
	soundGladiator.setInput(input);

	// init default variables 
	musicOn = true;
	cooldown = 2;

}

OptionMenu::~OptionMenu()
{
	// destructor 
}

// is music playing or not 
bool OptionMenu::isMusicEnabled()
{
	return musicOn;
}

// handleinput 
void OptionMenu::handleInput(float dt)
{
	cooldown += dt; // increment cooldown

	// Close window on Escape pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

	// when the gladiator is clicked switch states
	if (soundGladiator.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))) && input->isMouseLDown())
	{
		if (cooldown >= 1) // a cooldown so it isn't constantl flicking between 
		{
			if (musicOn == true) // switch off music 
			{
				audio->playSoundbyName("pickup");
				cooldown = 0;
				audio->setMusicVolume(0);
				musicOn = false;
				
			}
			else if (musicOn == false) // switch on music
			{
				audio->playSoundbyName("pickup");
				cooldown = 0;
				audio->setMusicVolume(50);
				musicOn = true;
				
			}

		}
		

	}

	// if the back button is clicked return to the main menu 
	if (backButton.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		if (input->isMouseLDown())
		{
			audio->playSoundbyName("pickup"); // play pickup noise 
			gameState->setCurrentState(State::MENU); // return to meny state
		}

	}
}

void OptionMenu::update(float dt)
{
	// play an animation based on the music state 
	if (musicOn == true)
	{
		soundGladiator.update(dt);
	}
	else if (musicOn == false)
	{
		soundGladiator.die(dt);
	}
	//set view 
	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768)));

}

//render
void OptionMenu::render()
{
	beginDraw();
	window->draw(optionScreen);
	window->draw(soundGladiator);
	endDraw();
}

void OptionMenu::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void OptionMenu::endDraw()
{
	window->display();
}
