#include "Gladiator.h"

Gladiator::Gladiator(AudioManager* aud)
{
	// intitialise audio pointer
	audio = aud;
	
	
	// setting up idle animation
	stand.addFrame(sf::IntRect(0, 0, 32, 32));
	stand.addFrame(sf::IntRect(32, 0, 32, 32));
	stand.addFrame(sf::IntRect(64, 0, 32, 32));
	stand.addFrame(sf::IntRect(96, 0, 32, 32));
	stand.addFrame(sf::IntRect(128, 0, 32, 32));
	stand.setFrameSpeed(1.f / 10.f); // set frame rate

	// setting up walk animation
	walk.addFrame(sf::IntRect(0, 32, 32, 32));
	walk.addFrame(sf::IntRect(32, 32, 32, 32));
	walk.addFrame(sf::IntRect(64, 32, 32, 32));
	walk.addFrame(sf::IntRect(96, 32, 32, 32));
	walk.addFrame(sf::IntRect(128, 32, 32, 32));
	walk.addFrame(sf::IntRect(160, 32, 32, 32));
	walk.addFrame(sf::IntRect(192, 32, 32, 32));
	walk.addFrame(sf::IntRect(224, 32, 32, 32));
	walk.setFrameSpeed(1.f / 10.f); // set frame rate

	//setting up damaged annimation
	damaged.addFrame(sf::IntRect(0, 96, 32, 32));
	damaged.addFrame(sf::IntRect(32, 96, 32, 32));
	damaged.addFrame(sf::IntRect(64, 96, 32, 32));
	damaged.setFrameSpeed(1.f / 10.f); // set frame rate

	//setting up the attack animation
	attack.addFrame(sf::IntRect(0, 64, 32, 32));
	attack.addFrame(sf::IntRect(32, 64, 32, 32));
	attack.addFrame(sf::IntRect(64, 64, 32, 32));
	attack.addFrame(sf::IntRect(96, 64, 32, 32));
	attack.addFrame(sf::IntRect(128, 64, 32, 32));
	attack.setFrameSpeed(1.f / 10.f); // set frame rate

	//setting up the death animation
	death.addFrame(sf::IntRect(0, 128, 32, 32));
	death.addFrame(sf::IntRect(32, 128, 32, 32));
	death.addFrame(sf::IntRect(64, 128, 32, 32));
	death.addFrame(sf::IntRect(96, 128, 32, 32));
	death.addFrame(sf::IntRect(128, 128, 32, 32));
	death.addFrame(sf::IntRect(160, 128, 32, 32));
	death.addFrame(sf::IntRect(192, 128, 32, 32));
	death.setFrameSpeed(1.f / 3.f); // set frame rate
	death.setLooping(false); // so the player doesn't repeatedly die

	currentAnimation = &stand; // set the default animation to idle
	setTextureRect(currentAnimation->getCurrentFrame());

	// set the initial sped
	x_speed = 85;
	y_speed = 85;
	
	// setup health
	playerHealth = 100;
	// setup how much damage the player can take
	playerDamage = 5;
	// set the player alive
	isDead = false;
	// the player currently has no buffs
	increasedDamage = false;
	increasedSpeed = false;

	// set all the counter/timers to an initial value of 0
	soundCooldown = 0; // counter to control sound effects
	collectableCooldown = 0; // counter to control the pickups
	timeCount = 0; // a general timer counter
	collectBoolCount = 0; // a count tracking the variable 

	// reset the buffs
	buffed = false;
	buffType = 0;

	srand(time(0)); // seed the random

	
}

Gladiator::~Gladiator() {} // destructor


// a reset function 
void Gladiator::reset() 
{
	// reset the animation
	currentAnimation = &stand;
	setTextureRect(currentAnimation->getCurrentFrame());

	//reset the speed
	x_speed = 85;
	y_speed = 85;

	// reset int variables
	timeCount = 0;
	collectableCooldown = 0;
	soundCooldown = 0;
	collectBoolCount = 0;
	buffType = 0;
	playerHealth = 100;
	playerDamage = 5;

	// reset bool values
	isDead = false;
	increasedDamage = false;
	increasedSpeed = false;
	buffed = false;
	
}

// returns the damage value
int Gladiator::getDamage()
{
	return playerDamage;
}

// sets the damage value
void Gladiator::setDamage(int d)
{
	playerDamage = d;
}

// sets the speed variables
void Gladiator::setSpeed(int s)
{
	x_speed = s;
	y_speed = s;
}

// returns true if the player's health is at 0; hence they are 'dead'
bool Gladiator::checkHealth()
{
	if (playerHealth <= 0)
	{
		return true;
	}
	
	return false;
}

// returns the health value
int Gladiator::getHealth()
{
	return playerHealth;
}

// adds onto the players health
void Gladiator::addHealth(int h)
{
	playerHealth = playerHealth + h;
}

// decreases the player's health
void Gladiator::takeDamage(float dt)
{

	if (timeCount <= 0.5)
	{
		audio->playSoundbyName("playerDamage");
		playerHealth = playerHealth - 5;

	}
}

// returns an integer number that indicates what buff the player has
int Gladiator::getBuff()
{
	return buffType;
}

// returns true if the player is buffed
bool Gladiator::isBuffed()
{
	return buffed;
}

// called when the player dies
void Gladiator::die(float dt)
{
	
	x_speed = 0; // sets the speed to 0 so the player can't move
	y_speed = 0;
	currentAnimation = &death; // play the death animation
	currentAnimation->animate(dt);
	setTextureRect(currentAnimation->getCurrentFrame());
}

void Gladiator::handleInput(float dt)
{
	soundCooldown += dt; // increment the cooldown timer

	//move up
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		if (soundCooldown >= 0.5)
		{
			audio->playSoundbyName("walk"); // play the walking sound
			soundCooldown = 0; // reset the timer for the sound so it isn't overlapping itself
		}

		move(0, -y_speed * dt);  
	}

	//move down
	if (input->isKeyDown(sf::Keyboard::Down))
	{
		if (soundCooldown >= 0.5)
		{
			audio->playSoundbyName("walk"); // play the walking sound
			soundCooldown = 0; // reset the timer for the sound so it isn't overlapping itself
		}

		move(0, y_speed * dt);
	}

	//move left
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		if (soundCooldown >= 0.5)
		{
			audio->playSoundbyName("walk"); // play the walking sound
			soundCooldown = 0; // reset the timer for the sound so it isn't overlapping itself
		}

		move(-x_speed * dt, 0);
		currentAnimation->setFlipped(true); // flip the animatoin so the player is facing the correct direction
	}

	//move right
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		if (soundCooldown >= 0.5)
		{
			audio->playSoundbyName("walk"); // play the walking sound
			soundCooldown = 0; // reset the timer for the sound so it isn't overlapping itself
		}

		move(x_speed * dt, 0);
		currentAnimation->setFlipped(false); // don't flip 
	}


}

void Gladiator::update(float dt)
{
	// increment timers
	timeCount += dt;
	collectableCooldown += dt;

	// check if the gladiator has an active buff; if yes acitvate the timer and control buffed state

	if (buffType == 1) // added health buff 
	{
		collectBoolCount += dt; // increment the buff timer
		buffed = true; // set the buffed bool to true 
		if (collectBoolCount >= 5) // after five seconds
		{
			collectBoolCount = 0; // set the timer back to zero
			buffType = 0; // de-buff the player
			buffed = false; // set the buffed bool back to false 
		}
	}
	else if (increasedDamage == true) // increased damage buff
	{
		collectBoolCount += dt; // increment the buff timer
		setDamage(10); // set the amount of damage the player can deal to 
		buffed = true; // set the buffed bool to true 
		if (collectBoolCount >= 5) // after five seconds
		{
			setDamage(5); // reset the damage back to 5
			increasedDamage = false; // set the increased damage bool to false
			collectBoolCount = 0; // reset the timer
			buffType = 0; // de-buff the player
			buffed = false; // set the buffed bool back to false
		}
	}
	else if (increasedSpeed == true) // increased speed buff
	{
		collectBoolCount += dt; // increment the buff timer
		buffed = true; // set the buffed bool to true
		setSpeed(120); // set the player's speed to 120
		if (collectBoolCount >= 5) // after five seconds
		{
			setSpeed(85); // set the speed back to the defualt 
			increasedSpeed = false; // set he increased speed bool to false
			collectBoolCount = 0; // reset timer
			buffType = 0; // de-buff the player
			buffed = false; // set the buffed bool back to false
		}
	}

	// setting the animation when a key is pressed

	if (input->isKeyDown(sf::Keyboard::Up)) // up
	{
		currentAnimation = &walk;
		setTextureRect(currentAnimation->getCurrentFrame());
	}
	else if (input->isKeyDown(sf::Keyboard::Down)) // down 
	{
		
		currentAnimation = &walk;
		setTextureRect(currentAnimation->getCurrentFrame());
	}
	else if (input->isKeyDown(sf::Keyboard::Left)) // left
	{
		
		currentAnimation = &walk;
		setTextureRect(currentAnimation->getCurrentFrame());
	}
	else if (input->isKeyDown(sf::Keyboard::Right)) // right
	{
		
		currentAnimation = &walk;
		setTextureRect(currentAnimation->getCurrentFrame());
	}
	else //idling
	{
		currentAnimation = &stand;
		setTextureRect(currentAnimation->getCurrentFrame());
	}


	if (input->isKeyDown(sf::Keyboard::Space)) // player attack
	{
		currentAnimation = &attack; // set the animation to attack
		currentAnimation->animate(dt);
		setTextureRect(currentAnimation->getCurrentFrame());
	}
	else
	{
		attack.reset(); // reset the attack animtion 
	}

	currentAnimation->animate(dt); // animate
	setTextureRect(currentAnimation->getCurrentFrame());

}

void Gladiator::idle(float dt)
{
	currentAnimation = &stand;
	currentAnimation->animate(dt); // animate
	setTextureRect(currentAnimation->getCurrentFrame());
}


// when the player collides with the enemy
void Gladiator::enemyCollisionResponse(GameObject* Collider, float dt) 
{

	// this is so the player is slightly pushed back from the enemywhen they collide, preventing them from walking over each other
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		move(0, (y_speed-10) * dt);
	}
	if (input->isKeyDown(sf::Keyboard::Down))
	{
		move(0, (-y_speed-10) * dt);
	}
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		move((x_speed+10) * dt, 0);
		currentAnimation->setFlipped(true);
	}
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		move((-x_speed-10) * dt, 0);
		currentAnimation->setFlipped(false);
	}

	if (timeCount >= 1.5) // creates a cooldown time so the player can't be constantly taking damage from the enemy
	{
		timeCount = 0; // reset the timer
		int damageChance= (rand() % 100) + 1; // generate a random number 
		if (damageChance < 70) //  a 70% chance to hit the player, so the player doesnt constantly take damage whenever they collide
		{
			audio->playSoundbyName("damage"); // play the damage sound
			currentAnimation = &damaged; // set the animation to damaged
			takeDamage(dt); // decreases the players health
			currentAnimation->animate(dt); // animate
			setTextureRect(currentAnimation->getCurrentFrame());
			
		}
		
	}
	
	
}

// for when the player collides with the wine collectable that gives buffs
void Gladiator::wineCollisionResponse(GameObject* Collider, float dt)
{
	if (collectableCooldown >= 2) // if the cooldown is over two secs
	{
		collectableCooldown = 0; // reset the cooldown

		int collectableChance = (rand() % 3) + 1; // generate a random number to decide which buff is given

		if (collectableChance <= 1) // the additional health buff
		{
			addHealth(5); // add five health to the player
			buffType = 1; // change the bufftype to 1

		}
		else if (collectableChance <= 2) // the increased damage buff
		{
			increasedDamage = true; // set increaseddmage to true
			buffType = 2; // set the bufftype to 2

		}
		else if (collectableChance <= 3) // increased speed buff 
		{
			increasedSpeed = true; // increasedspeed is true
			buffType = 3; // set the bufftype to three 

		}
		
	}
}

// player/arena collision responce to jeep the player inside the arena 
void Gladiator::arenaCollisionResponse(GameObject* Collider)
{
	// new x y coords 
	int newX = 0; 
	int newY = 0;

	// current x y coords
	int currentX = 0;
	int currentY = 0;

	// new position is calculated based on what buttons are being pressed

	if (input->isKeyDown(sf::Keyboard::Up) && input->isKeyDown(sf::Keyboard::Left)) // north west
	{

		// get the players coords
		currentX = getPosition().x;
		currentY = getPosition().y;

		//set them the new coords to a position inside the arena 
		newX = currentX + 8;
		newY = currentY + 8;

		// set the new coords
		setPosition(newX, newY);

	}else if (input->isKeyDown(sf::Keyboard::Up) && input->isKeyDown(sf::Keyboard::Right)) //north east
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newX = currentX - 8;
		newY = currentY + 8;
		setPosition(newX, newY);

	}else if (input->isKeyDown(sf::Keyboard::Down) && input->isKeyDown(sf::Keyboard::Left)) // south west
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newX = currentX + 8;
		newY = currentY - 8;
		setPosition(newX, newY);


	}else if (input->isKeyDown(sf::Keyboard::Down) && input->isKeyDown(sf::Keyboard::Right)) // south east
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newX = currentX - 8;
		newY = currentY - 8;
		setPosition(newX, newY);


	}else if (input->isKeyDown(sf::Keyboard::Up)) // north
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newY = currentY + 8;
		setPosition(currentX, newY);


	}else if (input->isKeyDown(sf::Keyboard::Down)) // south
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newY = currentY - 8;
		setPosition(currentX, newY);


	} else if (input->isKeyDown(sf::Keyboard::Left)) // east
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newX = currentX + 8;
		setPosition(newX, currentY);

	} else if (input->isKeyDown(sf::Keyboard::Right)) // east
	{
		currentX = getPosition().x;
		currentY = getPosition().y;
		newX = currentX - 8;
		setPosition(newX, currentY);

	}

}

