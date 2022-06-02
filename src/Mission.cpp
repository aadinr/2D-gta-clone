#include "Mission.h"

CMission::CMission() {
	InMission = false;
	MissionID = 0;
	DataGet = false;
}

void CMission::GetData(std::string DataFilename, int _MissionID) {
		DataFile.open(DataFilename.c_str(), std::ios::out | std::ios::in);

		while(1) {
			std::string Buffer;
			std::string Buffer2;

			DataFile >> Buffer;

			Buffer2 = '#' + int2str(_MissionID);
		
			if(Buffer == Buffer2)
			{
				DataFile.ignore();
				break;
			}
			if(Buffer != Buffer2) DataFile.ignore();

			if(DataFile.eof()) break;
		}

		std::string PrincipalImageFilename;
		std::string TargetImageFilename;
		
		DataFile >> PrincipalImageFilename >> PrincipalPosition.x >> PrincipalPosition.y;
		DataFile >> TargetImageFilename >> TypeOfOrder >> MotionOfTarget >> TargetPosition.x >> TargetPosition.y;

		PrincipalImage.LoadFromFile(PrincipalImageFilename);
		PrincipalImage.SetSmooth(false);
		PrincipalImage.CreateMaskFromColor(sf::Color(255, 0, 255));
		sf::IntRect SubRect;
		SubRect.Right = PrincipalImage.GetWidth();
		SubRect.Bottom = PrincipalImage.GetHeight();
		PrincipalSprite.SetSubRect(SubRect);
		PrincipalSprite.SetImage(PrincipalImage);

		TargetImage.LoadFromFile(TargetImageFilename);
		TargetImage.SetSmooth(false);
		TargetImage.CreateMaskFromColor(sf::Color(255, 0, 255));
		SubRect.Right = TargetImage.GetWidth();
		SubRect.Bottom = TargetImage.GetHeight();
		TargetSprite.SetSubRect(SubRect);
		TargetSprite.SetImage(TargetImage);

		DataFile.close();
}

void CMission::DrawPrincipal(sf::RenderWindow &Application, sf::Vector2f PlayerPosition) {
	if(InMission == false) {
		PrincipalSprite.SetPosition(PrincipalPosition.x - PlayerPosition.x + (Application.GetWidth()
		- PrincipalSprite.GetSize().x) / 2, PrincipalPosition.y - PlayerPosition.y + (Application.GetHeight() - PrincipalSprite.GetSize().y) / 2);
		Application.Draw(PrincipalSprite);
	}
	if(InMission == true) {
		TargetSprite.SetPosition(TargetPosition.x - PlayerPosition.x + (Application.GetWidth() - TargetSprite.GetSize().x) / 2,
		TargetPosition.y - PlayerPosition.y + (Application.GetHeight() - TargetSprite.GetSize().y) / 2);
		Application.Draw(TargetSprite);
	}
}

void CMission::Check(sf::RenderWindow &Application, sf::Vector2f PlayerPosition) {
	int Distance = sqrt(pow(PlayerPosition.x - PrincipalPosition.x, 2) + pow(PlayerPosition.y - PrincipalPosition.y, 2));

	if(Application.GetInput().IsKeyDown(sf::Key::Return) && Distance < 70 && InMission == false) {
		InMission = true;
	}

	if(TypeOfOrder == "eliminate" && InMission == true) {
		int TargetDistance = sqrt(pow(PlayerPosition.x - TargetPosition.x, 2) + pow(PlayerPosition.y - TargetPosition.y, 2));
		if(TargetDistance < 50) {
			InMission = false;
			DataGet = false;
			MissionID++;
		}
	}

	if(InMission == false && DataGet == false) {
		GetData("missions.txt", MissionID);
		DataGet = true;
	}
}


std::string CMission::int2str(int i) const {
	std::stringstream ss;
	std::string temp;
    ss << i;
    ss >> temp;
    return temp;
}
