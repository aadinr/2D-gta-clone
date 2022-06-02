#ifndef CHARACTERSMANAGER_HPP
#define CHARACTERSMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "Pedestrian.hpp"
#include "Weapon.hpp"

class CCharactersManager {
	sf::Image PedestriansSet;
	int PedestriansNumber;
	std::vector<CPedestrian*> Pedestrians;
	std::vector<CPedestrian*>::iterator PedestriansIterator;

public:
	CCharactersManager();
	~CCharactersManager();
	void LoadSets(std::string PedestriansSetFilename);
	void CreatePedestrian(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition);
	void DestroyPedestrian();
	void DrawCharacters(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition);
	void CheckPedestriansCollision(CWeapon* pWeapon);
	void ResetData();
};

#endif