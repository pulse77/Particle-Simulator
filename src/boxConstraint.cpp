#include "boxConstraint.h"
#include <cmath>

void BoxConstraint::applyConstraint(VerletObject& object) const {
	sf::Vector2f displacement = object.position - centre;
	if (abs(displacement.x) + object.radius > size.x / 2.0f) {
		// Constrain horizontally
		float delta_x = abs(displacement.x) + object.radius - size.x / 2.0f;
		int sign = displacement.x < 0 ? -1 : 1;
		object.position.x -= delta_x * sign;
	}
	if (abs(displacement.y) + object.radius > size.y / 2.0f) {
		// Constrain vertically
		float delta_y = abs(displacement.y) + object.radius - size.y / 2.0f;
		int sign = displacement.y < 0 ? -1 : 1;
		object.position.y -= delta_y * sign;
	}
}