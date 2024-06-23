#pragma once
#include "circleConstraint.h"
#include "boxConstraint.h"

class Renderer {
private:
	sf::RenderTarget& m_target;

public:
	Renderer(sf::RenderTarget& target) : m_target(target) {}

	void render(const Solver& solver) const {
		const Constraint* constraint = solver.getConstraint();
		const BoxConstraint* boxConstraint = dynamic_cast<const BoxConstraint*>(constraint);
		/*const CircleConstraint* circleConstraint = dynamic_cast<const CircleConstraint*>(constraint);
		sf::CircleShape constraint_background{ circleConstraint->getRadius() };
		constraint_background.setPosition(circleConstraint->getCentre());*/
		//constraint_background.setOrigin(constraint_background.getRadius(), constraint_background.getRadius());
		//constraint_background.setPointCount(128);

		sf::RectangleShape constraint_background{ boxConstraint->getSize() };
		constraint_background.setOrigin(boxConstraint->getSize() / 2.0f);
		constraint_background.setFillColor(sf::Color::Cyan);
		m_target.draw(constraint_background);

		sf::CircleShape particle;
		const auto& objects = solver.getObjects();
		for (const auto& obj : objects) {
			particle.setPosition(obj.position);
			particle.setRadius(obj.radius);
			//particle.setFillColor(sf::Color::Magenta);
			particle.setFillColor(obj.color);
			particle.setOrigin(obj.radius, obj.radius);
			m_target.draw(particle);
		}


	}
};