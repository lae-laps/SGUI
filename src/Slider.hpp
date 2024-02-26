#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "UiElement.hpp"
#include "BoxContainerShape.hpp"

#include <array>
#include <SFML/Graphics.hpp>

// TODO: add wheel control

struct SliderProperties {

	double min;
	double max;

	double initialValue;

	bool showSelector;
	bool showIncrementors;

	int incrementorWidth;
	sf::Vector2f baseDimensions;
	sf::Vector2f selectorDimensions;

	std::array<int, 6> baseRimThickness;
	std::array<int, 6> selectorRimThickness;

	std::array<sf::Color, 6> baseFillColorLeft;
	std::array<sf::Color, 6> baseFillColorRight;
	std::array<sf::Color, 6> baseRimColor;
	std::array<sf::Color, 6> selectorFillColor;
	std::array<sf::Color, 6> selectorRimColor;
	std::array<sf::Color, 6> incrementorBackgroundColor;
	std::array<sf::Color, 6> incrementorArrowColor;

	int baseCornerRadius;
	int selectorCornerRadius;

};

class Slider : public UiElement {
public:

	Slider(const SliderProperties &properties, const sf::Vector2f position_) 
		: min(properties.min),
		  max(properties.max),
		  showSelector(properties.showSelector),
		  showIncrementors(properties.showIncrementors),
		  incrementorWidth(properties.incrementorWidth),
		  baseDimensions(properties.baseDimensions),
		  selectorDimensions(properties.selectorDimensions),
		  baseFillColorLeft(properties.baseFillColorLeft),
		  baseFillColorRight(properties.baseFillColorRight),
		  baseRimColor(properties.baseRimColor),
		  baseRimThickness(properties.baseRimThickness),
		  selectorRimThickness(properties.selectorRimThickness),
		  selectorFillColor(properties.selectorFillColor),
		  selectorRimColor(properties.selectorRimColor),
		  incrementorBackgroundColor(properties.incrementorBackgroundColor),
		  incrementorArrowColor(properties.incrementorArrowColor),
		  baseCornerRadius(properties.baseCornerRadius),
		  selectorCornerRadius(properties.selectorCornerRadius)
	{

		base.set(baseDimensions, baseCornerRadius);	
		selector.set(selectorDimensions, selectorCornerRadius);
		leftBase.set(
			sf::Vector2f(valueToWidth(properties.initialValue), baseDimensions.y), 
			baseCornerRadius
		);

		position = position_;
		base.setPosition(position);
		leftBase.setPosition(position);

		// initialize slider with initial value
		setCurrent(properties.initialValue);

		setState(0);

	}


	void setState(const int newState) {
		state = newState;

		// set colors

		base.setOutlineThickness(baseRimThickness[state]);
		selector.setOutlineThickness(selectorRimThickness[state]);

		leftBase.setFillColor(baseFillColorLeft[state]);
		base.setFillColor(baseFillColorRight[state]);

		leftBase.setOutlineColor(baseRimColor[state]);
		base.setOutlineColor(baseRimColor[state]);
		
		if (showSelector) {
			selector.setFillColor(selectorFillColor[state]);
			selector.setOutlineColor(selectorRimColor[state]);
		}
		if (showIncrementors) {
			leftIncrementor.setFillColor(incrementorBackgroundColor[state]);
			rightIncrementor.setFillColor(incrementorBackgroundColor[state]);
		}

		onStateChange(state);

	}

	virtual void onStateChange(const int i) {
		// pass	
	}

	double widthToValue(const double width) {
		return min + (width * (max - min)) / baseDimensions.x;
	}

	double valueToWidth(const double val) {
		return (baseDimensions.x / (max - min)) * (val - min);
	}

	// get value of Slider
	double getCurrent() {
		return current;
	}	

	// set value of Slider
	virtual void setCurrent(const float val) {
		if (val == current)
			return;
		current = val;
		selector.setPosition(
			sf::Vector2f(
					position.x + valueToWidth(current),
					position.y - baseDimensions.y / 4
				)
			);
		leftBase.setSize(
			sf::Vector2f(
					valueToWidth(current),
					baseDimensions.y
				)
			);
	}

	virtual void draw(sf::RenderWindow &window) {

		window.draw(base);
		window.draw(leftBase);

		if (showSelector) {
			window.draw(selector);
		}

		if (showIncrementors) {
			window.draw(leftIncrementor);
			window.draw(rightIncrementor);
		}
	}

	virtual void manageEvent(const sf::Event *event) {
		switch (event->type) {
			case sf::Event::MouseButtonPressed:
				switch (event->mouseButton.button) {
					case sf::Mouse::Left:
						if (selector.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {
							setState(4);
						} else if (base.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {
							setCurrent(widthToValue(event->mouseButton.x - position.x));	
							setState(4);
						}
						break;
					case sf::Mouse::Right:
						if (base.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {
							setState(5);
						}
						break;
					default:
						break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event->mouseButton.button == sf::Mouse::Left) {
					if (state == 4) {
						setState(0);
					}
				}
				break;
			case sf::Event::MouseMoved:
				if (state == 4) {
					setCurrent(widthToValue(event->mouseMove.x - position.x));
				}
				break;
			default:
				break;
		}
	}

private:

	// state
	// 0 -> normal
	// 1 -> highlight base
	// 2 -> hightlight left incrementor
	// 3 -> highlight right incrementor
	// 4 -> click left
	// 5 -> click right
	int state;

	double min;
	double max;
	double current;

	bool showSelector;
	bool showIncrementors;


	std::array<int, 6> baseRimThickness;
	std::array<int, 6> selectorRimThickness;

	BoxContainerShape base;
	BoxContainerShape selector;

	BoxContainerShape leftBase;

	BoxContainerShape leftIncrementor;
	BoxContainerShape rightIncrementor;

	int incrementorWidth;
	sf::Vector2f baseDimensions;
	sf::Vector2f selectorDimensions;

	std::array<sf::Color, 6> baseFillColorLeft;
	std::array<sf::Color, 6> baseFillColorRight;
	std::array<sf::Color, 6> baseRimColor;
	std::array<sf::Color, 6> selectorFillColor;
	std::array<sf::Color, 6> selectorRimColor;
	std::array<sf::Color, 6> incrementorBackgroundColor;
	std::array<sf::Color, 6> incrementorArrowColor;

	int baseCornerRadius;
	int selectorCornerRadius;

	// positions
	
	sf::Vector2f position;

	sf::Vector2f basePosition;
	sf::Vector2f selectorPosition;

};

#endif

