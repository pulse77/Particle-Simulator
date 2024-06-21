#include "circleConstraint.h"

void CircleConstraint::applyConstraint(VerletObject& object) const {
    const sf::Vector2f v = centre - object.position;
    const float dist = sqrt(v.x * v.x + v.y * v.y);
    if (dist > (radius - object.radius)) {
        const sf::Vector2f n = v / dist;
        object.position = centre - n * (radius - object.radius);
    }
}