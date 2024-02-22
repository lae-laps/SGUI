#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "button.hpp"

#define WIDTH 1400
#define HEIGHT 800

/*	Super messy code
 *	add highlight when on top
 *	add click functionality
 *	center text correctly
 */

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
