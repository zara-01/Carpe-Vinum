#include "WineCollectable.h"

WineCollectable::WineCollectable(AudioManager* aud)
{
	//init pointers
	audio = aud;

	// set default variables
	isAlive = false; // not alive 
	buff = 0; // no buffed
	timer = 0; // timer is at zero
	srand(time(0)); // seed the random
}

WineCollectable::~WineCollectable() {} // destructor 

//reset
void WineCollectable::reset()
{
	timer = 0; //reset timer to default 
}

// where the bottle will spawn 
void WineCollectable::calculateSpawn() // calculate a spawn point between these numbers
{
	// generate a random coord within the bounds of the arena floor 
	int x = rand() % 481 + 187; 
	int y = rand() % 254 + 247;

	spawnPoint = sf::Vector2f(x, y); // set the random spwan point

}

//handle input 
void WineCollectable::handleInput(float dt)
{
	if (isAlive == false) // if the bottle is not alive 
	{
		calculateSpawn(); // cycle a new spawn
	}

	if (timer >= 10) // after every ten seconds
	{
		isAlive = true; // make it alive
		timer = 0; // reset timer
	}
}

//update 
void WineCollectable::update(float dt)
{
	timer += dt; // increment timer 

	if (isAlive == true)
	{
		setPosition(sf::Vector2f(spawnPoint)); // set the spawn pos
	}

}

// return whether or not the bottle is alive 
bool WineCollectable:: bottleAlive()
{
	return isAlive;
}

// player collision response
void WineCollectable::playerCollision(GameObject* Collider, float dt)
{
	timer = 0; // set the timer to 0
	isAlive = false; // kill the bottle 

}