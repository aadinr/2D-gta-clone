#ifndef VEHICLES_MANAGER_HPP
#define VEHICLES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include "Car.hpp"
#include "Player.hpp"

class CVehiclesManager {
	sf::Image CarsSet;
	int CarsNumber;
	std::vector<CCar*> Cars;
	std::vector<CCar*>::iterator CarsIterator;

public:
	CVehiclesManager();
	~CVehiclesManager();
	void LoadSet(std::string CarsSetFilename);
	void CreateCar(sf::RenderWindow& Application, sf::Vector2f& PlayerPosition);
	void DestroyCar();
	void UpdateVehicles();
	void MoveVehicles();
	void DrawVehicles(sf::RenderWindow& Application, sf::Vector2f& PlayerPosition);
	void CheckDrivingPossible(CPlayer* pPlayer);
	void ResetData();
};

#endif
