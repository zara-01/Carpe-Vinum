#include "Enemy.h"

Enemy::Enemy(AudioManager* aud)
{
	audio = aud;

	// setting up animations

	//idling
	stand.addFrame(sf::IntRect(0, 0, 32, 32));
	stand.addFrame(sf::IntRect(32, 0, 32, 32));
	stand.addFrame(sf::IntRect(64, 0, 32, 32));
	stand.addFrame(sf::IntRect(96, 0, 32, 32));
	stand.addFrame(sf::IntRect(128, 0, 32, 32));
	stand.setFrameSpeed(1.f / 10.f);
	//walk
	walk.addFrame(sf::IntRect(0, 32, 32, 32));
	walk.addFrame(sf::IntRect(32, 32, 32, 32));
	walk.addFrame(sf::IntRect(64, 32, 32, 32));
	walk.addFrame(sf::IntRect(96, 32, 32, 32));
	walk.addFrame(sf::IntRect(128, 32, 32, 32));
	walk.addFrame(sf::IntRect(160, 32, 32, 32));
	walk.addFrame(sf::IntRect(192, 32, 32, 32));
	walk.addFrame(sf::IntRect(224, 32, 32, 32));
	walk.setFrameSpeed(1.f / 10.f);
	//damaged
	damaged.addFrame(sf::IntRect(0, 96, 32, 32));
	damaged.addFrame(sf::IntRect(32, 96, 32, 32));
	damaged.addFrame(sf::IntRect(64, 96, 32, 32));
	damaged.setFrameSpeed(1.f / 10.f);
	//attack
	attack.addFrame(sf::IntRect(0, 64, 32, 32));
	attack.addFrame(sf::IntRect(32, 64, 32, 32));
	attack.addFrame(sf::IntRect(64, 64, 32, 32));
	attack.addFrame(sf::IntRect(96, 64, 32, 32));
	attack.addFrame(sf::IntRect(128, 64, 32, 32));
	attack.setFrameSpeed(1.f / 10.f);
	//death
	death.addFrame(sf::IntRect(0, 128, 32, 32));
	death.addFrame(sf::IntRect(32, 128, 32, 32));
	death.addFrame(sf::IntRect(64, 128, 32, 32));
	death.addFrame(sf::IntRect(96, 128, 32, 32));
	death.addFrame(sf::IntRect(128, 128, 32, 32));
	death.addFrame(sf::IntRect(160, 128, 32, 32));
	death.addFrame(sf::IntRect(192, 128, 32, 32));
	death.setFrameSpeed(1.f / 3.f);
	death.setLooping(false);
	//set the default animation to idling 
	currentAnimation = &stand;
	setTextureRect(currentAnimation->getCurrentFrame());

	//set deafult speed varibles 
	maxSpeed = 60; 
	currentSpeed = 0; 
	//set the default health and damage values 
	enemyHealth = 100;
	damage = 5;

	//set the enemy to alive (not dead)
	isDead = false;
	//set the timer to 0
	enemyTimeCount = 0;
	//set the special collide to flase
	specialColliding = false;

	srand(time(0)); // seed the random
}

Enemy::~Enemy() {} // destructor 

// reset
void Enemy::reset()
{
	// set animation to idlde
	currentAnimation = &stand;
	setTextureRect(currentAnimation->getCurrentFrame());
	// reset speed vals 
	maxSpeed = 60;
	currentSpeed = 0;
	//reset damage val
	damage = 5;
	// reset health 
	enemyHealth = 100;
	// reset bools and timer 
	isDead = false;
	specialColliding = false;
	enemyTimeCount = 0;
}

// play attack animation 
void Enemy::attackPlayer(GameObject* Collider, float dt)
{
	currentAnimation = &attack; // set animation to attack 
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

}

// take damage from the player 
void Enemy::enemyTakeDamage(float dt)
{
	if (enemyTimeCount >= 1.5) // creates a cooldown time so the player can't be constantly taking damage from the enemy
	{
		enemyTimeCount = 0; // reset the timer 
		audio->playSoundbyName("damage"); // play the enemy damage sound 
		currentAnimation = &damaged; // set the damage animatin 
		enemyGetHit(); // call the enemyGetHit function to take damage
		currentAnimation->animate(dt);
		setTextureRect(currentAnimation->getCurrentFrame());
	}

}

// return the health value 
int Enemy::getEnemyHealth()
{
	return enemyHealth;
}

// check the health to see if he is dead or alive, returns a boolean value 
bool Enemy::checkHealth()
{
	if (enemyHealth <= 0)
	{
		return true;
	}

	return false;
}

// take damage 
void Enemy::enemyGetHit()
{
	if (enemyTimeCount <= 0.5) // if the timer is less then 0.5 secs
	{
		enemyHealth = enemyHealth - damage; // take damage

	}
}

// retreive the amount of damage the enemy can take by passing in the value from player through level 
void Enemy::getPlayerDamage(int d)
{
	damage = d; // set the damage 
}

// called when the enemy is dead 
void Enemy::die(float dt)
{
	//set the speed to 0
	maxSpeed = 0;
	currentSpeed = 0;
	//play death animation
	currentAnimation = &death;
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
}

// move towards the player 
void Enemy::findPlayer(int playerX, int playerY, float dt) // essentially enemy update function
{
	// increment timers 
	enemyTimeCount += dt;
	walkTimer += dt;

	// get the current pos
	pointA = (sf::Vector2f(getPosition()));
	// get the player's pos 
	pointB = sf::Vector2f(playerX, playerY);

	// calc direction and velocity 
	direction = pointB - pointA;
	direction = Vector::normalise(direction); // normalise 
	velocity = (direction * currentSpeed) * dt;

	//acceleration
	if (currentSpeed < maxSpeed)
	{
		currentSpeed += 3.f;
	}

	// make sure the enemy sprite flips to the correct direction
	if (pointA.x > pointB.x) 
	{
		currentAnimation->setFlipped(true);
	}
	else
	{
		currentAnimation->setFlipped(false);
	}

	// move the enemy 
	move(velocity.x, 0);
	move(0, velocity.y);

	// set the current animation to walk 
	currentAnimation = &walk;
	setTextureRect(currentAnimation->getCurrentFrame());
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());

	
}

//alt collision response 
void Enemy::altCollisionResponse(GameObject* Collider, float dt)
{
	currentSpeed = 0; //set the speed to 0 
	attackPlayer(Collider, dt); // attack the player
}

//player collision response 
void Enemy::playerCollisionResponse(GameObject* Collider, float dt)
{	
	currentSpeed = -10; // set the speed to -10
	attackPlayer(Collider, dt); // attack the player 
}

//arena collision response 
void Enemy::arenaCollisionResponse(GameObject* Collider)
{
	specialColliding = true; // set special collide to true 
	//currentSpeed = -10; // set the speed to -10

}

// the antie arena collision response
void Enemy::notArenaColliding()
{
	specialColliding = false; // set special collide to false
}

void Enemy::moveRandom(float dt, sf::Vector2f gladiator) // get the enemy to move away from wherever the player is 
{

	pointA = (sf::Vector2f(getPosition())); // get current pos
	pointB = sf::Vector2f(gladiator); // get gladiator pos
	

	if (currentSpeed < maxSpeed) // acceleration
	{
		currentSpeed += 3.f;
	}

	// calc direction and velocity 
	direction = pointB - pointA;
	direction = Vector::normalise(direction);
	velocity = (direction * currentSpeed) * dt;

	// make sure the enemy flips to the correct direction
	if (pointA.x < pointB.x) 
	{
		currentAnimation->setFlipped(true);
	}
	else
	{
		currentAnimation->setFlipped(false);
	}

	//move the enemy 
	move(-velocity.x, 0);
	if (specialColliding==true)
	{
		move(velocity.x, 0); // allows the enemy to slide along the wall without clipping
	}

	move(0, -velocity.y);
	if (specialColliding==true)
	{
		move(0, velocity.y); // allows the enemy to slide along the wall without clipping
	}

	// set walk animation 
	currentAnimation = &walk;
	setTextureRect(currentAnimation->getCurrentFrame());
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
}

