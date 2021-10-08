#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/AudioManager.h"
#include "Framework/Vector.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>  /* srand, rand */
#include <time.h>  // time



class Enemy : public GameObject
{
public:
	//contrusctor&destructor
	Enemy(AudioManager* aud);
	~Enemy();

	//return the enemy health value
	int getEnemyHealth();

	//collision responses
	void playerCollisionResponse(GameObject* Collider, float dt); // when the enemy collides with the player
	void arenaCollisionResponse(GameObject* Collider); // when the enemy collides with the arena 
	void notArenaColliding(); // when not colliding 
	void altCollisionResponse(GameObject* Collider, float dt); // an alt collision response that runs under certain conditions

	//move functions 
	void findPlayer(int playerX, int playerY, float dt); //move towards the player
	void moveRandom(float dt, sf::Vector2f gladiator); //move away from the player 

	//attack the player 
	void attackPlayer(GameObject* Collider, float dt);

	//getting hit by the player 
	void enemyTakeDamage(float dt);
	void enemyGetHit();

	//return the enemy's health value 
	bool checkHealth();

	//recieve the amount of damage the enemy should take using a variable passed in from player through level
	void getPlayerDamage(int d);

	//for when the enemy dies
	void die(float dt);

	//reset everythin to it's default 
	void reset();


protected:

	//speed variables 
	float currentSpeed;
	float maxSpeed;

	// health and damage variables
	int enemyHealth;
	int damage;
	
	//timers
	float enemyTimeCount;
	float walkTimer;
	//if dead or not
	bool isDead;

	// if they need to use the special/alt collision
	bool specialColliding;
	
	// point vectors 
	sf::Vector2f pointA;
	sf::Vector2f pointB;
	sf::Vector2f direction;

	// objects and animations 
	AudioManager* audio;

	Animation* currentAnimation;

	Animation walk;
	Animation stand;
	Animation damaged;
	Animation attack;
	Animation death;

};

