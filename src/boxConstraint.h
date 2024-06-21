#pragma once
#include "constraint.h"
#include <cmath>

class BoxConstraint : public Constraint {
public:
	BoxConstraint(sf::Vector2f centre, sf::Vector2f size)
		: centre(centre), size(size) {}

	bool isWithin(VerletObject& object) const override {
		const sf::Vector2f& pos = object.position;
		const float& radius = object.radius;
		if (pos.x < centre.x - size.x - radius || pos.x > centre.x + size.x + radius) return false;
		if (pos.y < centre.y - size.y - radius || pos.y > centre.y + size.y + radius) return false;
		return true;
	}
	void applyConstraint(VerletObject& object) const override;

	const sf::Vector2f& getCentre() const { return centre; }
	const sf::Vector2f& getSize() const { return size; }
private:
	sf::Vector2f centre;
	sf::Vector2f size;
};