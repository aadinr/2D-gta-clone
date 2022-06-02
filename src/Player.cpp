#include "Player.hpp"

CPlayer::CPlayer() {
	pWeapon = new CWeapon;
	pCar = new CCar;
	ResetData();
}

CPlayer::~CPlayer() {
	delete pWeapon;
	delete pCar;
	ResetData();
}

void CPlayer::LoadSprite(std::string SpriteFilename) {
	if(!Image.LoadFromFile(SpriteFilename)) {
		// TODO
	}
	else {
		Image.CreateMaskFromColor(sf::Color(255, 0, 255));
		Sprite.SetImage(Image);
		Sprite.SetCenter(static_cast<float>(Image.GetWidth() / 2), static_cast<float>(Image.GetHeight() / 2));
	}

	pWeapon->LoadBulletData("weapons.txt");
}

void CPlayer::HandleInput(sf::RenderWindow &Application) {
	if(Application.GetInput().IsKeyDown(sf::Key::W)) {
		if(PlayerDriving == true) pCar->Gas();
		if(PlayerDriving == false) PlayerMoving = true;
	}
	
	else {
		if(PlayerDriving == true) pCar->ReleaseGas();
		if(PlayerDriving == false) PlayerMoving = false;
	}

	if(Application.GetInput().IsKeyDown(sf::Key::S)) { if(PlayerDriving == true) pCar->Brake(); }
	else { if(PlayerDriving == true) pCar->ReleaseBrake(); }

	if(Application.GetInput().IsKeyDown(sf::Key::A)) { if(PlayerDriving == true) pCar->Turn(-1); }
	else if(Application.GetInput().IsKeyDown(sf::Key::D)) { if(PlayerDriving == true) pCar->Turn(1); }
	else { if(PlayerDriving == true) pCar->ReleaseWheel(); }
	
	if(Application.GetInput().IsMouseButtonDown(sf::Mouse::Left)) { PlayerShooting = true; }
	else PlayerShooting = false;

	if(Application.GetInput().IsKeyDown(sf::Key::Return)) {
		if(PlayerDriving == false) {
			PlayerWannaDrive = true;
			return;
		}
	}
	else PlayerWannaDrive = false;

	if(Application.GetInput().IsKeyDown(sf::Key::LShift)) {
		if(PlayerDriving == true) {
			PlayerDriving = false;
			PlayerWannaDrive = false;
			SetPosition(pCar->GetPosition()->x - 75, pCar->GetPosition()->y);
			pCar->Exit();
			pCar = NULL;
			return;
		}
	}
}

void CPlayer::Move(sf::RenderWindow &Application) {
	sf::Vector2i MousePosition;

	MousePosition.x = Application.GetInput().GetMouseX();
	MousePosition.y = Application.GetInput().GetMouseY();

	CalculateAngle(MousePosition, Application);

	if(PlayerMoving == true && Collision == true) {
		PlayerOffset.x = static_cast<float>(sin(PlayerAngle / 180 * 3.1415) * PlayerVelocity);
		PlayerOffset.y = static_cast<float>(-cos(PlayerAngle / 180 * 3.1415) * PlayerVelocity);
		Position.x -= PlayerOffset.x;
		Position.y -= PlayerOffset.y;
	}

	if(PlayerMoving == true && Collision == false) {
		PlayerOffset.x = static_cast<float>(sin(PlayerAngle / 180 * 3.1415) * PlayerVelocity);
		PlayerOffset.y = static_cast<float>(-cos(PlayerAngle / 180 * 3.1415) * PlayerVelocity);
		Position.x += PlayerOffset.x;
		Position.y += PlayerOffset.y;
	}

	if(PlayerDriving == true) {
		Position = *(pCar->GetPosition());
	}

	if(Position.x < Application.GetWidth() / 2) Position.x = Application.GetWidth() / 2;
	if(Position.y < Application.GetHeight() / 2) Position.y = Application.GetHeight() / 2;


	pWeapon->UpdateBullets(Application, &Position);
	//if(PlayerDriving == true)
	//{
	//	pCar->Update();
	//	pCar->Move();
	//}
}

void CPlayer::Draw(sf::RenderWindow &Application) {
	if(PositionSet == false) {
		Position.x = Application.GetWidth() / 2;
		Position.y = Application.GetHeight() / 2;

		PlayerPositionOnScreen.x = Application.GetWidth() / 2;
		PlayerPositionOnScreen.y = Application.GetHeight() / 2;

		PositionSet = true;
	}
	
	Sprite.SetPosition(PlayerPositionOnScreen);
	Sprite.SetRotation(-PlayerAngle);
	if(PlayerDriving == false) Application.Draw(Sprite);

	pWeapon->DrawBullets(Application);

	//sf::String Speed(int2str(pCar->GetSpeed()));
	//Speed.SetPosition(50.f, 5.f);
	//Application.Draw(Speed);
	//sf::String Turn(int2str(pCar->GetTurn()));
	//Turn.SetPosition(100.f, 5.f);
	//Application.Draw(Turn);
}

void CPlayer::Shoot() { if(PlayerShooting == true) pWeapon->Shoot(&Position, &PlayerAngle); }

void CPlayer::CheckCollision(int TileID, sf::RenderWindow &Application) {
	if(TileID == 4) Collision = true;
	else Collision = false;
}

void CPlayer::SetPosition(sf::Vector2f PlayerPosition) {
	Position.x = PlayerPosition.x;
	Position.y = PlayerPosition.y;
}

void CPlayer::SetPosition(float PositionX, float PositionY) {
	Position.x = PositionX;
	Position.y = PositionY;
}

sf::Vector2f CPlayer::GetPosition() { return Position; }

void CPlayer::CalculateAngle(sf::Vector2i MousePosition, sf::RenderWindow &Application) {
	float TriangleWidth = 0;
	float TriangleHeight = 0;

	int MouseX = MousePosition.x;
	int MouseY = MousePosition.y;

	int WindowWidth = Application.GetWidth();
	int WindowHeight = Application.GetHeight();

	if(MouseX < WindowWidth && MouseX > 0 && MouseY < WindowHeight && MouseY > 0) {
		if(MouseX > WindowWidth / 2 && MouseY < WindowHeight / 2) {
			TriangleWidth = static_cast<float>(MouseX - WindowWidth / 2);
			TriangleHeight = static_cast<float>(WindowHeight / 2 - MouseY);
			PlayerAngle = atan(TriangleWidth / TriangleHeight) * 60;
		}
		if(MouseX > WindowWidth / 2 && MouseY > WindowHeight / 2) {
			TriangleWidth = static_cast<float>(MouseX - WindowWidth / 2);
			TriangleHeight = static_cast<float>(MouseY - WindowHeight / 2);
			PlayerAngle = atan(TriangleHeight / TriangleWidth) * 60 + 90;
		}
		if(MouseX < WindowWidth / 2 && MouseY > WindowHeight / 2) {
			TriangleWidth = static_cast<float>(WindowWidth / 2 - MouseX);
			TriangleHeight = static_cast<float>(MouseY - WindowHeight / 2);
			PlayerAngle = atan(TriangleWidth / TriangleHeight) * 60 + 180;
		}
		if(MouseX < WindowWidth / 2 && MouseY < WindowHeight / 2) {
			TriangleWidth = static_cast<float>(WindowWidth / 2 - MouseX);
			TriangleHeight = static_cast<float>(WindowHeight / 2 - MouseY);
			PlayerAngle = atan(TriangleHeight / TriangleWidth) * 60 + 270;
		}
		if(MouseX == WindowWidth / 2) {
			TriangleWidth = 0;
			if(MouseY < WindowHeight / 2) TriangleHeight = 1;
			if(MouseY > WindowHeight / 2) TriangleHeight = -1;
		}
		if(MouseY == WindowHeight / 2) {
			TriangleHeight = 0;
			if(MouseX < WindowWidth / 2) TriangleWidth = -1;
			if(MouseX > WindowWidth / 2) TriangleWidth = 1;
		}
	}

	if(PlayerAngle > 360) PlayerAngle = 0;
}

float CPlayer::GetAngle() { return PlayerAngle; }

bool CPlayer::PlayerWannaDrive() { return PlayerWannaDrive; }
bool CPlayer::PlayerDriving() { return PlayerDriving; }

void CPlayer::SetDrivingState(bool State) { PlayerDriving = State; }
CWeapon* CPlayer::GetWeaponPointer() { return pWeapon; }
void CPlayer::SetPlayerCar(CCar** pCar) { this->pCar = *pCar; }

void CPlayer::ResetData() {
	PlayerPositionOnScreen.x = 0;
	PlayerPositionOnScreen.y = 0;
	PlayerOffset.x = 0;
	PlayerOffset.y = 0;
	PlayerAngle = 0;
	PlayerVelocity = 3;
	PositionSet = false;
	PlayerMoving = false;
	PlayerShooting = false;
	PlayerDriving = false;
	PlayerWannaDrive = false;
	Collision = false;
}
