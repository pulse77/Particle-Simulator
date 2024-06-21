#pragma once
#include "constraint.h"
#include <cmath>

class CircleConstraint : public Constraint {
public:
	CircleConstraint(sf::Vector2f centre, float radius) 
		: centre(centre), radius(radius) {}

	bool isWithin(VerletObject& object) const override {
		sf::Vector2f delta_pos = object.position - centre;
		return std::hypotf(delta_pos.x, delta_pos.y) <= radius + object.radius;
	}
	void applyConstraint(VerletObject& object) const override;

	const sf::Vector2f& getCentre() const { return centre; }
	const float& getRadius() const { return radius; }
private:
	sf::Vector2f centre;
	float radius;
};