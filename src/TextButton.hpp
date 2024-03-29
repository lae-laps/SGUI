#ifndef TEXT_BUTTON_HPP
#define TEXT_BUTTON_HPP

#include <SFML/Window/Event.hpp>
#include <array>
#include <optional>
#include <SFML/Graphics.hpp>

#include "UiElement.hpp"
#include "BoxContainerShape.hpp"

/*	Since there are so many options neccesary for a completely-customizable button, we create a struct to mantain config
 *	This is also good, as a struct can be created, and many similar buttons can be created easilly
 *	TODO:
 *		- better shadows with a slope
 */

struct TextButtonProperties {

	std::array<sf::Color, 4> innerColor;
	std::array<sf::Color, 4> rimColor;
	std::array<unsigned int, 4> rimThickness;
	std::array<unsigned int, 4> shadowThickness;
	std::array<unsigned int, 4> fontSize;
	sf::Font *font;

	std::array<unsigned int, 4> cornerCuts;
	unsigned int cornerRadius;

	// remain in clicked state or return inmediatelly to normal state
	bool remainClickedLeft;
	bool remainClickedRight;

	// change button size when text is changed
	bool resizeOnChangeText;

	//std::array<std::string, 4> texts;
	//std::array<std::unique_ptr<sf::Sprite>, 3> sprites;

};

// specifiedDimensions is not needed, if it is set as NULL, the constructor will decide the adecuate dimensions

class TextButton : public UiElement {
public:

    // constructor
    TextButton(const std::string text, const TextButtonProperties &properties, const sf::Vector2f position, const std::optional<sf::Vector2f> specifiedDimensions = std::nullopt) 
        : innerColor(properties.innerColor), 
          rimColor(properties.rimColor),
          rimThickness(properties.rimThickness),
          shadowThickness(properties.shadowThickness),
          fontSize(properties.fontSize),
          font(properties.font),
          remainClickedLeft(properties.remainClickedLeft),
          remainClickedRight(properties.remainClickedRight),
          cornerRadius(properties.cornerRadius),
          cornerCuts(properties.cornerCuts),
          resizeOnChangeText(properties.resizeOnChangeText),
          position(position),
          text(text),
          state(0)																	// Default to normal state
    {
	
		// CREATE LABEL

		label = sf::Text();
		//label.setString(text);
		label.setPosition(position);
		if (font)
			label.setFont(*font);

		setText(text);	

		// CREATE BOXES
    
		// assign the dimensions parameter, or optionally if it doesnt exist, asign a default one
		//dimensions = specifiedDimensions.value_or(sf::Vector2f(0.75f * fontSize[state] * text.size(), 50));
		dimensions = calculateBoxBoundFromText();

		box.set(dimensions, cornerRadius, cornerCuts);	
		box.setPosition(position);

		shadow.set(dimensions, cornerRadius, cornerCuts);
		shadow.setFillColor(sf::Color(20, 20, 20));										// TODO: fix this

		// SET MISC

		lastLeftClickWasInside = false;
		lastRightClickWasInside = false;

		// SET STATE

		setState(state);															// initialize button to state 0
		lastState = state;															// set lastState to 0 for the specific case where button spawns with pointer inside it
    }

    // change the state
    void setState(const int newState) {
    	lastState = state;
    	state = newState;
		box.setFillColor(innerColor[state]);	
		box.setOutlineColor(rimColor[state]);	
		box.setOutlineThickness(rimThickness[state]);
		label.setCharacterSize(fontSize[state]);
		shadow.setPosition(
			sf::Vector2f(
				position.x + shadowThickness[state], 
				position.y + shadowThickness[state]
			)
		);
    	onStateChange(newState);
    }

	sf::Vector2f calculateBoxBoundFromText() {
		//sf::FloatRect textBounds = label.getLocalBounds();
		sf::FloatRect textBounds = label.getGlobalBounds();
			//TODO: add paddings
		return sf::Vector2f(sf::Vector2f(textBounds.width, textBounds.height));
	}

    void setText(const std::string newText) {
		label.setString(newText);
		if (resizeOnChangeText) {
			box.setSize(calculateBoxBoundFromText());
		}
    }

    // override this to define custom behaviour
    virtual void onStateChange(const int i) {
		//std::cout << "new state: " << i << std::endl;
    }

	// bool
	/*int clickInsideElement(const float x, const float y) {
		return (x > position.x && x < position.x + dimensions.x && y > position.y && y < position.y + dimensions.y);
	} */

	virtual void manageEvent(const sf::Event *event) {
		switch (event->type) {
			case sf::Event::MouseButtonPressed:		// mouse click
				// handle mouse click
				switch (event->mouseButton.button) {
					case sf::Mouse::Left:
						if (box.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {

							lastLeftClickWasInside = true;

							// clicked button -> set state to 2 (left click)
							//if (remainClickedLeft && (lastState == 2 || state == 2))
							if (state == 2 || lastState == 2)
								setState(0);
							else 
								setState(2);
						} else {
							lastLeftClickWasInside = false;
						}
						break;
					case sf::Mouse::Right:
						if (box.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {

							lastRightClickWasInside = true;

							// clicked button -> set state to 3 (right click)
							//if (remainClickedRight && (lastState == 3 || state == 3)) 
							if (state == 3 || lastState == 3)
								setState(0);
							else
								setState(3);
						} else {
							lastRightClickWasInside = false;
						}
						break;
					default:
						break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				switch (event->mouseButton.button) {
					case sf::Mouse::Left:	
						if (lastLeftClickWasInside && !remainClickedLeft)
							setState(0);
						break;
					case sf::Mouse::Right:
						if (lastRightClickWasInside && !remainClickedRight)
							setState(0);
						break;
					default:
						break;
				}
			case sf::Event::MouseMoved:
				if (box.isInsideElement(event->mouseMove.x, event->mouseMove.y)) {
					// mouse inside button -> set state to 1 (highlighted)
					// we have to remember previous state to return to it
					if (state != 1) {
						setState(1);
					}
				} else {
					// mouse outside button -> set state to 0 (normal)
					if (state == 1)
						setState(lastState);
				}
				break;
			default:
				break;
		}
	}
	
	virtual void draw(sf::RenderWindow &window) {

		// clean non-persistent states
		//if ((!remainClickedLeft && state == 2) || (!remainClickedRight && state == 3))
		//	setState(0);

		if (shadowThickness[state] != 0)
			window.draw(shadow);
		window.draw(box);
		window.draw(label);
	}

private:

	// state
	// 0 -> normal
	// 1 -> highlighted
	// 2 -> clicked left
	// 3 -> clicked right
	int state;

	int lastState;	// buffer for highlight state

	std::string text;

	bool remainClickedLeft;
	bool remainClickedRight;

	bool resizeOnChangeText;

	std::array<sf::Color, 4> innerColor;
	std::array<sf::Color, 4> rimColor;
	std::array<unsigned int, 4> rimThickness;
	std::array<unsigned int, 4> shadowThickness;
	std::array<unsigned int, 4> cornerCuts;
	unsigned int cornerRadius;
	std::array<unsigned int, 4> fontSize;
	sf::Font *font;

	//sf::RectangleShape box;
	//sf::RectangleShape shadow;
	BoxContainerShape box;
	BoxContainerShape shadow;

	sf::Text label;

	sf::Vector2f position;
	sf::Vector2f dimensions;

	bool lastLeftClickWasInside;
	bool lastRightClickWasInside;

};

#endif

