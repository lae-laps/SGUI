#include <iostream>
#include <SFML/Graphics.hpp>

#include "Slider.hpp"
#include "TextInput.hpp"
#include "TextButton.hpp"

#define WIDTH 1600
#define HEIGHT 1000

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
    TextButton button1("Este es un texto\nVamos a hacerlo multilinea\nporque no?", 
		TextButtonProperties {
			.innerColor = {sf::Color(80, 120, 200), sf::Color(100, 180, 255), sf::Color(100, 180, 255), sf::Color(100, 180, 255)},
			.rimColor = {sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black},
			.rimThickness = {0, 0, 0, 0},
			.shadowThickness = {10, 10, 10, 10},
			.fontSize = {20, 20, 20, 20},
			.font = &defaultFont,
			.cornerCuts = {20, 0, 20, 0},
			.cornerRadius = 10,
			.remainClickedLeft = 0,
			.remainClickedRight = 0
		},
		sf::Vector2f(100, 100)
		);

    TextButton button2("A button with a large text", 
		TextButtonProperties {
			.innerColor = {sf::Color(0, 0, 0, 0), sf::Color::Blue, sf::Color::Blue, sf::Color::Blue},
			.rimColor = {sf::Color(20, 20, 100, 255), sf::Color(50, 50, 200), sf::Color(20, 20, 100), sf::Color(20, 20, 100)},
			.rimThickness = {0, 0, 0, 0},
			.shadowThickness = {0, 0, 0, 0},
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
			.remainClickedRight = 1

		},
		sf::Vector2f(100, 500)
		);

    TextButton button4("Some button", 
		TextButtonProperties {
			.innerColor = {sf::Color(178, 133, 0), sf::Color(255, 191, 0), sf::Color(255, 191, 0), sf::Color(255, 191, 0)},
			.rimColor = {sf::Color(178, 133, 0), sf::Color(178, 133, 0), sf::Color(178, 133, 0), sf::Color(178, 133, 0)},
			.rimThickness = {5, 5, 5, 5},
			.shadowThickness = {0, 15, 0, 0},
			.fontSize = {20, 20, 20, 20},
			.font = &defaultFont,
			.cornerCuts = {6, 0, 6, 0},
			.cornerRadius = 0,
			.remainClickedLeft = 0,
			.remainClickedRight = 0
		},
		sf::Vector2f(700, 100)
		);

    TextButton button5("A", 
		TextButtonProperties {
			.innerColor = {sf::Color(220, 20, 60), sf::Color(180, 10, 40), sf::Color(220, 20, 60), sf::Color(220, 20, 60)},
			.rimColor = {sf::Color(178, 133, 0), sf::Color(178, 133, 0), sf::Color(178, 133, 0), sf::Color(178, 133, 0)},
			.rimThickness = {0, 0, 0, 0},
			.shadowThickness = {0, 4, 0, 0},
			.fontSize = {20, 20, 20, 20},
			.font = &defaultFont,
			.cornerCuts = {6, 0, 6, 0},
			.cornerRadius = 25,
			.remainClickedLeft = 0,
			.remainClickedRight = 0
		},
		sf::Vector2f(600, 100),
		sf::Vector2f(25, 25)
		);

	TextButton button6("Test Button", 
		TextButtonProperties {
			.innerColor = {sf::Color::Blue, sf::Color::Blue, sf::Color::Red, sf::Color::Green},
			.rimColor = {sf::Color::Black, sf::Color::Black, sf::Color::Black, sf::Color::Black},
			.rimThickness = {0, 0, 0, 0},
			.shadowThickness = {0, 0, 0, 0},
			.fontSize = {20, 20, 20, 20},			// Change the font size as needed
			.font = &defaultFont,
			.remainClickedLeft = 0,
			.remainClickedRight = 0

		},
		sf::Vector2f(400, 500)
		);

	Slider slider1(
		SliderProperties {
			.min = 10.0,
			.max = 40.0,
			.initialValue = 20.0,
			.showSelector = true,
			.baseDimensions = sf::Vector2f(200, 5),
			.selectorDimensions = sf::Vector2f(10, 10),

			.baseRimThickness = {0, 0, 0, 0, 0, 0},
			.selectorRimThickness = {2, 2, 2, 2, 2, 2},
			.baseFillColorLeft = {sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0)},
			.baseFillColorRight = {sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150)},
			.selectorFillColor = {sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100)},
			.selectorRimColor = {sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0)},

			.baseCornerRadius = 5,
			.selectorCornerRadius = 10,
		}, 
		sf::Vector2f(600, 600)
		);

	Slider slider2(
		SliderProperties {
			.min = 20.0,
			.max = 40.0,
			.initialValue = 30.0,
			.showSelector = true,
			.baseDimensions = sf::Vector2f(300, 10),
			.selectorDimensions = sf::Vector2f(5, 10),
			.baseRimThickness = {2, 2, 2, 2, 2, 2},
			.selectorRimThickness = {2, 2, 2, 2, 2, 2},
			.baseFillColorLeft = {sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0)},
			.baseFillColorRight = {sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(150, 150, 150)},
			.selectorFillColor = {sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100), sf::Color(100, 100, 100)},
			.selectorRimColor = {sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0), sf::Color(255, 128, 0)},
			.baseCornerRadius = 5,
			.selectorCornerRadius = 0,
		}, 
		sf::Vector2f(600, 700)
		);

	TextInput input1(
		TextInputProperties {
			.defaultText = "default",
			.cursorWidth = 2,
			.cornerRadius = 5,
			.dimensions = sf::Vector2f(200, 25),
			.rimThickness = {2, 2, 2, 2},
			.cursorColor = sf::Color(0, 0, 0),
			.fillColor = {sf::Color(100, 100, 200), sf::Color(150, 150, 250), sf::Color(150, 150, 250), sf::Color(150, 150, 250)},
			.rimColor = {sf::Color(50, 50, 50), sf::Color(50, 50, 50), sf::Color(250, 150, 150), sf::Color(150, 150, 150)},
			.textColor = {sf::Color(50, 50, 50), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(150, 150, 150)},
			.fontSize = 16,
			.font = &defaultFont,
			.allowEmptyInput = false,
			.maxInputSize = 19

		},
		sf::Vector2f(1000, 400)
		);


	TextInput input2(
		TextInputProperties {
			.defaultText = "input 2",
			.cursorWidth = 2,
			.cornerRadius = 5,
			.dimensions = sf::Vector2f(400, 25),
			.rimThickness = {2, 2, 2, 2},
			.cursorColor = sf::Color(0, 0, 0),
			.fillColor = {sf::Color(200, 100, 100), sf::Color(100, 200, 100), sf::Color(100, 100, 200), sf::Color(100, 200, 200)},
			.rimColor = {sf::Color(50, 50, 50), sf::Color(50, 50, 50), sf::Color(50, 50, 50), sf::Color(50, 50, 50)},
			.textColor = {sf::Color(100, 100, 100), sf::Color(0, 0, 0), sf::Color(0, 0, 0), sf::Color(150, 150, 150)},
			.fontSize = 16,
			.font = &defaultFont,
			.allowEmptyInput = true,
			.maxInputSize = 0

		},
		sf::Vector2f(1000, 600)
		);

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
            button4.manageEvent(&event);
            button5.manageEvent(&event);
            button6.manageEvent(&event);

			slider1.manageEvent(&event);
			slider2.manageEvent(&event);

			input1.manageEvent(&event);
			input2.manageEvent(&event);
            
			switch (event.type) {
				case sf::Event::KeyPressed:				// key (pressed)
					// handle keypress
					switch (event.key.code) {
						case sf::Keyboard::Escape:		// close on Esc
							//window.close();
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
        window.clear(sf::Color(200, 200, 200));

		// draw buffer

		button1.draw(window);
		button2.draw(window);
		button3.draw(window);
		button4.draw(window);
		button5.draw(window);
		button6.draw(window);

		slider1.draw(window);
		slider2.draw(window);

		input1.draw(window);
		input2.draw(window);

		//window.draw(button.box);

        // update the window
        window.display();
    }

    // cleanup
 
    return 0;
}
