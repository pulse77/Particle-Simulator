#include <SFML/Graphics.hpp>
#include "solver.h"
#include "renderer.h"
#include "circleConstraint.h"

#include <iostream>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	constexpr uint32_t WINDOW_WIDTH = 1920;
	constexpr uint32_t WINDOW_HEIGHT = 1080;
	constexpr uint32_t FPS_LIMIT = 60;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Particle Simulator", sf::Style::Default);
	window.setFramerateLimit(FPS_LIMIT);

	sf::View view{ {0.0f, 0.0f}, {WINDOW_WIDTH, WINDOW_HEIGHT} };
	window.setView(view);


	const sf::Vector2f constraintCentre{0.0f, 0.0f };
	constexpr float constraintRadius{500.0f};
	CircleConstraint cc(constraintCentre, constraintRadius);
	Solver solver(&cc);
	solver.SetUpdateInterval(1.0f / FPS_LIMIT);
	Renderer renderer{window};

	sf::Clock clock;
	float currTime{};
	constexpr int particlesToSpawn = 500;
	constexpr float timeBetweenSpawns = 0.0025f;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 1.0);

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.scancode == sf::Keyboard::Scancode::Escape)
					window.close();
				if (evnt.key.scancode == sf::Keyboard::Scancode::Space) {
					std::cout << "removing\n";
					std::vector<VerletObject>& objects = const_cast<std::vector<VerletObject>&>(solver.getObjects());
					int index = rand() % objects.size();
					objects.erase(objects.begin() + index);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (evnt.mouseButton.button == sf::Mouse::Button::Left) {
					sf::Vector2i windowPixelPos = sf::Mouse::getPosition(window);
					sf::Vector2f worldPos = window.mapPixelToCoords(windowPixelPos);
					solver.addObject(worldPos, {0,0}, 20.0f);
				}

				break;
			}
		}

		float deltaTime = clock.restart().asSeconds();
		currTime += deltaTime;
		if (solver.getObjects().size() < particlesToSpawn && currTime >= timeBetweenSpawns) {
			currTime -= timeBetweenSpawns;
			float a = 2*M_PI*dis(gen);
			float r = (500.0f - 20.0f) * dis(gen);
			sf::Vector2f spawnPos = r * sf::Vector2f{sinf(a), cosf(a)};
			solver.addObject(spawnPos, { 0, 0 }, 20.0f);
		}

		solver.update();
		window.clear();
		renderer.render(solver);
		window.display();
	}

	return 0;
}