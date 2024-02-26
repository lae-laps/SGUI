#ifndef BOX_CONTAINER_SHAPE_HPP
#define BOX_CONTAINER_SHAPE_HPP

#include <cmath>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

#include <iostream>

// This class allows for dynamic, easy to use, rectangle-like shapes
//
// NOTES:
// cornerCut refers to the cut in each corner as in
//  ______
// /      |
// |      |
// |______/
//
// quarterCircleSections is the sections for each of the quarters of the cirlce, preset to 8
//
// note the class will ignore the cornerCut if the radius is not 0

#define PI 3.141592654

class BoxContainerShape : public sf::Shape {
public :

    BoxContainerShape() = default;
    //explicit BoxContainerShape();
    
    void set(const sf::Vector2f boxSize_, const unsigned int cornerRadius_, const std::array<unsigned int, 4> cornerCut_ = {0, 0, 0, 0}, const unsigned int quarterCircleSections_ = 8) {

		boxSize = boxSize_;
    	cornerRadius = cornerRadius_;
    	cornerCut = cornerCut_;
    	quarterCircleSections = quarterCircleSections_;

    	updateShape();

    }

    void updateShape() {

    	// clear point vector from beforehand if already set
    	points.clear();

		if (cornerRadius == 0) {
			int ignoreCornerCuts = 1;
			for (size_t i = 0; i < 4; i++) {
				if (cornerCut[i] != 0) {
					ignoreCornerCuts = 0;
				}
			}
			if (ignoreCornerCuts) {
				points = {
					sf::Vector2f(0, 0),
					sf::Vector2f(boxSize.x, 0),
					sf::Vector2f(boxSize.x, boxSize.y),
					sf::Vector2f(0, boxSize.y)
				};
			} else {
				points = {
					sf::Vector2f(cornerCut[0], 0),
					sf::Vector2f(boxSize.x - cornerCut[1], 0),
					sf::Vector2f(boxSize.x, cornerCut[1]),
					sf::Vector2f(boxSize.x, boxSize.y - cornerCut[2]),
					sf::Vector2f(boxSize.x - cornerCut[2], boxSize.y),
					sf::Vector2f(cornerCut[3], boxSize.y),
					sf::Vector2f(0, boxSize.y - cornerCut[3]),
					sf::Vector2f(0, cornerCut[0])
				};
			}
		} else {
			for (int cornerNumber = 0; cornerNumber < 4; cornerNumber++) {

				sf::Vector2f currentOffset;																				// add the offset as if not, it would be a circle
				// couldn't find a more elegant way than a switch case
			
				switch (cornerNumber) {
					case 0: // Top-left corner
						currentOffset = sf::Vector2f(0, 0);
						break;
					case 1: // Top-right corner
						currentOffset = sf::Vector2f(boxSize.x - cornerRadius, 0);
						break;
					case 2: // Bottom-right corner
						currentOffset = sf::Vector2f(boxSize.x - cornerRadius, boxSize.y - cornerRadius);
						break;
					case 3: // Bottom-left corner
						currentOffset = sf::Vector2f(0, boxSize.y - cornerRadius);
						break;
				}

				for (size_t segment = 0; segment <= quarterCircleSections; segment ++) {
					double angle = (segment * M_PI) / (quarterCircleSections * 2) + (M_PI/2) * (cornerNumber - 2);					// compute angle, there is also an angle "takeover"
					points.push_back(sf::Vector2f(cornerRadius * std::cos(angle), cornerRadius * std::sin(angle)) + currentOffset);	// compute points considering offset
				}
				// dont know if i have to manually add some points here
			}
		}

        update();				// update internal geometry of base class
    }

    void setSize(const sf::Vector2f newSize) {
		boxSize = newSize;
		updateShape();
    }

    // return wether a position is inside the element
    int isInsideElement(float x, float y) {
		return getGlobalBounds().contains(sf::Vector2f(x, y));																		// most elegant way
    }
	
    // change this to size_t to prevent type errors
    virtual std::size_t getPointCount() const override {
    	return points.size();
    }

    virtual sf::Vector2f getPoint(std::size_t index) const override {
    	return points[index];
    }

private :
	
	std::vector<sf::Vector2f> points;

	sf::Vector2f boxSize;
	unsigned int cornerRadius;
	unsigned int quarterCircleSections;
	std::array<unsigned int, 4> cornerCut;
	
};

#endif

