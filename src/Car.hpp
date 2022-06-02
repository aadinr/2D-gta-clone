#ifndef CAR_HPP
#define CAR_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

class CCar {
	sf::IntRect Rect;
	sf::Sprite Sprite;
	sf::Vector2f PositionWorld;
	sf::Vector2f Position;
	bool Throttle;
	bool Brakes;
	float ThrottleForce;
	sf::Vector2f Acceleration;
	float Mass;
	sf::Vector2f Velocity;
	float Angle;
	bool Full;
	int Turning;

public:
	CCar();
	~CCar();
	void Create(sf::Image& CarsSet, sf::Vector2f& PlayerPosition, sf::RenderWindow& Application);
	void Update();
	void Gas();
	void ReleaseGas();
	void Brake();
	void ReleaseBrake();
	void Turn(int Direction);
	void ReleaseWheel();
	void Enter();
	void Exit();
	void Draw(sf::RenderWindow &Application, sf::Vector2f &PlayerPosition);
	sf::Vector2f *GetPosition();
};

#endif