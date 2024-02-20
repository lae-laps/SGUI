#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 1400
#define HEIGHT 800

/*	Super messy code
 *	add highlight when on top
 *	add click functionality
 *	center text correctly
 */


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

int main() {

    // create main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GUI Test", sf::Style::Default);

	// load fonts
	
	sf::Font defaultFont;
	if (!defaultFont.loadFromFile("/usr/share/fonts/TTF/FiraCode-Regular.ttf")) {
		std::cout << "could not find system fonts : TODO: add local fonts to project" << std::endl;	
	}

	// button
	
	Button button1(sf::Color(60, 220, 100), sf::Color(60, 220, 100), sf::Color(60, 220, 100), sf::Color(100, 255, 180), 5, 12, "Pulsame y un texto mas largo !!", sf::Vector2f(40, 40), &defaultFont, 16);
	Button button2(sf::Color(100, 100, 240), sf::Color(112, 255, 128), sf::Color(130, 130, 255), sf::Color(0, 0, 0), 0, 8, "Este es un texto muy muy largo para probar como funciona \n TODO: añadir multiline support", sf::Vector2f(40, 200), &defaultFont, 16);
	Button button3(sf::Color(40, 40, 250), sf::Color(20, 20, 150), sf::Color(40, 40, 250), sf::Color(255, 40, 40), 3, 0, "text", sf::Vector2f(40, 400), &defaultFont, 16);

	// predefine event
	sf::Event event;

    // main loop
	while (window.isOpen()) {

		// get new events and parse each one untill there is no more
        while (window.pollEvent(event)) {
            // switch over sf::Event(s) union
            // keypress and mouse first for speed

            button1.manageEvent(&event);
            button2.manageEvent(&event);
            button3.manageEvent(&event);
            
			switch (event.type) {
				case sf::Event::KeyPressed:				// key (pressed)
					// handle keypress
					switch (event.key.code) {
						case sf::Keyboard::Escape:		// close on Esc
							window.close();
							break;
						case sf::Keyboard::Key::W:
							//y -= delta;
							break;
						case sf::Keyboard::Key::A:
							//x -= delta;
							break;
						case sf::Keyboard::Key::S:
							//y += delta;
							break;
						case sf::Keyboard::Key::D:
							//x += delta;
							break;
						default:
							//statusIndicator.setString("pressed key");
							break;
					}
					break;
				case sf::Event::MouseButtonPressed:		// mouse click
					// handle mouse click
					switch (event.mouseButton.button) {
						case sf::Mouse::Left:
							//statusIndicator.setString("left mouse click");
							break;
						case sf::Mouse::Right:
							//statusIndicator.setString("right mouse click");
							break;
						default:
							break;
					}
					break;
				case sf::Event::Closed:					// close call from user
					window.close();
					break;
				case sf::Event::LostFocus:				// window not in focus
					break;
				case sf::Event::GainedFocus:			// window in focus again
					break;
				default:
					break;
			}
        }
 
        // clear screen
        window.clear(sf::Color(255, 255, 255));

		// draw buffer

		button1.draw(window);
		button2.draw(window);
		button3.draw(window);
		//window.draw(button.box);

        // update the window
        window.display();
    }

    // cleanup
 
    return 0;
}
