#include "Bullet.hpp"

CBullet::CBullet() {
	ResetData();
}

CBullet::~CBullet() {
	// TODO
}

void CBullet::Create(sf::Vector2f* PlayerPosition, float* PlayerAngle, sf::Image* BulletImage, float* BulletVelocity) {
	this->BulletImage = BulletImage;
	BulletSprite.SetImage(*this->BulletImage);
	BulletSprite.SetCenter(static_cast<float>(BulletImage->GetWidth() / 2), static_cast<float>(BulletImage->GetHeight() / 2));
	Alive = true;
	BulletPosition = *PlayerPosition;
	BulletAngle = *PlayerAngle;
	BulletSprite.SetRotation(-BulletAngle);
	this->BulletVelocity = *BulletVelocity;
	BulletOffset.x = static_cast<float>(sin(BulletAngle / 180 * 3.14) * this->BulletVelocity);
	BulletOffset.y = static_cast<float>(-cos(BulletAngle / 180 * 3.14) * this->BulletVelocity);
}

bool CBullet::Update(sf::Vector2f* PlayerPosition, sf::RenderWindow& Application) {
	int Distance = static_cast<int>(sqrt(pow(PlayerPosition->x - BulletPosition.x, 2) + pow(PlayerPosition->y - BulletPosition.y, 2)));
	
	if(Distance > 500) {
		return false;
	}

	else {
		BulletPosition.x += BulletOffset.x;
		BulletPosition.y += BulletOffset.y;

		sf::Vector2f BulletSpriteSize = BulletSprite.GetSize();

		sf::Vector2f BulletWindowPosition;
		BulletWindowPosition.x = BulletPosition.x - PlayerPosition->x + (Application.GetWidth() - BulletSpriteSize.x) / 2 + BulletSpriteSize.x / 2;
		BulletWindowPosition.y = BulletPosition.y - PlayerPosition->y + (Application.GetHeight() - BulletSpriteSize.y) / 2 + BulletSpriteSize.y / 2;

		BulletSprite.SetPosition(BulletWindowPosition);

		return true;
	}
}

void CBullet::Draw(sf::RenderWindow& Application) {
	if(Alive == true) Application.Draw(BulletSprite);
}

sf::Vector2f* CBullet::GetBulletPosition() {
	return &BulletPosition;
}

void CBullet::ResetData() {
	BulletImage = NULL;
	Alive = false;
	BulletPosition.x = 0;
	BulletPosition.y = 0;
	BulletOffset.x = 0;
	BulletOffset.y = 0;
	BulletAngle = 0;
	BulletVelocity = 0;
}