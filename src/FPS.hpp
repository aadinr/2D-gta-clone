#ifndef FPS_HPP
#define FPS_HPP

#include <SFML/Graphics.hpp>

class CFPS {
private:

	sf::Vector2f Position;
	sf::Color Color;
	sf::Clock Clock;
	sf::Shape Shape;
	int FPS;
	float Thickness;
	float Width;
	float Height;
	float Spacing;
	float LeftOffset;
	float TopOffset;
	float LetterTop;
	float LetterMiddle;
	float LetterBottom;

public:

	CFPS();
	CFPS(sf::Vector2f Position, sf::Color Color);
	void Draw(sf::RenderWindow& Application);
	void DrawNumber(sf::RenderWindow& Application, int Number, int Offset);
};

#endif