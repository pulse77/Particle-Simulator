#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "constraint.h"
#include "verletObject.h"

class Solver
{
private:
	std::vector<VerletObject> m_objects;
	sf::Vector2f m_gravity{0,1000.0f};
	const Constraint* m_constraint;
	float m_substeps{8};
	float m_update_interval{0};
	float m_time{0};

	void updateObjects(float dt) {
		for (auto& obj : m_objects) {
			obj.update(dt);
		}
	}
	void applyGravity() {
		for (auto& obj : m_objects) {
			obj.accelerate(m_gravity);
		}
	}

	bool resolveCollision(VerletObject& obj1, VerletObject& obj2) {
		sf::Vector2f collision_axis = obj1.position - obj2.position;
		float dist = std::hypotf(collision_axis.x, collision_axis.y);
		float sum_radius = obj1.radius + obj2.radius;
		if (dist >= sum_radius) {
			return false; // no collision detected
		}

		const sf::Vector2f n = collision_axis / dist;
		float d1 = obj2.radius * (1 - dist / sum_radius);
		float d2 = sum_radius - dist - d1;
		obj1.position += d1 * n;
		obj2.position -= d2 * n;
		return true;
	}

	void checkCollisions() {
		int n = m_objects.size();
		for (int i = 0; i < n; i++) {
			auto& obj1 = m_objects[i];
			for (int j = i + 1; j < n; j++) {
				auto& obj2 = m_objects[j];
				resolveCollision(obj1, obj2);
			}
		}
	}

	void applyConstraints() {
		for (auto& obj : m_objects) {
			m_constraint->applyConstraint(obj);
		}
	}


public:
	Solver(const Constraint* constraint) : m_constraint(constraint) {}

	VerletObject& addObject(sf::Vector2f position, sf::Vector2f velocity, float radius) {
		return m_objects.emplace_back(position, velocity, radius);
		printf("Spawning Particle: %u\n", m_objects.size());
	}

	void SetUpdateInterval(float dt) {
		m_update_interval = dt;
	}


	void update() {
		m_time += m_update_interval;
		const float sub_dt = m_update_interval / m_substeps;
		for (int i = 0; i < m_substeps; i++) {
			applyGravity();
			checkCollisions();
			applyConstraints();
			updateObjects(sub_dt);
		}
	}

	const std::vector<VerletObject>& getObjects() const {
		return m_objects;
	}

	const Constraint* getConstraint() const {
		return m_constraint;
	}
};