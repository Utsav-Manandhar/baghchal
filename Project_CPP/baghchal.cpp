
#pragma once

#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Animal.h"
#include"Bakhraa.h"
using namespace std;
using namespace sf;
//bakhraa


bool game_is_over=false;
bool is_goats_turn = true;
bool is_goats_placed = false;



void update_events(RenderWindow& window, Bakhraa goats[], int* x_grid, int* y_grid, int grid[][5]);
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
	Bakhraa goats[20];
	for(int i=0;i<20;i++)
	{
		goats[i].setRadius(40.f);
		goats[i].set_Position(-1, -1);
		goats[i].setFillColor(Color::White);
		goats[i].setstate(dead);
	}


	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		update_events(window, goats, x_grid, y_grid, grid);


		window.clear(Color::Black);

		window.draw(V_lines);
		window.draw(H_lines);
		window.draw(Borders);
		for(int i=0;i<20;i++)		//draw goats on board
		{
			if(goats[i].getstate())
			{
				window.draw(goats[i]);
			}
		}

		window.display();

	}
}


void update_events(RenderWindow& window, Bakhraa goats[], int* x_grid, int* y_grid, int grid[][5])
{    //mouse positon to record in pixels
	int x_m=Mouse::getPosition(window).x, y_m=Mouse::getPosition(window).y;
	int x_mouse=-1,y_mouse=-1;//mouse to record position in grid placement
	if(x_m>400&&x_m<800&&y_m>200&&y_m<600)
	{ //changing pixel to grid state
		x_mouse = (x_m - 400) / 80;
		y_mouse = (y_m - 200) / 80;
	}
	if(!game_is_over)
	{
		if(is_goats_turn)
		{
	        if(!is_goats_placed)
			{
				if(grid[x_mouse][y_mouse]==0 && Mouse::isButtonPressed(Mouse::Left)&&bakhraa_count<20&&x_m>400&&x_m<800&&y_m>200&&y_m<600)
				{
					grid[x_mouse][y_mouse] = 1;
					goats[bakhraa_count].set_Position(x_mouse, y_mouse);
					goats[bakhraa_count].setstate(alive);
					goats[bakhraa_count].setPosition(Vector2f(x_grid[x_mouse], y_grid[y_mouse]));
					bakhraa_count++;
					//goat turn sakkaidine
				}
			}
			
		}

	}
}
