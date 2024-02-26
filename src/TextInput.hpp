#ifndef TEXT_INPUT_HPP
#define TEXT_INPUT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "UiElement.hpp"
#include "BoxContainerShape.hpp"

struct TextInputProperties {

	std::string defaultText;

	int cursorWidth;
	int cornerRadius;
	sf::Vector2f dimensions;
	std::array<int, 4> rimThickness;

	sf::Color cursorColor;
	sf::Color highlightedColor;
	std::array<sf::Color, 4> fillColor;
	std::array<sf::Color, 4> rimColor;
	std::array<sf::Color, 4> textColor;

	int fontSize;
	sf::Font *font;

	bool allowEmptyInput;

	// set to 0 for unlimited
	int maxInputSize;

};

class TextInput : public UiElement {
public:

	TextInput(const TextInputProperties &properties, const sf::Vector2f position_) 
		: defaultText(properties.defaultText),
		  cursorWidth(properties.cursorWidth),
		  cornerRadius(properties.cornerRadius),
		  dimensions(properties.dimensions),
		  rimThickness(properties.rimThickness),
		  cursorColor(properties.cursorColor),
		  highlightedColor(properties.highlightedColor),
		  fillColor(properties.fillColor),
		  rimColor(properties.rimColor),
		  textColor(properties.textColor),
		  fontSize(properties.fontSize),
		  font(properties.font),
		  allowEmptyInput(properties.allowEmptyInput),
		  maxInputSize(properties.maxInputSize),
		  position(position_)
	{

		box.set(dimensions, cornerRadius);
		box.setPosition(position);

		cursor.setSize(sf::Vector2f(cursorWidth, static_cast<float>(fontSize)));
		cursor.setFillColor(cursorColor);
		cursor.setPosition(position);

		if (font)
			label.setFont(*font);

		label.setCharacterSize(fontSize);
		label.setPosition(position);

		// seters

		cursorPosition = 0;
		setText(defaultText);
		state = -1;							// so that state == newState doesnt go off first time
		setState(0);

	}

	virtual void setState(const int newState) {
		if (state == newState)
			return;
		state = newState;

		box.setOutlineThickness(rimThickness[state]);

		box.setOutlineColor(rimColor[state]);
		box.setFillColor(fillColor[state]);
		label.setFillColor(textColor[state]);

		if (state != 2 && input.empty()) {
			setText(defaultText);			// set text back to the default only if the input is empty
		}

	}

	void setText(const std::string text) {

		label.setString(text);

	}

	int setCursorPosition(const int newPosition) {
		if (newPosition < 0 || newPosition > input.size())
			return -1;

		cursorPosition = newPosition;

		//std::string textBeforeCursor = input.substr(0, cursorPosition);
		//int x = label.findCharacterPos(textBeforeCursor.size()).x;
		
		float textWidth = 0.0f;
		for (int i = 0; i < cursorPosition; i++) {
			// Get the character code
			unsigned int charCode = input[i];
			// Get the corresponding glyph in the font
			const sf::Glyph& glyph = font->getGlyph(charCode, fontSize, false);
			// Add the glyph's advance to the total text width
			textWidth += glyph.advance;
		}	

		cursor.setPosition(
			sf::Vector2f(
				position.x + textWidth,
				position.y
			)
		);

		return 0;

	}

	void addCharacterToInput(const char c) {
		if (input.size() == maxInputSize && maxInputSize != 0)	// dont add on max size
			return;
		input.insert(cursorPosition, 1, c);			// note, 1 is as we only insert once
		setCursorPosition(cursorPosition + 1);
	}

	void removeCharacterFromInput() {
		if (input.empty())							// ignore if already empty
			return;
		input.erase(cursorPosition - 1, 1);				// only erase 1 char
		setCursorPosition(cursorPosition - 1);
	}
	
	virtual void draw(sf::RenderWindow &window) {
		
		window.draw(box);
		window.draw(label);

		if (state == 2)
			window.draw(cursor);

	}

	virtual void onEnter() {
		// override this
		std::cout << "entered text: " << input << std::endl;
	}

	virtual void manageEvent(sf::Event *event) {
		switch (event->type) {
			case sf::Event::TextEntered:
				if (state == 2) {
					//std::cout << static_cast<char>(event->text.unicode) << std::endl;
					// Check if the entered character is ASCII and not a control character (like backspace)
					if (event->text.unicode < 128 && event->text.unicode != '\b') {
						// Append the entered character to the input string
						//input += static_cast<char>(event->text.unicode);
						addCharacterToInput(static_cast<char>(event->text.unicode));
						// Update the text object with the new input string
						setText(input);
					} else if (event->text.unicode == '\b') {
						// Handle backspace: Remove the last character from the input string
						removeCharacterFromInput();
						// Update the text object with the modified input string
						setText(input);
					}
				}

				break;

			// set Esc and Enter as the key to get out of input mode
			case sf::Event::KeyPressed:
				switch (event->key.code) {
					case sf::Keyboard::Enter:
						if (state == 2) {
							if (input.empty() && !allowEmptyInput) {
								break;
							}
							onEnter();								// call override function for input
						}
						setState(0);								// get out of input
						break;
					case sf::Keyboard::Escape:
						setState(0);								// get out of input
						break;
					case sf::Keyboard::Left:
						setCursorPosition(cursorPosition - 1);		// move cursor left
						break;
					case sf::Keyboard::Right:
						setCursorPosition(cursorPosition + 1);		// move cursor right
						break;
					default:
						break;
				}
			break;

			case sf::Event::MouseButtonPressed:
				switch (event->mouseButton.button) {
					case sf::Mouse::Left:
						if (box.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {
							setState(2);
							setText(input);
						}
						break;
					case sf::Mouse::Right:
						if (box.isInsideElement(event->mouseButton.x, event->mouseButton.y)) {
							setState(3);
						}
						break;
					default:
						break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event->mouseButton.button == sf::Mouse::Left) {
					if (state == 3) {
						setState(0);
					}
				}
				break;
			case sf::Event::MouseMoved:
				if (box.isInsideElement(event->mouseMove.x, event->mouseMove.y)) {
					if (state == 0) {
						setState(1);
					}
				} else {
					if (state == 1) {
						setState(0);
					}
				}
				break;
			default:
				break;
		}


	}

private:

	int state;

	std::string defaultText;

	std::string input;
	int cursorPosition;

	sf::Vector2f position;

	BoxContainerShape box;
	sf::Text label;
	sf::RectangleShape cursor;
	//sf::RectangleShape highlight;


	int cursorWidth;
	int cornerRadius;
	sf::Vector2f dimensions;
	std::array<int, 4> rimThickness;

	sf::Color cursorColor;
	sf::Color highlightedColor;
	std::array<sf::Color, 4> fillColor;
	std::array<sf::Color, 4> rimColor;
	std::array<sf::Color, 4> textColor;

	int fontSize;
	sf::Font *font;

	bool allowEmptyInput;
	int maxInputSize;

};

#endif

