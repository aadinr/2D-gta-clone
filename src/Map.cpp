#include "Map.hpp"

CMap::CMap() {
	Width = 20;
	Height = 20;
	NumberOfTilesInHorizon = 0;
	NumberOfTilesInVertical = 0;

	for(int i = 0; i < Height; i++) {
		for(int j = 0; j < Width; j++) {
			Map[i][j] = 0;
		}
	}

	for(int i = 0; i < 8; i++) {
		CollisionTiles[i] = 0;
	}
}

CMap::~CMap() {
	// TODO
}

bool CMap::LoadTileset(std::string TilesetFilename, int WindowWidth, int WindowHeight) {
	if(!TilesetImage.LoadFromFile(TilesetFilename)) {
		return false;
	}

	else {
		TilesetImage.SetSmooth(false);
		Tileset.SetImage(TilesetImage);
	}
	
	NumberOfTilesInHorizon = static_cast<int>(WindowWidth / 128) + 1;
	NumberOfTilesInVertical = static_cast<int>(WindowHeight / 128) + 2;

	return true;
}

void CMap::Draw(sf::RenderWindow &Application, sf::Vector2f PlayerPosition) {
	// currently map is hardcoded
	int Map[20][20] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 0, 1, 1, 1, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 4, 4, 4,
						4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 0, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 0, 0, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

	int TileNrX = (static_cast<int>(PlayerPosition.x) - static_cast<int>(PlayerPosition.x) % 128) / 128 - ((NumberOfTilesInHorizon / 2) - 1);
	int TileNrY = (static_cast<int>(PlayerPosition.y) - static_cast<int>(PlayerPosition.y) % 128) / 128 - ((NumberOfTilesInVertical / 2) - 1);
	if(TileNrX < 0) TileNrX = 0;
	if(TileNrY < 0) TileNrY = 0;
	int DiffX = static_cast<int>(PlayerPosition.x) % 128;
	int DiffY = static_cast<int>(PlayerPosition.y) % 128;

	for(int i = 0; i < NumberOfTilesInVertical; i++) {
		for(int j = 0; j < NumberOfTilesInHorizon; j++) {
			int X = (Map[i + TileNrY][j + TileNrX] % 3) * 128;
			int Y = (Map[i + TileNrY][j + TileNrX] / 3) * 128;
			Tileset.SetSubRect(sf::IntRect(X, Y, X + 128, Y + 128));
			Tileset.SetPosition(j * 128 - static_cast<float>(DiffX), i * 128 - static_cast<float>(DiffY));
			Application.Draw(Tileset);
		}
	}
}

int CMap::GetCollisionTile(sf::Vector2f PlayerPosition) const {
	int Map[20][20] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 0, 1, 1, 1, 0, 4, 4, 4, 4, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 3, 0, 0, 0, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 4, 4, 4,
						4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 0, 4, 4, 4, 4, 4, 3, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 0, 0, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 3, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
						4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

	int TileNrX = (static_cast<int>(PlayerPosition.x - 64) - static_cast<int>(PlayerPosition.x - 64) % 128) / 128;
	int TileNrY = (static_cast<int>(PlayerPosition.y - 16) - static_cast<int>(PlayerPosition.y - 16) % 128) / 128;

	TileNrX += 3;
	TileNrY += 2;

	return Map[TileNrY][TileNrX];
}
