#include "FPS.hpp"

CFPS::CFPS() {
	Position.x = 5.0;
	Position.y = 5.0;
	Color.r = 255;
	Color.g = 255;
	Color.b = 255;
	FPS = 0;
	Thickness = 2;
	Width = 4;
	Height = 10;
	Spacing = 10;
	LeftOffset = 5;
	TopOffset = 10;
	LetterTop = TopOffset;
	LetterMiddle = TopOffset + Height / 2;
	LetterBottom = TopOffset + Height;
	Clock.Reset();
}

CFPS::CFPS(sf::Vector2f Position, sf::Color Color) {
	this->Position = Position;
	this->Color = Color;
	FPS = 0;
	Thickness = 2;
	Width = 4;
	Height = 10;
	Spacing = 10;
	LeftOffset = 5;
	TopOffset = 10;
	LetterTop = TopOffset;
	LetterMiddle = TopOffset + Height / 2;
	LetterBottom = TopOffset + Height;
	Clock.Reset();
}

void CFPS::Draw(sf::RenderWindow& Application) {
	DrawNumber(Application, (FPS / 1000) % 10, 0);
	DrawNumber(Application, (FPS / 100) % 10, 1);
	DrawNumber(Application, (FPS / 10) % 10, 2);
	DrawNumber(Application, (FPS) % 10, 3);

	FPS = static_cast<int>(1.0 / Clock.GetElapsedTime());
	Clock.Reset();
}

void CFPS::DrawNumber(sf::RenderWindow& Application, int Number, int Offset) {
	float LetterLeft = static_cast<float>(LeftOffset + (Offset * Spacing));
	float LetterRight = LetterLeft + Width;

	switch(Number) {
	case 0:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterBottom, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 1:
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 2:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterMiddle, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterMiddle, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterBottom, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 3:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterBottom, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterMiddle, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		break;

	case 4:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterMiddle, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		break;
	
	case 5:
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterLeft, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterMiddle, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterMiddle, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterBottom, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 6:
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterLeft, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterBottom, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterBottom, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterMiddle, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		break;

	case 7:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 8:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterMiddle, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterBottom, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		break;

	case 9:
		Application.Draw(sf::Shape::Line(LetterLeft, LetterBottom, LetterRight, LetterBottom, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterBottom, LetterRight, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterRight, LetterTop, LetterLeft, LetterTop, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterTop, LetterLeft, LetterMiddle, Thickness, Color, 0, Color));
		Application.Draw(sf::Shape::Line(LetterLeft, LetterMiddle, LetterRight, LetterMiddle, Thickness, Color, 0, Color));
		break;

	default:
		break;
	}
}
