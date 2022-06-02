#include "Car.hpp"

CCar::CCar() {
	Rect.Left = 0;
	Rect.Right = 0;
	Rect.Top = 0;
	Rect.Bottom = 0;
	PositionWorld.x = 0;
	PositionWorld.y = 0;
	Position.x = 0;
	Position.y = 0;
	Throttle = false;
	Brakes = false;
	ThrottleForce = 0;
	Acceleration.x = 0;
	Acceleration.y = 0;
	Mass = 1500;
	Velocity.x = 0;
	Velocity.y = 0;
	Angle = 90;
	Full = false;
	Turning = 0;
}

CCar::~CCar() {
	// TODO
}

void CCar::Create(sf::Image& CarsSet, sf::Vector2f& PlayerPosition, sf::RenderWindow& Application) {
	Rect.Left = 0;
	Rect.Right = CarsSet.GetWidth();
	Rect.Top = 0;
	Rect.Bottom = CarsSet.GetHeight();

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

	PositionWorld.x = PlayerPosition.x + OffsetX;
	PositionWorld.y = PlayerPosition.y + OffsetY;

	Sprite.SetSubRect(Rect);
	Sprite.SetImage(CarsSet);
	Sprite.SetCenter(Sprite.GetSize().x / 2, Sprite.GetSize().y / 2);
}

void CCar::Update() {
	/*
	if(Throttle == true) ThrottleForce += 10;
	if(Throttle == false) ThrottleForce -= 5;
	if(ThrottleForce > 1000) ThrottleForce = 1000;
	if(ThrottleForce < 0) ThrottleForce = 0;

	if(Turning == -1) Angle -= 2;
	if(Turning == 1) Angle += 2;

	if(Angle < 0) Angle = 360;
	if(Angle > 360) Angle = 0;

	Acceleration.x = (ThrottleForce / Mass);
	Acceleration.y = (ThrottleForce / Mass);

	Acceleration.x = Acceleration.x * sin(Angle / 180 * 3.1415);
	Acceleration.y = Acceleration.y * -cos(Angle / 180 * 3.1415);

	Velocity.x += Acceleration.x;
	Velocity.y += Acceleration.y;

	PositionWorld.x += Velocity.x;
	PositionWorld.y += Velocity.y;
	*/

	if(Throttle == true) ThrottleForce += 30;
	if(Throttle == false) ThrottleForce -= 20;

	if(Brakes == true) ThrottleForce -= 10;

	if(ThrottleForce > 5000) ThrottleForce = 5000;
	if(ThrottleForce < 0) ThrottleForce = 0;

	if(Turning == -1) Angle -= 3;
	if(Turning == 1) Angle += 3;

	if(Angle < 0) Angle = 360;
	if(Angle > 360) Angle = 0;

	Acceleration.x = ThrottleForce / Mass;
	Acceleration.y = ThrottleForce / Mass;

	Velocity.x += Acceleration.x * sin(Angle / 180 * 3.14);
	Velocity.y += Acceleration.y * -cos(Angle / 180 * 3.14);

	PositionWorld += Velocity;
}

void CCar::Gas() {
	Throttle = true;
}

void CCar::ReleaseGas() {
	Throttle = false;
}

void CCar::Brake() {
	Brakes = true;
}

void CCar::ReleaseBrake() {
	Brakes = false;
}

void CCar::Turn(int Direction) {
	Turning = Direction;
}

void CCar::ReleaseWheel() {
	Turning = 0;
}

void CCar::Enter() {
	Full = true;
}

void CCar::Exit() {
	Full = false;
}

void CCar::Draw(sf::RenderWindow &Application, sf::Vector2f &PlayerPosition) {
	if(Full == true) {
		Position.x = 320;
		Position.y = 240;
	}

	if(Full == false) {
		Position.x = PositionWorld.x - PlayerPosition.x + 320;
		Position.y = PositionWorld.y - PlayerPosition.y + 240;
	}

	Sprite.SetPosition(Position);
	Sprite.SetRotation(-Angle);
	Application.Draw(Sprite);
}

sf::Vector2f *CCar::GetPosition() {
	return &PositionWorld;
}