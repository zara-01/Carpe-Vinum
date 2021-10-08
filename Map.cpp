#include "Map.h"

Map::Map(sf::RenderWindow* hwnd) 
{ // constructor
	viewX = 600.f;
	window = hwnd;
	sf::View view(sf::Vector2f(250, 338), sf::Vector2f(float(window->getSize().x), float(window->getSize().y))); //set view 
}

Map::~Map() { // destructor

}

// if theres a scrolling map 
void Map::scrollMap(float dt) { 
	 
	if (input->isKeyDown(sf::Keyboard::A)) {
		viewX -= 50 * dt;
	}
	else if (input->isKeyDown(sf::Keyboard::D)) {
		viewX += 50 * dt;
	}
}

//update 
void Map::update() {
	sf::View view(sf::Vector2f(viewX, 338), sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
	window->setView(view);
}
