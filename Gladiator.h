#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/AudioManager.h"
#include "Enemy.h"
#include <stdlib.h>  /* srand, rand */
#include <time.h>  // time

class Gladiator : public GameObject
{
public:
	Gladiator(AudioManager* aud); // constructor
	~Gladiator(); // destructor

	void handleInput(float dt); // handleinput

	void update(float dt) override; // update
	void idle(float dt); // just makes the gladiator idle

	// collision responses
	void arenaCollisionResponse(GameObject* Collider); // arena collision response
	void enemyCollisionResponse(GameObject* Collider, float dt); // enemy collision response
	void wineCollisionResponse(GameObject* Collider, float dt); // collectable collision response 
	void takeDamage(float dt); // taking damage

	// setting the speed
	void setSpeed(int s);

	// getting health and damage values
	int getHealth();
	int getDamage();

	// adding/setting to damage and health
	void addHealth(int h);
	void setDamage(int d);
	// checking if the player is still alive
	bool checkHealth();

	// getting/checking buffs
	int getBuff();
	bool isBuffed();

	//for when the player dies
	void die(float dt);
	//reset values
	void reset();

protected:

	//buff variables
	bool buffed;
	int buffType;
	//speed variables
	int x_speed;
	int y_speed;
	//damage variable
	int playerDamage;
	//health variable
	int playerHealth;
	//timer/countdown variables 
	float timeCount;
	float soundCooldown;
	float collectableCooldown;
	float collectBoolCount;
	//bool variables for buffs
	bool isDead;
	bool increasedDamage;
	bool increasedSpeed;

	// objects and animations

	AudioManager* audio;
	
	Animation* currentAnimation;

	Animation walk;
	Animation stand;
	Animation damaged;
	Animation attack;
	Animation death;

	
};