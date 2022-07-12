//rough draft of rendering board and moving piece

#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;
void update(RenderWindow& window, CircleShape& piece, int* x_grid, int* y_grid);

int main()
{
	RenderWindow window(VideoMode(800, 800), "baghchal", Style::Default);
	window.setFramerateLimit(60);
	int x_grid[5], y_grid[5];					
	for (int i = 0; i < 5; i++) {						//Initializing grid(map) of Board
		x_grid[i] = i * window.getSize().x / 5;
		y_grid[i] = i * window.getSize().y / 5;
	}
	CircleShape piece(80.f);							//Initializing piece
	piece.setPosition(Vector2f(x_grid[0], y_grid[0]));
	piece.setFillColor(Color::Red);

	VertexArray Borders(LineStrip, 4);					//Drawing Borders
	Borders[0].position = Vector2f(0, 0);
	Borders[1].position = Vector2f(window.getSize().x, 0);
	Borders[2].position = Vector2f(window.getSize().x, window.getSize().y);
	Borders[3].position = Vector2f(0, window.getSize().y);

	VertexArray V_lines(LineStrip, 8);					//Drawing Vertical lines
	VertexArray H_lines(LineStrip, 8);					//Drawing Horizontal lines

	for (int i = 1,j = 0; i < 5; i++,j++) {
		if (i % 2 == 1) {
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + window.getSize().y / 5);
		}
		else {
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + window.getSize().y / 5);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
		}
	}

	for (int i = 1, j = 0; i < 5; i++, j++) {
		if (i % 2 == 1) {
			H_lines[j].position = Vector2f(x_grid[0], y_grid[i]);
			j++;
			H_lines[j].position = Vector2f(x_grid[4] + window.getSize().x / 5, y_grid[i] );
		}
		else {
			H_lines[j].position = Vector2f(x_grid[4] + window.getSize().x / 5, y_grid[i]);
			j++;
			H_lines[j].position = Vector2f(x_grid[0], y_grid[i]);
			
		}
	}

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		update(window, piece, x_grid, y_grid);

		window.clear(Color::Black);
		
		window.draw(V_lines);
		window.draw(H_lines);
		window.draw(Borders);

		window.draw(piece);
		window.display();

	}
}
void update(RenderWindow& window, CircleShape& piece, int* x_grid, int* y_grid) {
	float r = piece.getRadius();											//Radius of piece
	float x = piece.getPosition().x, y = piece.getPosition().y;				//position of top left corner of piece
	int x_m = Mouse::getPosition(window).x, y_m = Mouse::getPosition(window).y;		// position of mouse
	if (x_m > x && x_m<x + 2 * r && y_m>y && y_m < y + 2 * r && Mouse::isButtonPressed(Mouse::Left)) {
		piece.setPosition(Vector2f(x_m - r, y_m - r));
	}
	else {
		int x_pos = (x + r) / (window.getSize().x / 5), y_pos = (y + r) / (window.getSize().y / 5); //calculating tile
		if (x_pos > 4)x_pos = 4;							//in case mouse is out of window
		if (y_pos > 4)y_pos = 4;
		if (x_pos < 0)x_pos = 0;
		if (y_pos < 0)y_pos = 0;
		piece.setPosition(Vector2f(x_grid[x_pos], y_grid[y_pos]));
	}
}


