#ifndef PEDESTRIAN_HPP
#define PEDESTRIAN_HPP

#include <SFML/Graphics.hpp>
#include "Human.hpp"
#include "Config.h"

class CPedestrian : public CHuman {
	sf::IntRect PedestrianRect;
	sf::Vector2f PedestrianPositionOnScreen;
	float PedestrianAngle;
	float PedestrianHealth;
	bool PedestrianAlive;

public:
	CPedestrian();
	~CPedestrian();
	void Create(sf::Image* PedestriansSet, sf::Vector2f* PlayerPosition, sf::RenderWindow& Application);
	void Draw(sf::RenderWindow &Application, sf::Vector2f* PlayerPosition);
	sf::Vector2f GetPedestrianPosition();
	void ResetData();
};

#endif