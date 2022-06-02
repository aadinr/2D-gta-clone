#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

class CMap {
	int Width;
	int Height;
	int NumberOfTilesInHorizon;
	int NumberOfTilesInVertical;
	sf::Image TilesetImage;
	sf::Sprite Tileset;
	int Map[20][20];
	int CollisionTiles[8];

public:
	CMap();
	~CMap();
	bool LoadTileset(std::string TilesetFilename, int WindowWidth, int WindowHeight);
	void Draw(sf::RenderWindow &Application, sf::Vector2f PlayerPosition);
	int GetCollisionTile(sf::Vector2f PlayerPosition) const;
};

#endif