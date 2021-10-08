#include "FullWineCollectable.h"

FullWineCollectable::FullWineCollectable(AudioManager* aud)
{
	//initialise pointer 
	audio = aud;
	//set alive to false 
	isAlive = false;
	//set bottles collected to 0
	bottlesCollected = 0;
	//set timer to 0
	timer = 0;
	// seed the random
	srand(time(0)); 
}

//destructor 
FullWineCollectable::~FullWineCollectable() {}

//reset
void FullWineCollectable::reset()
{
	bottlesCollected = 0; //set bottlescollected to 0
}

// return 'points' value 
int FullWineCollectable::getPoints()
{
	return bottlesCollected; //set bottlescollected to 0 
}

// return if bottle is alive 
bool FullWineCollectable::bottleAlive()
{
	return isAlive;
}

// calculate the spwanpoint of the bottle 
void FullWineCollectable::calculateSpawn() 
{
	// get random coords within arena bounds 
	int x = rand() % 481 + 187;
	int y = rand() % 254 + 247;

	spawnPoint = sf::Vector2f(x, y); // set the random spwan point

}

//player collsision
void FullWineCollectable::playerCollision(GameObject* Collider, float dt)
{
	timer = 0; // set timer to 0
	isAlive = false; // the bottle is no longer alive
	bottlesCollected++; // increment bottlescollected 
}

//handleinput 
void FullWineCollectable::handleInput(float dt)
{
	if (isAlive == false)
	{
		calculateSpawn(); // cycle a new spawn whilst its not alive 
	}

	if (timer >= 5) // after five seconds
	{
		isAlive = true; // make it alive
		timer = 0; // reset timer
	}
}

void FullWineCollectable::update(float dt)
{
	timer += dt; // increment timer 

	if (isAlive == true)
	{
		setPosition(sf::Vector2f(spawnPoint)); // set the spawn pos
	}

}

