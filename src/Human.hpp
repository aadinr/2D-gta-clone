#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class CHuman {
protected:

	sf::Image Image;
	sf::Sprite Sprite;
	sf::Vector2f Position;

public:
	CHuman() {
		Position.x = 0;
		Position.y = 0;
	}

	virtual ~CHuman() {
		// TODO
	}

	virtual void LoadSprite(std::string ImageFilename) {
		Image.LoadFromFile(ImageFilename);
		Image.CreateMaskFromColor(sf::Color(255, 0, 255));
		Sprite.SetImage(Image);
	}

	virtual void Draw(sf::RenderWindow& Application) {
		Sprite.SetPosition(Position);
		Application.Draw(Sprite);
	}
};

#endif