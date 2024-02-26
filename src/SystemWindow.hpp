#ifndef SYSTEM_WINDOW_HPP
#define SYSTEM_WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "UiElement.hpp"

class Window {
public:


private:

	sf::Vector2f dimensions;

	std::vector<UiElement> elements;

};

#endif

