#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Config.h"
#include "Human.hpp"
#include "Weapon.hpp"
#include "Car.hpp"

class CPlayer : public CHuman {
	CWeapon* pWeapon;
	CCar* pCar;
	sf::Vector2f PlayerPositionOnScreen;
	sf::Vector2f PlayerOffset;
	float PlayerAngle;
	float PlayerVelocity;
	bool PositionSet;
	bool PlayerMoving;
	bool PlayerShooting;
	bool PlayerDriving;
	bool PlayerWannaDrive;
	bool Collision;

public:
	CPlayer();
	~CPlayer();
	void LoadSprite(std::string SpriteFilename);
	void HandleInput(sf::RenderWindow &Application);
	void Move(sf::RenderWindow &Application);
	void Draw(sf::RenderWindow &Application);
	void Shoot();
	void CheckCollision(int TileID, sf::RenderWindow &Application);
	void SetPosition(sf::Vector2f PlayerPosition);
	void SetPosition(float PositionX, float PositionY);
	sf::Vector2f GetPosition();
	void CalculateAngle(sf::Vector2i MousePosition, sf::RenderWindow &Application);
	float GetAngle();
	bool PlayerWannaDrive();
	bool PlayerDriving();
	void SetDrivingState(bool State);
	CWeapon* GetWeaponPointer();
	void SetPlayerCar(CCar** pCar);
	void ResetData();
	std::string int2str(int i) const {
		std::stringstream ss;
		std::string temp;
		ss << i;
		ss >> temp;
		return temp;
	}
};

#endif