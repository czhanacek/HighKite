#include <iostream>
#include <Windows.h>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.h"


int main(void)
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::Texture texture;
	texture.loadFromFile("texture.png");
	//Eagle b(200, 0);
	//b.setTexture(texture);
	//b.scale(.05, .05);
	//Bird b2(1000, 0);
	//b2.setTexture(texture);
	//b2.scale(.05, .05);
	Spaceship b3(350,0);
	b3.setTexture(texture);
	b3.scale(.05, .05);
	sf::Texture texture2;
	texture2.loadFromFile("fire.png");
	sf::Sprite bullet;
	bullet.setTexture(texture2);
	bullet.scale(.1, .1);
	b3.bullet = bullet;

    while (window.isOpen())
    {
		window.clear();
		window.draw(b3);
		window.display();
        sf::Event event;
		float x = 0;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
				
        }

		std::vector<sf::RectangleShape> projectiles;
		sf::RectangleShape newProjectile;

		if (b3.angle % 30 == 0)
		{
			newProjectile.setPosition(b3.getPosition().x, b3.getPosition().y + 1);
			newProjectile.setSize(sf::Vector2f(5, 5));
			newProjectile.setFillColor(sf::Color::Green);
			newProjectile.setOutlineColor(sf::Color::Green);
			newProjectile.setOutlineThickness(1);
			projectiles.push_back(newProjectile);
		}
		int i2 = 0;
		for (auto i = projectiles.begin(); i < projectiles.end(); i++)
		{
			projectiles[i2].move(0, 3);
			window.draw(projectiles[i2]);
			i2++;
		}
		
		b3.movement();
		
		std::cout << "X Position : " << b3.getPosition().x << std::endl;
		std::cout << "Y Position : " << b3.getPosition().y << std::endl;
		window.clear();
    }
	

    return 0;

	return 0;
}
