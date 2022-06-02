#include "Pedestrian.hpp"

CPedestrian::CPedestrian() {
	ResetData();
}

CPedestrian::~CPedestrian() {
	// TODO
}

void CPedestrian::Create(sf::Image* PedestrianSet, sf::Vector2f* PlayerPosition, sf::RenderWindow& Application) {
	PedestrianRect.Left = 0;
	PedestrianRect.Right = 32;
	PedestrianRect.Top = 0;
	PedestrianRect.Bottom = 32;

	int MouseX = Application.GetInput().GetMouseX();
	int MouseY = Application.GetInput().GetMouseY();

	int OffsetX = 0;
	int OffsetY = 0;

	int HalfWindowX = Application.GetWidth() / 2;
	int HalfWindowY = Application.GetHeight() / 2;
	
	if(MouseX < HalfWindowX) OffsetX = (HalfWindowX - MouseX) * -1;
	if(MouseX > HalfWindowX) OffsetX = (MouseX - HalfWindowX);
	if(MouseX == Application.GetWidth() / 2) OffsetX = 0;

	if(MouseY < HalfWindowY) OffsetY = (HalfWindowY - MouseY) * -1;
	if(MouseY > HalfWindowY) OffsetY = (MouseY - HalfWindowY);
	if(MouseY == Application.GetHeight() / 2) OffsetY = 0;

	Position.x = PlayerPosition->x + OffsetX;
	Position.y = PlayerPosition->y + OffsetY;

	PedestrianAngle = 0;

	PedestrianHealth = 0;
	PedestrianAlive = true;

	Sprite.SetSubRect(PedestrianRect);
	Sprite.SetImage(*PedestrianSet);
}

void CPedestrian::Draw(sf::RenderWindow &Application, sf::Vector2f* PlayerPosition) {
	int Distance = static_cast<int>(sqrt(pow(PlayerPosition->x - Position.x, 2) + pow(PlayerPosition->y - Position.y, 2)));

	PedestrianPositionOnScreen.x = Position.x - PlayerPosition->x + (Application.GetWidth() - Sprite.GetSize().x) / 2;
	PedestrianPositionOnScreen.y = Position.y - PlayerPosition->y + (Application.GetHeight() - Sprite.GetSize().y) / 2;

	Sprite.SetPosition(PedestrianPositionOnScreen);

	if(PedestrianAlive == true && Distance < 500) Application.Draw(Sprite);
}

sf::Vector2f CPedestrian::GetPedestrianPosition() { return Position; }

void CPedestrian::ResetData() {
	PedestrianRect.Left = 0;
	PedestrianRect.Right = 0;
	PedestrianRect.Top = 0;
	PedestrianRect.Bottom = 0;
	Position.x = 0;
	Position.y = 0;
	PedestrianPositionOnScreen.x = 0;
	PedestrianPositionOnScreen.y = 0;
	PedestrianAngle = 0;
	PedestrianHealth = 0;
	PedestrianAlive = false;
}
