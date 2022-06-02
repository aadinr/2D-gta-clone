#ifndef MISSION_H
#define MISSION_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <cmath>

class CMission {
	bool InMission;
	std::fstream DataFile;
	sf::Vector2f PrincipalPosition;
	sf::Image PrincipalImage;
	sf::Sprite PrincipalSprite;
	int MissionID;
	std::string TypeOfOrder;
	std::string MotionOfTarget;
	sf::Vector2f TargetPosition;
	bool DataGet;
	sf::Image TargetImage;
	sf::Sprite TargetSprite;
	std::string MissionFilename;

public:
	CMission();
	void GetData(std::string DataFilename, int _MissionID);
	void DrawPrincipal(sf::RenderWindow &Application, sf::Vector2f PlayerPosition);
	void Check(sf::RenderWindow &Application, sf::Vector2f PlayerPosition);
	std::string int2str(int i) const;
};

#endif