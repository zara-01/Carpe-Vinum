#include "Splash.h"

Splash::Splash(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud):splashGladiator(aud)
{
	// init pointers
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// initial load in of audio files
	audio->addMusic("sfx/grassyWorld.ogg", "grassyWorld");
	audio->addMusic("sfx/drunken sailor.ogg", "sailor");
	audio->addMusic("sfx/Victory.ogg", "victory");
	audio->addMusic("sfx/lose.ogg", "lose");

	audio->addSound("sfx/Minecraft-gravel2.ogg", "walk");
	audio->addSound("sfx/Hit_01.wav-270326.ogg", "damage");
	audio->addSound("sfx/8-bit_Pickup.aif-170170.ogg", "pickup");
	audio->addSound("sfx/8_Bit_Slam-361636.ogg", "playerDamage");

	//load in objects and textures 

	splashTexture.loadFromFile("gfx/splashScreen.png");

	splashScreen.setTexture(&splashTexture);
	splashScreen.setSize(sf::Vector2f(1024, 768));
	splashScreen.setPosition(0, 0);

	gladiatorTexture.loadFromFile("gfx/GladiatorSheet.png");
	splashGladiator.setSize(sf::Vector2f(192, 192));
	splashGladiator.setPosition(288, 288);
	splashGladiator.setTexture(&gladiatorTexture);
	splashGladiator.setSpeed(0);
	splashGladiator.setInput(input);

	// init default variables
	timer = 0;
}

Splash::~Splash()
{
	//destructor
}

//handle input 
void Splash::handleInput(float dt)
{
	//splashGladiator.handleInput(dt);

	// Close window on Escape pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

}

//update
void Splash::update(float dt)
{
	splashGladiator.idle(dt);

	timer += dt; // increment timer 
	if (timer >= 5) // after five secs
	{
		gameState->setCurrentState(State::MENU); // go to menu state 
	}

	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768))); //set view 
}

// render 
void Splash::render()
{
	beginDraw();

	window->draw(splashScreen);
	window->draw(splashGladiator);

	endDraw();
}

void Splash::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

void Splash::endDraw()
{
	window->display();
}
