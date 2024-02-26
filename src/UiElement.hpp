#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

class UiElement {
public:
	
	virtual void draw() {
	}

	virtual void manageEvent(sf::Event *event) {
	}

private:

	sf::Vector2f position;

};

#endif

