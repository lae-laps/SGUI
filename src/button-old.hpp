#ifndef BUTTON_HPP
#define BUTTON_HPP

class Button {
	public:

		Button (sf::Color innerColor, sf::Color outerColor, sf::Color highlightInnerColor, sf::Color highlightOuterColor, size_t outerThickness, size_t shadowThickness, std::string str, sf::Vector2f pos, sf::Font *font, size_t fontSize) {

			setFontSize(fontSize);
			setText(str);
			setPosition(pos);

			setColor(innerColor, outerColor, highlightInnerColor, highlightOuterColor);
			setOuterThickness(outerThickness);

			setFont(font);

			setShadow(shadowThickness);
		}
		

		void updateColor(int mode) {
			// mode -> 0 = Normal / 1 = Highlight
			if (mode == 0) {
				box.setFillColor(innerColor);
				box.setOutlineColor(outerColor);

			} else {
				box.setFillColor(highlightInnerColor);
				box.setOutlineColor(highlightOuterColor);
			}
		}

		// N = normal / H = highlight
		void setColor(sf::Color NinnerColor, sf::Color NouterColor, sf::Color HinnerColor, sf::Color HouterColor) {

			innerColor = NinnerColor;
			outerColor = NouterColor;
			highlightInnerColor = HinnerColor;
			highlightOuterColor = HouterColor;

			//box.setFillColor(NinnerColor);
			//box.setOutlineColor(NouterColor);
			updateColor(0);
		}

		void setText(std::string str) {
			text.setString(str);
			// 1 font size point = 0.75 pixels
			// TODO: find this constant well
			box.setSize(sf::Vector2f(0.75 * fontSize * str.length(), 40));
			shadow.setSize(box.getSize());
		}

		void setPosition(sf::Vector2f position) {
			box.setPosition(position);
			text.setPosition(position);
			text.move(10, 8);
		}

		void setFont(sf::Font *font) {
			text.setFont(*font);
		}

		void setFontSize(size_t size) {
			text.setCharacterSize(size);
			fontSize = size;
		}

		void setOuterThickness(size_t thickness) {
			box.setOutlineThickness(thickness);
		}

		void setShadow(size_t thickness) {
			shadow.setSize(box.getSize());
			shadow.setPosition(box.getPosition());
			shadow.move(sf::Vector2f(thickness, thickness));
			shadow.setFillColor(sf::Color(20, 20, 20));
		}

		// bool
		int clickInsideElement(float x, float y) {
			sf::Vector2f boxPos = box.getPosition();
			sf::Vector2f boxSize = box.getSize();
			return (x > boxPos.x && x < boxPos.x + boxSize.x && y > boxPos.y && y < boxPos.y + boxSize.y);
		} 

		void draw(sf::RenderWindow &window) {
			window.draw(shadow);
			window.draw(box);
			window.draw(text);
		}

		void manageEvent(sf::Event *event) {
			switch (event->type) {
				case sf::Event::MouseButtonPressed:		// mouse click
					// handle mouse click

					// get position
					//int x = event->mouseButton.x;
					//int y = event->mouseButton.y;
					
					// x and y are in event->mouseButton.x / y

					switch (event->mouseButton.button) {
						case sf::Mouse::Left:
							if (clickInsideElement(event->mouseButton.x, event->mouseButton.y)) {
								setText("clicked me");
							} else {
								setText("didnt click me");
							}
							break;
						case sf::Mouse::Right:
							setText("right mouse click");
							break;
						default:
							break;
					}
					break;
				case sf::Event::MouseMoved:
					if (clickInsideElement(event->mouseMove.x, event->mouseMove.y)) {
						//box.setOutlineColor(sf::Color(200, 10, 10));
						updateColor(1);
					} else {
						updateColor(0);
					}
					break;
				case sf::Event::Closed:					// close call from user
					//window.close();
					break;
				case sf::Event::LostFocus:				// window not in focus
					break;
				case sf::Event::GainedFocus:			// window in focus again
					break;
				default:
					break;
			}
		}

private:
	//std::string text;
	//sf::Color color;

	sf::Text text;
	sf::RectangleShape box;
	sf::RectangleShape shadow;

	sf::Color innerColor;
	sf::Color outerColor;
	sf::Color highlightInnerColor;
	sf::Color highlightOuterColor;

	size_t fontSize;
};

#endif

