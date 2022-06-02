#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "Config.h"
#include "Bullet.hpp"

class CWeapon {
	sf::Image BulletImage;
	sf::Clock Time;
	float LastShootTime;
	float BulletsInterval;
	float BulletsVelocity;
	int BulletsNumber;
	std::vector<CBullet*> Ammunition;
	std::vector<CBullet*>::iterator AmmunitionIterator;
	
public:
	CWeapon();
	~CWeapon();
	void LoadBulletData(std::string WeaponsDataFilename);
	void Shoot(sf::Vector2f* PlayerPosition, float* PlayerAngle);
	void DrawBullets(sf::RenderWindow& Application);
	void UpdateBullets(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition);
	bool CheckBulletsCollision(sf::Vector2f* ObjectPosition);
	int GetBulletsNumber() const;
	void DestroyBullet();
	void DestroyBullets();
	void ResetData();
};

#endif