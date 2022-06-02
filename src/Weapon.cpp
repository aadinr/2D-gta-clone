#include "Weapon.hpp"

CWeapon::CWeapon() { ResetData(); }
CWeapon::~CWeapon() { DestroyBullets(); }

void CWeapon::LoadBulletData(std::string WeaponsDataFilename) {
	std::fstream File;
	File.open(WeaponsDataFilename, std::ios::in);

	std::string BulletImageFilename;

	File >> BulletImageFilename >> BulletsVelocity >> BulletsInterval;

	File.close();

	BulletImage.LoadFromFile(BulletImageFilename);
	BulletImage.CreateMaskFromColor(sf::Color(255, 0, 255));
}

void CWeapon::Shoot(sf::Vector2f* PlayerPosition, float* PlayerAngle) {
	if(Time.GetElapsedTime() - LastShootTime > BulletsInterval) {
		CBullet* pBullet = new CBullet;
		pBullet->Create(PlayerPosition, PlayerAngle, &BulletImage, &BulletsVelocity);
		Ammunition.push_back(pBullet);
		Time.Reset();
		LastShootTime = Time.GetElapsedTime();
		BulletsNumber = Ammunition.size();
	}
}

void CWeapon::DrawBullets(sf::RenderWindow& Application) {
	for(AmmunitionIterator = Ammunition.begin(); AmmunitionIterator != Ammunition.end(); ++AmmunitionIterator) {
		(*AmmunitionIterator)->Draw(Application);
	}
}

void CWeapon::UpdateBullets(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition) {
	for(AmmunitionIterator = Ammunition.begin(); AmmunitionIterator != Ammunition.end(); ) {
		if((*AmmunitionIterator)->Update(PlayerPosition, Application) == false) {
			DestroyBullet();
		}
		else ++AmmunitionIterator;

		BulletsNumber = Ammunition.size();
	}
}

bool CWeapon::CheckBulletsCollision(sf::Vector2f* ObjectPosition) {
	int Distance = 0;
	int Range = 0;

	for(AmmunitionIterator = Ammunition.begin(); AmmunitionIterator != Ammunition.end(); ) {
		sf::Vector2f BulletPosition;
		BulletPosition = *(*AmmunitionIterator)->GetBulletPosition();
		Distance = static_cast<int>(sqrt(pow(ObjectPosition->x - BulletPosition.x, 2) + pow(ObjectPosition->y - BulletPosition.y, 2)));
		Range = (BulletImage.GetWidth() + BulletImage.GetHeight()) / 3;

		if(Distance < Range) {
			DestroyBullet();
			return true;
		}
		else ++AmmunitionIterator;

		BulletsNumber = Ammunition.size();
	}

	return false;
}

int CWeapon::GetBulletsNumber() const { return BulletsNumber; }

void CWeapon::DestroyBullet() {
	delete (*AmmunitionIterator);
	AmmunitionIterator = Ammunition.erase(AmmunitionIterator);
}

void CWeapon::DestroyBullets() {
	for(AmmunitionIterator = Ammunition.begin(); AmmunitionIterator != Ammunition.end(); ) {
		delete (*AmmunitionIterator);
		AmmunitionIterator = Ammunition.erase(AmmunitionIterator);
	}
}

void CWeapon::ResetData() {
	Time.Reset();
	LastShootTime = Time.GetElapsedTime();
	BulletsInterval = 0;
	BulletsVelocity = 0;
	BulletsNumber = 0;
	AmmunitionIterator = Ammunition.begin();
}
