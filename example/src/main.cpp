#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

using namespace sf; // подключаем пространство имен sf

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	 int size_x = 700;
	 int size_y = 700;

	// Объект, который, собственно, является главным окном приложения
	RenderWindow window(VideoMode(size_x, 700), "Lab1", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	sf::View view = window.getDefaultView();

	// Создаем треугольник
	const float radius = 65.0f;
	CircleShape circle(radius);

	circle.setFillColor(Color::Blue); // устанавливаем цвет треугольника - синий
	circle.setOrigin(radius, radius);
	circle.setPosition(radius, 350);

	CircleShape triangle(radius, 8);

	triangle.setFillColor(Color::Black); // устанавливаем цвет треугольника - синий
	triangle.setOrigin(radius, radius);
	triangle.setPosition(700 - radius, 350);

	float speed_x_c = 3.0f;
	float speed_y_c = 3.0f;

	float speed_x_t = 4.0f;
	float speed_y_t = -4.0f;

	float scale_c = 1.01f;
	float scale_t = 1.5f;

	const float upscale = 1.5;
	const float downscale = 1. / upscale;

	Vector2f position_c = circle.getPosition();
	Vector2f position_t = triangle.getPosition();

	Clock timer;

	// Главный цикл приложения: выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
				window.close(); // тогда закрываем его

			if (event.type == sf::Event::Resized) {
					// resize my view
					view.setSize({
									static_cast<float>(event.size.width),
									static_cast<float>(event.size.height)
					});

					size_x = static_cast<float>(event.size.width);
					size_y = static_cast<float>(event.size.height);
					
					window.setView(view);
					// and align shape
			}
		}

		if ((speed_x_c > 0 && position_c.x + circle.getRadius() > size_x) ||
				(speed_x_c < 0 && position_c.x - circle.getRadius() < 0))
		{
			speed_x_c = -speed_x_c;
			scale_c = 1. / scale_c;
		}

		if ((speed_y_c > 0 && position_c.y + circle.getRadius() > size_y) ||
				(speed_y_c < 0 && position_c.y - circle.getRadius() < 0))
		{
			speed_y_c = -speed_y_c;
			scale_c = 1. / scale_c;
		}

		position_c.x += speed_x_c;
		position_c.y += speed_y_c;

		sf::Vector2f scale = circle.getScale();
		//circle.setScale(scale.x * scale_c, scale.y * scale_c);

		circle.setPosition(position_c);
		//circle.scale(scale_c, scale_c);


		std::cout << "================================================\n";
		std::cout << "Circle { x: " << position_c.x - circle.getRadius() << ", y: " << position_c.y - circle.getRadius() << " }"<< std::endl;
		std::cout << "Window { w: " << window.getSize().x << ", h: " << window.getSize().y << " }" << std::endl;
		std::cout << "================================================\n";

		//circle.setRadius(circle.getRadius() * scale_c);

		if ((speed_x_t > 0 && position_t.x + radius > 700) ||
				(speed_x_t < 0 && position_t.x - radius < 0))
		{
			speed_x_t = -speed_x_t;
		}

		if ((speed_y_t > 0 && position_t.y + radius > 700) ||
				(speed_y_t < 0 && position_t.y - radius < 0))
		{
			speed_y_t = -speed_y_t;
		}

		position_t.x += speed_x_t;
		position_t.y += speed_y_t;

		triangle.setPosition(position_t);

		// Установка цвета фона
		window.clear(Color(250, 220, 100, 0));
		window.draw(circle); // отрисовка треугольника
		window.draw(triangle);
		// Отрисовка окна
		window.display();
	}

	return 0;
}