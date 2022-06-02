#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Window.hpp>
#include <string>
#include <fstream>

#include "Map.hpp"
#include "FPS.hpp"
#include "Player.hpp"
#include "CharactersManager.hpp"
#include "Mission.h"
#include "Logger.h"
#include "VehiclesManager.hpp"

class CApp {
	sf::RenderWindow App;
	CMap Map;
	CFPS FPS;
	CLogger Log;
	CPlayer Player;
	CCharactersManager CharactersManager;
	CMission Mission;
	CVehiclesManager VehiclesManager;

public:
	CApp();
	~CApp();
	void Set(int Width, int Height, int BPS, bool Fullscreen, std::string ApplicationTitle);
	void Set(std::string ConfigFilename, std::string ApplicationTitle);
	void Run();
	void Exit();
};

#endif