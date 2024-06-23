#pragma once
#include <SFML/Graphics.hpp>

struct VerletObject
{
	sf::Color color;
	sf::Vector2f position;
	sf::Vector2f last_position;
	sf::Vector2f acceleration;
	float radius;

	VerletObject() = default;
	VerletObject(float radius) : radius(radius) {}
	VerletObject(const sf::Vector2f& position, const sf::Vector2f& velocity, float radius) : position(position), radius(radius) {
		last_position = position; // for 0 velocity
		//color = sf::Color{ (uint32_t)rand() };
		color.r = rand() % 256;
		color.g = rand() % 256;
		color.b = rand() % 256;
		color.a = 220 + rand() % (256 - 220);
		//color.a = 50 + rand() % (256 - 50);
		//setVelocity(velocity, dt);
	}

	void update(float dt) {
		sf::Vector2f delta_pos = position - last_position;
		last_position = position;
		position += delta_pos + acceleration * dt * dt;
		acceleration = {};

		if (std::isnan(position.x) || std::isnan(position.y)) {
			position = {float(- 500 + rand() % 1000), float(- 500 + rand() % 1000)};
			last_position = position;
			return;
		}
	}

	void accelerate(const sf::Vector2f& accel) {
		acceleration += accel;
	}

	void setVelocity(const sf::Vector2f& velocity, float dt) {
		last_position = position - velocity * dt;
	}
};