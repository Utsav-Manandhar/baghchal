#pragma once

#include <iostream>
#include<cmath>
#include<algorithm>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Animal.h"

using namespace std;
using namespace sf;

//information about bakhraa
static int bakhraa_count = 0;
static int bakhraa_killed = 0;
static int bakhraa_remain = 20;
enum goatstate { Dead, alive };
//information about turns and goats
bool game_is_over = false;
bool is_goats_turn = true;
bool is_goats_placed = false;
//information about piece moving
bool is_current_recorded = false;
int tiger_number = 0;
int goat_number = 0;
bool piece_is_clicked = false;
int  x_selected = 0, y_selected = 0;
//for tigers

int current_t_pos_x = 0, current_t_pos_y = 0;
int new_t_pos_x = 0, new_t_pos_y = 0;
int bali_ka_bakhraa = 0;
int mid_tile_x = 0, mid_tile_y = 0;
//for bakhraa
int  x_gselected = 0, y_gselected = 0;
int current_g_pos_x = 0, current_g_pos_y = 0;
int new_g_pos_x = -1, new_g_pos_y = -1;
class Bakhraa : public Animal
{
private:
	goatstate state = Dead;
public:
	Bakhraa() {}//construtor can be used to draw sfml or display texture of bakhraa

	goatstate getstate() {//just to get state of 'x' goat
		return state;

	}
	void setstate(goatstate sate) {//to set state of individual goat
		state = sate;
	}

};
class Baagh : public Animal
{
private:
	bool trapped;
public:
	Baagh()
	{
		this->trapped = false;
	}
	bool is_trapped()
	{
		return this->trapped;
	}
	void trap()
	{
		this->trapped = true;
	}

};


void update_events(RenderWindow& window, Bakhraa goats[], Baagh tigers[], int* x_grid, int* y_grid, int grid[][5]);
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
	Bakhraa goats[20];	//Initializing goats
	for (int i = 0; i < 20; i++)
	{
		goats[i].setRadius(40.f);
		goats[i].set_Position(-1, -1);
		goats[i].setFillColor(Color::White);
		goats[i].setstate(Dead);
	}
	Baagh tigers[4];//Iinitializing Tigers
	tigers[0].set_Position(0, 0);
	tigers[1].set_Position(0, 4);
	tigers[2].set_Position(4, 4);
	tigers[3].set_Position(4, 0);

	for (int i = 0; i < 4; i++)
	{
		tigers[i].setRadius(40.f);
		tigers[i].setFillColor(Color::Red);
		tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
		grid[tigers[i].get_X()][tigers[i].get_Y()] = 2;

	}





	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}

		update_events(window, goats, tigers, x_grid, y_grid, grid);


		window.clear(Color::Black);

		window.draw(V_lines);
		window.draw(H_lines);
		window.draw(Borders);
		for (int i = 0; i < 20; i++)		//draw goats on board
		{
			if (goats[i].getstate())
			{
				window.draw(goats[i]);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			window.draw(tigers[i]);
		}

		window.display();

	}
}


void update_events(RenderWindow& window, Bakhraa goats[], Baagh tigers[], int* x_grid, int* y_grid, int grid[][5])
{    //mouse positon to record in pixels
	int x_m = Mouse::getPosition(window).x, y_m = Mouse::getPosition(window).y;
	int x_mouse = 0, y_mouse = 0;//mouse to record position in grid placement
	int r = 40;

	if (x_m > 400 && x_m < 800 && y_m>200 && y_m < 600)
	{ //changing pixel to grid state
		x_mouse = (x_m - 400) / 80;
		y_mouse = (y_m - 200) / 80;
	}
	if (!game_is_over)
	{
		if (is_goats_turn)
		{//****nedd to logic bool is_goat_placed logic doesnt seem to work
			if (bakhraa_count<20)		//To check phase 1 or 2 of game 
			{
				if (grid[x_mouse][y_mouse] == 0 && Mouse::isButtonPressed(Mouse::Left) && bakhraa_count < 20 && x_m>400 && x_m < 800 && y_m>200 && y_m < 600)
				{
					grid[x_mouse][y_mouse] = 1;
					goats[bakhraa_count].set_Position(x_mouse, y_mouse);
					goats[bakhraa_count].setstate(alive);
					goats[bakhraa_count].setPosition(Vector2f(x_grid[x_mouse], y_grid[y_mouse]));
					is_goats_turn = false;
					bakhraa_count++;
				}
			}//TO MOVE GOAT
			else {
				if (grid[x_mouse][y_mouse] == 1 && !piece_is_clicked)		//to see which goat mouse is hovered over
				{
					for (int i = 0; i < 20; i++)
					{
						if (goats[i].get_X() == x_mouse && goats[i].get_Y() == y_mouse)
						{
							goat_number = i;
							break;
						}
					}
					x_gselected = goats[goat_number].getPosition().x;	//recording that piece's position
					y_gselected = goats[goat_number].getPosition().y;
				}
				//if mouse is clicked on the piece
				if (x_m > x_gselected && x_m<(x_gselected + 2 * r) && y_m>y_gselected && y_m < (y_gselected + 2 * r) && Mouse::isButtonPressed(Mouse::Left))
				{
					piece_is_clicked = true;
					if (!is_current_recorded)						//recording piece's old position once before moving starts
					{
						current_g_pos_x = goats[goat_number].get_X();
						current_g_pos_y = goats[goat_number].get_Y();
						is_current_recorded = true;
					}
					new_g_pos_x = x_mouse;
					new_g_pos_y = y_mouse;

					goats[goat_number].setPosition(Vector2f(x_m - r, y_m - r));	//making the piece follow the mouse i.e. drag and drop
					x_gselected = goats[goat_number].getPosition().x;
					y_gselected = goats[goat_number].getPosition().y;
				}
				else if (abs(new_g_pos_x - current_g_pos_x) <= 1 && abs(new_g_pos_y - current_g_pos_y) <= 1 && grid[new_g_pos_x][new_g_pos_y] == 0)
				{	//if mouse is not clicked 
					piece_is_clicked = false;
					if (current_g_pos_x != new_g_pos_x || current_g_pos_y != new_g_pos_y)	// if you pick up the piece and put it back where it was
					{																		// then your turn isn't completed									
						is_goats_turn = false;
					}
					grid[current_g_pos_x][current_g_pos_y] = 0;								//updating game grid
					grid[new_g_pos_x][new_g_pos_y] = 1;
					current_g_pos_x = new_g_pos_x;											//updating to new posiion
					current_g_pos_y = new_g_pos_y;
				
					goats[goat_number].set_Position(new_g_pos_x, new_g_pos_y);			//updating piece's position and then piece's pixel position
					goats[goat_number].setPosition(Vector2f(x_grid[goats[goat_number].get_X()], y_grid[goats[goat_number].get_Y()]));
					is_current_recorded = false;
				}
				else
				{// if piece is moved to invalid square
					for (int i = 0; i < 20; i++)
					{
						goats[i].setPosition(Vector2f(x_grid[goats[i].get_X()], y_grid[goats[i].get_Y()]));
					}
					piece_is_clicked = false;
				}




			}
		}
		else
		{
			if (grid[x_mouse][y_mouse] == 2 && !piece_is_clicked)		//to see which tiger mouse is hovered over
			{
				for (int i = 0; i < 4; i++)
				{
					if (tigers[i].get_X() == x_mouse && tigers[i].get_Y() == y_mouse)
					{
						tiger_number = i;
						break;
					}
				}
				x_selected = tigers[tiger_number].getPosition().x;	//recording that piece's position
				y_selected = tigers[tiger_number].getPosition().y;
			}
			//if mouse is clicked on the piece
			if (x_m > x_selected && x_m<(x_selected + 2 * r) && y_m>y_selected && y_m < (y_selected + 2 * r) && Mouse::isButtonPressed(Mouse::Left))
			{
				piece_is_clicked = true;
				if (!is_current_recorded)						//recording piece's old position once before moving starts
				{
					current_t_pos_x = tigers[tiger_number].get_X();
					current_t_pos_y = tigers[tiger_number].get_Y();
					is_current_recorded = true;
				}
				new_t_pos_x = x_mouse;
				new_t_pos_y = y_mouse;

				tigers[tiger_number].setPosition(Vector2f(x_m - r, y_m - r));	//making the piece follow the mouse i.e. drag and drop
				x_selected = tigers[tiger_number].getPosition().x;
				y_selected = tigers[tiger_number].getPosition().y;
			}
			else if (abs(new_t_pos_x - current_t_pos_x) <= 1 && abs(new_t_pos_y - current_t_pos_y) <= 1 && grid[new_t_pos_x][new_t_pos_y] == 0)
			{	//if mouse is not clicked 
				piece_is_clicked = false;
				if (current_t_pos_x != new_t_pos_x || current_t_pos_y != new_t_pos_y)	// if you pick up the piece and put it back where it was
				{																		// then your turn isn't completed									
					is_goats_turn = true;
				}
				grid[current_t_pos_x][current_t_pos_y] = 0;								//updating game grid
				grid[new_t_pos_x][new_t_pos_y] = 2;
				current_t_pos_x = new_t_pos_x;											//updating to new posiion
				current_t_pos_y = new_t_pos_y;
				tigers[tiger_number].set_Position(new_t_pos_x, new_t_pos_y);			//updating piece's position and then piece's pixel position
				tigers[tiger_number].setPosition(Vector2f(x_grid[tigers[tiger_number].get_X()], y_grid[tigers[tiger_number].get_Y()]));
				is_current_recorded = false;
			}
			else if (abs(new_t_pos_x - current_t_pos_x) <= 2 && abs(new_t_pos_y - current_t_pos_y) <= 2 && grid[new_t_pos_x][new_t_pos_y] == 0)
			{//if baagh tries to eat a goat
				piece_is_clicked = false;
				is_current_recorded = false;
				if (new_t_pos_x != current_t_pos_x && new_t_pos_y != current_t_pos_y)
				{//diagonal case
					mid_tile_x = min(current_t_pos_x, new_t_pos_x) + 1;
					mid_tile_y = min(current_t_pos_y, new_t_pos_y) + 1;

				}
				else if (abs(new_t_pos_x - current_t_pos_x) == 2 && new_t_pos_y == current_t_pos_y)
				{//horizontal case
					mid_tile_x = min(current_t_pos_x, new_t_pos_x) + 1;
					mid_tile_y = current_t_pos_y;
				}
				else
				{//vertical case
					mid_tile_x = current_t_pos_x;
					mid_tile_y = min(current_t_pos_y, new_t_pos_y) + 1;
				}
				if (grid[mid_tile_x][mid_tile_y] == 1)
				{
					for (int i = 0; i < 20; i++)
					{
						if (goats[i].get_X() == mid_tile_x && goats[i].get_Y() == mid_tile_y)		//determining which goat to kill
						{
							bali_ka_bakhraa = i;
							break;
						}
					}
					goats[bali_ka_bakhraa].setstate(Dead);								//killing said goat
					goats[bali_ka_bakhraa].set_Position(-1, -1);						//getting rid of the body
					grid[mid_tile_x][mid_tile_y] = 0;									//updating grid			
					grid[current_t_pos_x][current_t_pos_y] = 0;
					grid[new_t_pos_x][new_t_pos_y] = 2;
					current_t_pos_x = new_t_pos_x;											//updating to new posiion
					current_t_pos_y = new_t_pos_y;
					tigers[tiger_number].set_Position(new_t_pos_x, new_t_pos_y);			//updating piece's position and then piece's pixel position
					tigers[tiger_number].setPosition(Vector2f(x_grid[tigers[tiger_number].get_X()], y_grid[tigers[tiger_number].get_Y()]));
					is_goats_turn = true;
				}
			}
			else
			{// if piece is moved to invalid square
				for (int i = 0; i < 4; i++)
				{
					tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
				}
				piece_is_clicked = false;
			}
		}
	}
}
