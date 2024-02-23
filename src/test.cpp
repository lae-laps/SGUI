#include <iostream>
#include <SFML/Graphics.hpp>

#include "TextButton.hpp"
#include "BoxContainerShape.hpp"

#define WIDTH 1400
#define HEIGHT 800

int main() {

	// set antialising
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

    // create main window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "GUI Test", sf::Style::Default, settings);

	// load fonts
	
	sf::Font defaultFont;
	if (!defaultFont.loadFromFile("/usr/share/fonts/TTF/FiraCode-Regular.ttf")) {
		std::cout << "could not find system fonts : TODO: add local fonts to project" << std::endl;	
	}

	// buttons

    //TextButtonProperties properties;

    // Create a text button with properties
    TextButton button1("Click me", 
		TextButtonProperties {
			.innerColor = {sf::Color(80, 120, 200), sf::Color(100, 180, 255), sf::Color(100, 180, 255), sf::Color(100, 180, 255)},
			.rimColor = {sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black},
			.rimThickness = {0, 0, 0, 0},
			.shadowThickness = {10, 10, 10, 10},
			.fontSize = {20, 20, 20, 20},			// Change the font size as needed
			.font = &defaultFont,
			.remainClickedLeft = 0,
			.remainClickedRight = 0

		},
		sf::Vector2f(100, 100)
		);

    TextButton button2("A button with a large text", 
		TextButtonProperties {
			.innerColor = {sf::Color::Blue, sf::Color::Blue, sf::Color::Blue, sf::Color::Blue},
			.rimColor = {sf::Color(20, 20, 100), sf::Color(50, 50, 200), sf::Color(20, 20, 100), sf::Color(20, 20, 100)},
			.rimThickness = {9, 9, 9, 9},
			.shadowThickness = {20, 20, 20, 20},
			.fontSize = {20, 20, 20, 20},			// Change the font size as needed
			.font = &defaultFont,
			.remainClickedLeft = 1,
			.remainClickedRight = 0

		},
		sf::Vector2f(100, 300)
		);

    TextButton button3("STOP", 
		TextButtonProperties {
			.innerColor = {sf::Color::Blue, sf::Color::Yellow, sf::Color::Red, sf::Color::Green},
			.rimColor = {sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black},
			.rimThickness = {2, 2, 2, 2},
			.shadowThickness = {20, 20, 20, 20},
			.fontSize = {20, 20, 20, 20},			// Change the font size as needed
			.font = &defaultFont,
			.remainClickedLeft = 1,
			.remainClickedRight = 0

		},
		sf::Vector2f(100, 500)
		);


	BoxContainerShape container(sf::Vector2f(300, 200), 0, {20, 0, 20, 0}, 5);
	container.setPosition(sf::Vector2f(600, 500));
	container.setFillColor(sf::Color(20, 255, 30));
	container.setOutlineThickness(10);
	container.setOutlineColor(sf::Color::Blue);


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

		window.draw(container);

		//window.draw(button.box);

        // update the window
        window.display();
    }

    // cleanup
 
    return 0;
}
