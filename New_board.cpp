
#pragma once

#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
using namespace std;
using namespace sf;



int main()
{
	int screen_height = 800, screen_width = 1200;
	RenderWindow window(VideoMode(screen_width, screen_height), "baghchal", Style::Default);
	window.setFramerateLimit(60);
	int grid[5][5];										//Initializing grid(map) of Board
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			grid[i][j] = 0;
		}
	}
	int board_height = 400, board_width = 400;
	int board_origin_x = 400, board_origin_y = 200;
	int x_grid[5], y_grid[5];
	for (int i = 0; i < 5; i++) {						//Initializing pixel grid of board
		x_grid[i] = board_origin_x + i * board_width / 5;
		y_grid[i] = board_origin_y + i * board_height / 5;
	}

	CircleShape piece;							//Initializing piece
	piece.setRadius(40.f);
	piece.setPosition(Vector2f(x_grid[0], y_grid[0]));
	piece.setFillColor(Color::Red);

	VertexArray Borders(LineStrip, 5);					//Drawing Borders
	Borders[0].position = Vector2f(board_origin_x, board_origin_y);
	Borders[1].position = Vector2f(board_origin_x + board_width, board_origin_y);
	Borders[2].position = Vector2f(board_origin_x + board_width, board_origin_y + board_height);
	Borders[3].position = Vector2f(board_origin_x, board_origin_y + board_height);
	Borders[4].position = Vector2f(board_origin_x, board_origin_y);

	VertexArray V_lines(LineStrip, 8);					//Drawing Vertical lines
	VertexArray H_lines(LineStrip, 8);					//Drawing Horizontal lines

	for (int i = 1, j = 0; i < 5; i++, j++) {
		if (i % 2 == 1) {
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + board_height / 5);
		}
		else {
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + board_height / 5);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
		}
	}

	for (int i = 1, j = 0; i < 5; i++, j++) {
		if (i % 2 == 1) {
			H_lines[j].position = Vector2f(x_grid[0], y_grid[i]);
			j++;
			H_lines[j].position = Vector2f(x_grid[4] + board_width / 5, y_grid[i]);
		}
		else {
			H_lines[j].position = Vector2f(x_grid[4] + board_width / 5, y_grid[i]);
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


		window.clear(Color::Black);

		window.draw(V_lines);
		window.draw(H_lines);
		window.draw(Borders);

		window.draw(piece);
		window.display();

	}
}




