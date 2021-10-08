#pragma once
#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"
#include "Enemy.h"
#include "Gladiator.h"
#include <stdlib.h>  /* srand, rand */
#include <time.h>  // time

class FullWineCollectable: public GameObject
{
public:

	//constructor&destructor
	FullWineCollectable(AudioManager* aud);
	~FullWineCollectable();

	//handlInput, update & reset 
	void handleInput(float dt);
	void update(float dt);
	void reset();

	// calculate the spawnpoint of the bottle 
	void calculateSpawn();
	//player collision response
	void playerCollision(GameObject* Collider, float dt);

	bool bottleAlive(); // returns if the bottle has been collected or not
	int getPoints(); // returns the number of bottles that have been collected

private:
	//intitialise audio
	AudioManager* audio;
	//initialise variables
	bool isAlive; // bool keeps track of the bottle's state
	int bottlesCollected; // keeps track of how many has been collected 
	float timer; //a timer that increments with dt
	sf::Vector2f spawnPoint; //spawnpoint
};