#include "Application.hpp"

CApp::CApp() {
	// TODO
}

CApp::~CApp() {
	// TODO
}

void CApp::Set(int Width, int Height, int BPS, bool Fullscreen, std::string ApplicationTitle) {
	if(Fullscreen == false) App.Create(sf::VideoMode(Width, Height, BPS), ApplicationTitle, sf::Style::Close);
	if(Fullscreen == true) App.Create(sf::VideoMode(Width, Height, BPS), ApplicationTitle, sf::Style::Close | sf::Style::Fullscreen);

	Log.OpenLog("log.txt", true);

	if(Map.LoadTileset("mapka.bmp", App.GetWidth(), App.GetHeight()) == false) Log.Log("Map tileset image was not loaded!");
	else Log.Log("Map tileset was loaded.");

	Player.LoadSprite("player.bmp");
	CharactersManager.LoadSets("player.bmp");
	VehiclesManager.LoadSet("car.bmp");
}

void CApp::Set(std::string ConfigFilename, std::string ApplicationTitle) {
	std::ifstream Config;
	int Width, Height, BPS;
	bool Fullscreen;

	Config.open(ConfigFilename, std::ios::in);
	Config >> Width >> Height >> BPS >> Fullscreen;

	Config.close();

	if(Fullscreen == false) App.Create(sf::VideoMode(Width, Height, BPS), ApplicationTitle, sf::Style::Close);
	if(Fullscreen == true) App.Create(sf::VideoMode(Width, Height, BPS), ApplicationTitle, sf::Style::Close | sf::Style::Fullscreen);

	Log.OpenLog("log.txt", true);

	if(Map.LoadTileset("mapka.bmp", App.GetWidth(), App.GetHeight()) == false) Log.Log("Map tileset image was not loaded!");
	else Log.Log("Map tileset was loaded.");

	Player.LoadSprite("player.bmp");
	CharactersManager.LoadSets("player.bmp");
	VehiclesManager.LoadSet("car.bmp");
}

void CApp::Run() {
	sf::Event Event;
	App.SetFramerateLimit(60);

	while(App.IsOpened())
	{
		while(App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed) App.Close();
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Escape) App.Close();
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::Q) Player.SetPosition(1000, 1000);
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::X) VehiclesManager.CreateCar(App, Player.GetPosition());
			if(Event.Type == sf::Event::KeyPressed && Event.Key.Code == sf::Key::C) CharactersManager.CreatePedestrian(App, &Player.GetPosition());
			Player.HandleInput(App);
		}

		Player.Shoot();

		CharactersManager.CheckPedestriansCollision(Player.GetWeaponPointer());
		VehiclesManager.CheckDrivingPossible(&Player);
		//Player.CheckCollision(Map.GetCollisionTile(Player.GetPosition()), App);
		//Player.HandleInput(App);
		Player.Move(App);
		Mission.Check(App, Player.GetPosition());
		VehiclesManager.UpdateVehicles();
		//VehiclesManager.MoveVehicles();

		App.Clear();

		Map.Draw(App, Player.GetPosition());
		Player.Draw(App);
		CharactersManager.DrawCharacters(App, &Player.GetPosition());
		VehiclesManager.DrawVehicles(App, Player.GetPosition());
		FPS.Draw(App);
		Mission.DrawPrincipal(App, Player.GetPosition());

		App.Display();
	}
}

void CApp::Exit() {
	//Deleting resources
	// TODO
}
