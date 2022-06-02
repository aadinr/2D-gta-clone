#include "VehiclesManager.hpp"

CVehiclesManager::CVehiclesManager() {
	ResetData();
}

CVehiclesManager::~CVehiclesManager() {
	// TODO
}

void CVehiclesManager::LoadSet(std::string CarsSetFilename) {
	CarsSet.LoadFromFile(CarsSetFilename);
	CarsSet.CreateMaskFromColor(sf::Color(255, 0, 255));
}

void CVehiclesManager::CreateCar(sf::RenderWindow& Application, sf::Vector2f& PlayerPosition) {
	CCar* pCar = new CCar;
	pCar->Create(CarsSet, PlayerPosition, Application);
	Cars.push_back(pCar);
	CarsNumber = Cars.size();
}

void CVehiclesManager::DestroyCar() {
	delete (*CarsIterator);
	CarsIterator = Cars.erase(CarsIterator);
}

void CVehiclesManager::UpdateVehicles() {
	for(CarsIterator = Cars.begin(); CarsIterator != Cars.end(); ++CarsIterator)
	{
		(*CarsIterator)->Update();
	}
}

void CVehiclesManager::MoveVehicles() {
	for(CarsIterator = Cars.begin(); CarsIterator != Cars.end(); ++ CarsIterator) {
		//(*CarsIterator)->Move();
	}
}

void CVehiclesManager::DrawVehicles(sf::RenderWindow& Application, sf::Vector2f& PlayerPosition) {
	for(CarsIterator = Cars.begin(); CarsIterator != Cars.end(); ++CarsIterator) {
		(*CarsIterator)->Draw(Application, PlayerPosition);
	}
}

void CVehiclesManager::CheckDrivingPossible(CPlayer* pPlayer) {
	bool PlayerWannaDrive = pPlayer->PlayerWannaDrive();
	bool PlayerDriving = pPlayer->PlayerDriving();

	if(PlayerWannaDrive == false) return;
	if(PlayerDriving == true) return;

	int Distance = 0;

	sf::Vector2f PlayerPosition(pPlayer->GetPosition());
	sf::Vector2f CarPosition;

	for(CarsIterator = Cars.begin(); CarsIterator != Cars.end(); ++CarsIterator) {
		CarPosition = *(*CarsIterator)->GetPosition();
		Distance = static_cast<int>(sqrt(pow(PlayerPosition.x - CarPosition.x, 2) + pow(PlayerPosition.y - CarPosition.y, 2)));

		if(Distance < 75) {
			pPlayer->SetDrivingState(true);
			pPlayer->SetPlayerCar(&(*CarsIterator));
			pPlayer->SetPosition(*(*CarsIterator)->GetPosition());
			(*CarsIterator)->Enter();
			break;
		}
	}
}

void CVehiclesManager::ResetData() {
	CarsNumber = 0;
	CarsIterator = Cars.begin();
}
