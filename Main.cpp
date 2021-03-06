// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "MainMenu.h"
#include "OptionMenu.h"
#include "Pause.h"
#include "WinScreen.h"
#include "DeathScreen.h"
#include "Splash.h"
#include "infoScreens.h"

int main()
{
	int x = 1024;
	int y = 768;

	//Create the window
	sf::RenderWindow window(sf::VideoMode((x), (y)), "CARPE VINUM");
	

	// Initialise input and level objects.
	Input input;
	GameState gameState;
	AudioManager audioManager;

	Level level(&window, &input, &gameState, &audioManager);
	MainMenu menu(&window, &input, &gameState, &audioManager);
	OptionMenu option(&window, &input, &gameState, &audioManager);
	Pause pause(&window, &input, &gameState, &audioManager);
	DeathScreen death(&window, &input, &gameState, &audioManager);
	WinScreen win(&window, &input, &gameState, &audioManager);
	Splash splash(&window, &input, &gameState, &audioManager);
	infoScreens info(&window, &input, &gameState, &audioManager);

	// Initialise objects for delta time

	sf::Clock clock;
	float deltaTime;

	gameState.setCurrentState(State::SPLASH);

	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();

		if (gameState.getCurrentState() == State::SPLASH)
		{
			splash.handleInput(deltaTime);
			splash.update(deltaTime);
			splash.render();
			menu.reset();
		}
		else if (gameState.getCurrentState() == State::MENU)
		{
			level.reset();
			info.reset();
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
		}
		else if (gameState.getCurrentState() == State::INFO)
		{

			info.handleInput(deltaTime);
			info.update(deltaTime);
			info.render();

		}
		else if (gameState.getCurrentState() == State::LEVEL)
		{
			// Call standard game loop functions (input, update and render)
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();
		}
		else if (gameState.getCurrentState() == State::OPTIONS)
		{
			option.handleInput(deltaTime);
			option.update(deltaTime);
			option.render();
		}
		else if (gameState.getCurrentState() == State::PAUSE)
		{
			pause.handleInput(deltaTime);
			pause.update(deltaTime);
			pause.render();
			
		}
		else if (gameState.getCurrentState() == State::WIN)
		{
			
			win.setFinalPoints(level.getPlayerPoints());
			win.handleInput(deltaTime);
			win.update(deltaTime);
			win.render();
			menu.reset();
			if (win.getReplay() == true)
			{
				win.reset();
				level.reset();
			}

		}
		else if (gameState.getCurrentState() == State::DEATH)
		{

			death.handleInput(deltaTime);
			death.update(deltaTime);
			death.render();
			menu.reset();
			if (death.getReplay() == true)
			{
				win.reset();
				level.reset();
			}
		}
	}

}

