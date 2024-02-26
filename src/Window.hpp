#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "UiElement.hpp"
#include "BoxContainerShape.hpp"

class Window {
public:


private:

	sf::Vector2f position;
	sf::Vector2f dimensions;

	BoxContainerShape box;
	
	std::vector<UiElement> elements;

};

#endif

