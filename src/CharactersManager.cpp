#include "CharactersManager.hpp"

CCharactersManager::CCharactersManager() {
	ResetData();
}

CCharactersManager::~CCharactersManager() {
	ResetData();
}

void CCharactersManager::LoadSets(std::string PedestriansSetFilename) {
	PedestriansSet.LoadFromFile(PedestriansSetFilename);
	PedestriansSet.CreateMaskFromColor(sf::Color(255, 0, 255));
}

void CCharactersManager::CreatePedestrian(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition) {
	CPedestrian* pPedestrian = new CPedestrian;
	pPedestrian->Create(&PedestriansSet, PlayerPosition, Application);
	Pedestrians.push_back(pPedestrian);
	PedestriansNumber = Pedestrians.size();
}

void CCharactersManager::DestroyPedestrian() {
	delete (*PedestriansIterator);
	PedestriansIterator = Pedestrians.erase(PedestriansIterator);
}

void CCharactersManager::DrawCharacters(sf::RenderWindow& Application, sf::Vector2f* PlayerPosition) {
	for(PedestriansIterator = Pedestrians.begin(); PedestriansIterator != Pedestrians.end(); ++PedestriansIterator)
	{
		(*PedestriansIterator)->Draw(Application, PlayerPosition);
	}
}

void CCharactersManager::CheckPedestriansCollision(CWeapon* pWeapon) {
	for(PedestriansIterator = Pedestrians.begin(); PedestriansIterator != Pedestrians.end(); )
	{
		if(pWeapon->CheckBulletsCollision(&(*PedestriansIterator)->GetPedestrianPosition()) == true)
		{
			delete (*PedestriansIterator);
			PedestriansIterator = Pedestrians.erase(PedestriansIterator);
		}
		else ++PedestriansIterator;
	}
}

void CCharactersManager::ResetData() {
	PedestriansNumber = 0;
	PedestriansIterator = Pedestrians.begin();
}