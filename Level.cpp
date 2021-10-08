#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) :arenaFloor(hwnd),gladiator(aud),enemy(aud),wine(aud),fullWine(aud)
{
	// init pointers
	window = hwnd; 
	input = in;
	gameState = gs;
	audio = aud;

	// init variables to their default 
	timeCount = 0;
	playerBuffed = false;

	// load the text 
	if (!font.loadFromFile("font/Super Mario Bros. 2.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	// set the font 
	playerHealth.setFont(font);
	playerPoints.setFont(font);
	enemyHealth.setFont(font);
	buffDisplay.setFont(font);


	// initialise game objects

	gladiatorTexture.loadFromFile("gfx/GladiatorSheet.png");
	gladiator.setSize(sf::Vector2f(64, 64));
	gladiator.setCollisionBox(sf::FloatRect(0, 0, 28, 42));
	gladiator.setPosition(599, 386);
	gladiator.setTexture(&gladiatorTexture);
	gladiator.setInput(input);

	enemyTexture.loadFromFile("gfx/EnemySheet.png");
	enemy.setSize(sf::Vector2f(64, 64));
	enemy.setCollisionBox(sf::FloatRect(0, 0, 28, 42)); 
	enemy.setPosition(272, 228);
	enemy.setTexture(&enemyTexture);
	enemy.setInput(input);

	backdrop.loadFromFile("gfx/Arena.png");
	map.setTexture(&backdrop);
	map.setSize(sf::Vector2f(1024, 768));
	map.setPosition(0, 0);
	
	arena_floor.loadFromFile("gfx/ArenaFloor.png");
	arenaFloor.setTexture(&arena_floor);
	arenaFloor.setSize(sf::Vector2f(1024, 768));
	arenaFloor.setCollisionBox(sf::FloatRect(sf::Vector2f(158, 196), sf::Vector2f(697, 311)));
	arenaFloor.setPosition(0, 0);

	wineTexture.loadFromFile("gfx/WineBottle.png");
	wine.setSize(sf::Vector2f(40, 20));
	wine.setCollisionBox(sf::FloatRect(0, 0, 40, 20));
	wine.setTexture(&wineTexture);
	wine.setInput(input);

	fullWineTexture.loadFromFile("gfx/FullWineBottle.png");
	fullWine.setSize(sf::Vector2f(40, 20));
	fullWine.setCollisionBox(sf::FloatRect(0, 0, 40, 20));
	fullWine.setTexture(&fullWineTexture);;
	fullWine.setInput(input);
	
}

Level::~Level() {} // destructor 

// get and return the player's 'points' from the fullWine object
int Level::getPlayerPoints()
{
	int p = fullWine.getPoints();
	return p;
}

//reselt everything to thir defaults 
void Level::reset()
{
	timeCount = 0;
	playerBuffed = false;
	gladiator.reset();
	gladiator.setPosition(599, 386);
	enemy.reset();
	enemy.setPosition(272, 228);
	wine.reset();
	fullWine.reset();
}

// a function to set up the strings 
void Level::textSetup()
{
	// get the player's health 
	int x = gladiator.getHealth();
	std::string x_string = std::to_string(x); // convert to string
	// get the enemy's health 
	int z = enemy.getEnemyHealth();
	std::string z_string = std::to_string(z); // convert to string
	// get the 'points'
	int p = fullWine.getPoints();
	std::string p_string = std::to_string(p); // convert to string

	int b = gladiator.getBuff(); // get the buff value 
	std::string b_string;

	// display the type of buff the player currently has
	if (b == 1)
	{
		/*b_string = std::to_string(b);*/
		b_string = "+5 Health!";
	}
	else if (b == 2)
	{
		/*b_string = std::to_string(b);*/
		b_string = "+5 Damage!";
	}
	else if (b == 3)
	{
		/*b_string = std::to_string(b);*/
		b_string = "Speed!";
	}
	else
	{
		/*b_string = std::to_string(b);*/
		b_string = "not buffed";
	}

	// set the strings, sizes, colours, and positions 

	playerHealth.setString("Caligula " + x_string);
	playerHealth.setCharacterSize(20);
	playerHealth.setFillColor(sf::Color::White);
	playerHealth.setPosition(10, 10);

	playerPoints.setString("Wine Siezed " + p_string);
	playerPoints.setCharacterSize(20);
	playerPoints.setFillColor(sf::Color::White);
	playerPoints.setPosition(39, 700);

	enemyHealth.setString("Bibulus " + z_string);
	enemyHealth.setCharacterSize(20);
	enemyHealth.setFillColor(sf::Color::White);
	enemyHealth.setPosition(791, 10);

	buffDisplay.setString("Buff Type: " + b_string);
	buffDisplay.setCharacterSize(20);
	buffDisplay.setFillColor(sf::Color::White);
	buffDisplay.setPosition(520, 700);

}

// handle user input
void Level::handleInput(float dt)
{
	// Close window on Escape pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		audio->playSoundbyName("pickup"); // play pickup sound 
		gameState->setCurrentState(State::PAUSE); // go to pause state 
	}

	// call the text function 
	textSetup(); 

	// handle object inputs 
	gladiator.handleInput(dt);
	wine.handleInput(dt);
	fullWine.handleInput(dt);
	
}

// Update game objects
void Level::update(float dt)
{
	//updates
	wine.update(dt);
	fullWine.update(dt);
	gladiator.update(dt);
	
	// move the enemt depending on whether or not the player is buffed 
	if (gladiator.isBuffed()==true)
	{
		enemy.moveRandom(dt, gladiator.getPosition()); // move away from the player when they are buffed
		
	}
	else
	{
		enemy.findPlayer(gladiator.getPosition().x, gladiator.getPosition().y, dt); // move towards the player if they are not buffed 
	}


	// COLLISION RESPONSES // 

	if (Collision::checkBoundingBox(&gladiator, &enemy)) // check for a collison between the player and the enemy 
	{
		gladiator.enemyCollisionResponse(NULL, dt); // player collision responce 

		if (gladiator.isBuffed() == false)
		{
			enemy.playerCollisionResponse(NULL, dt); // if the player is not buffed use default collision response
		}
		else
		{
			enemy.altCollisionResponse(NULL, dt); // if the player is buffed use the alt collision responce
		}
		
		// if space is pressed whilst the enemy and player are colliding 
		if (input->isKeyDown(sf::Keyboard::Space))
		{
			enemy.getPlayerDamage(gladiator.getDamage()); // get the amount of damage the player can deal
 			enemy.enemyTakeDamage(dt); // the enemy takes damage 
		}

	}

	// a collision check to keep the player within the bounnds of the arena 
	if (!Collision::checkBoundingBox(&gladiator, &arenaFloor)) // if the player is NOT colliding with the arena floor 
	{
		gladiator.arenaCollisionResponse(NULL); // arena collision response 
	}

	// a collision check to keep the enemy within the bounnds of the arena
	if (!Collision::checkBoundingBox(&enemy, &arenaFloor))  // if the enemy is NOT colliding with the arena floor 
	{
		enemy.arenaCollisionResponse(NULL); // arena collision response 
	}
	else
	{
		enemy.notArenaColliding();
	}

	//collision between the player and the bottles that give buffs 
	if (Collision::checkBoundingBox(&gladiator, &wine)) //  a collision check for the half empty bottles of wine that give buffs
	{
		if (wine.bottleAlive()) // if the bottle is alive 
		{
			wine.playerCollision(NULL, dt); // make the bottle disappear
			gladiator.wineCollisionResponse(NULL, dt); // give the player a buff
			audio->playSoundbyName("pickup"); // play the pickup sound 
		}
		
	}

	//collision between the player and the bottle that gives points 
	if (Collision::checkBoundingBox(&gladiator, &fullWine)) // a collision check for the full wine bottles to allocate points
	{
		if (fullWine.bottleAlive()) //if the bottle is alive 
		{
			fullWine.playerCollision(NULL, dt); // make the bottle disappear 
			audio->playSoundbyName("pickup"); // play the pickup noise 
		}
	}

	// if the enemy has died
	if (enemy.checkHealth()) 
	{
		enemy.die(dt); // enem dies 
		timeCount += dt; // a timer for the animation to play 

		if (timeCount >= 3) // once the timer is over three 
		{
			audio->playMusicbyName("victory"); // play the victory music 
			gameState->setCurrentState(State::WIN); // switch to win state 
		}
	}

	// if the player has died
	if (gladiator.checkHealth()) 
	{
		gladiator.die(dt); //player dies 
		timeCount += dt; // a timer for the animation to play 

		if (timeCount >= 3) // once the timer is over three
		{
			audio->playMusicbyName("lose"); // play the losing music 
			gameState->setCurrentState(State::DEATH); // switch to losing state 
		}
	}

	//set view 
	window->setView(sf::View(sf::Vector2f(512, 384), sf::Vector2f(1024, 768)));

}

// Render level
void Level::render()
{
	beginDraw();
	
	// draw the map
	window->draw(arenaFloor);
	window->draw(map);

	// if the bottle is alive, draw it 
	if (wine.bottleAlive())
	{
		window->draw(wine);
	}
	// if the bottle is alive, draw it 
	if (fullWine.bottleAlive())
	{
		window->draw(fullWine);
	}

	// draw the characters 
	window->draw(enemy);
	window->draw(gladiator);
	//draw the points, health and buff stats 
	window->draw(playerPoints);
	window->draw(playerHealth);
	window->draw(enemyHealth);
	window->draw(buffDisplay);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}