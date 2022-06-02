#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Config.h"

class CBullet {
	sf::Image* BulletImage;
	sf::Sprite BulletSprite;
	bool Alive;
	sf::Vector2f BulletPosition;
	sf::Vector2f BulletOffset;
	float BulletAngle;
	float BulletVelocity;

public:
	CBullet();
	~CBullet();
	void Create(sf::Vector2f* PlayerPosition, float* PlayerAngle, sf::Image* BulletImage, float* BulletVelocity);
	bool Update(sf::Vector2f* PlayerPosition, sf::RenderWindow& Application);
	void Draw(sf::RenderWindow& Application);
	sf::Vector2f* GetBulletPosition();
	void ResetData();
};

#endif