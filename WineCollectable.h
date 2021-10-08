#pragma once
#include "Framework/GameObject.h"
#include "Framework/AudioManager.h"
#include "Enemy.h"
#include "Gladiator.h"
#include <stdlib.h>  /* srand, rand */
#include <time.h>  // time

class WineCollectable: public GameObject
{
public:
	//constructor/destructor
	WineCollectable(AudioManager* aud);
	~WineCollectable();
	// handleInput, update, render
	void handleInput(float dt);
	void update(float dt);
	void reset();
	//calculate the spawn point 
	void calculateSpawn();
	//plauer collision 
	void playerCollision(GameObject* Collider, float dt);
	//is the bottle alive 
	bool bottleAlive(); // returns if the bottle has been collected or not
	


private:
	//objects
	AudioManager* audio;

	//variables 
	bool isAlive; // tracks if the bottle is alive 
	int buff; 
	float timer; // timer

	sf::Vector2f spawnPoint; //spawnpoint 

};