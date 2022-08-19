#pragma once
#include <iostream>
#include <cmath>
#include <algorithm>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "Animal.h"
#include "Bakhraa.h"
#include "Baagh.h"

using namespace std;
using namespace sf;

int tick_speed = 0;

class Path
{
public:
	string ImgPath = "C:/Users/Subham Shrestha/Documents/Visual Studio 2022/code/baghchal/img";
	string SoundPath = "C:/Users/Subham Shrestha/Documents/Visual Studio 2022/code/baghchal/img";
};
Path filepath;

class GameOver
{
private:
public:
	static bool has_goat_won;
	static bool game_is_over;
	static bool bagh_can_move;
	bool IsGameOver(int grid[][5], Bakhraa goats[], Baagh tigers[])
	{
		if (Bakhraa::getDeathToll() > 4)
		{
			has_goat_won = false;
			return true;
		}
		bagh_can_move = false;
		for (int i = 0; i < 4; i++) // i = baagh number
		{
			int tiger_going_to_x = tigers[i].get_X();
			int tiger_going_to_y = tigers[i].get_Y();
			for (int j = -2; j < 3; j++)
			{
				for (int k = -2; k < 3; k++)
				{
					if (tiger_going_to_x + j >= 0 && tiger_going_to_y + k >= 0 && tiger_going_to_x + j <= 4 && tiger_going_to_y + k <= 4)
					{
						if (j != 0 && k != 0 && k != j)
						{

							continue;
						}
						if (grid[tiger_going_to_x + j][tiger_going_to_y + k] == 0)
						{
							bagh_can_move = true;
							//////////////////////////
							/////////////////////////
							// break garna mile gara//
						}
					}
				}
			}
		}
		if (!bagh_can_move)
		{
			has_goat_won = true;
			return true;
		}
		else
			return false;
	}
};

// static  information about bakhraa
int Bakhraa::bakhraa_count = 0;
int Bakhraa::bakhraa_killed = 0;
int Bakhraa::goat_number = -1;

// static information about baagh
int Baagh::tiger_number = 0;

// static information about turns and goats
bool GameOver::game_is_over = false;
bool GameOver::bagh_can_move = false;
bool GameOver::has_goat_won = true;

// information about piece moving
bool is_goats_turn = true;
bool is_current_recorded = false;
bool piece_is_clicked = false;
bool mouse_clicked_once = false;
int x_selected = 0, y_selected = 0;
// extra information for tigers
int current_t_pos_x = 0, current_t_pos_y = 0;
int new_t_pos_x = 0, new_t_pos_y = 0;
int bali_ka_bakhraa = 0;
int hunter_tiger = 0;
int mid_tile_x = 0, mid_tile_y = 0;
// extra information for bakhraa
int x_gselected = 0, y_gselected = 0;
int current_g_pos_x = 0, current_g_pos_y = 0;
int new_g_pos_x = -1, new_g_pos_y = -1;
bool is_multiplayer = true;

///////////// AI PART FUNCTIONS /////////////
// int evaluate(int grid[][5], Bakhraa goats[], Baagh tigers[])
// {
// 	GameOver gameOverTry;
// 	gameOverTry.IsGameOver(grid, goats, tigers);
// 	if (has_goat_won == true)
// 	{
// 		return -10;
// 	}
// 	else if (has_goat_won == false)
// 	{
// 		return +10;
// 	}
// 	else
// 	{
// 		return 0;
// 	}
// }

// void minimax(int grid[][5], Bakhraa goats[], Baagh tigers[] /*, int depth, bool isMax*/)
// {
// int score = evaluate(grid, goats, tigers);
// if (score == 10)
// {
// 	return score;
// }
// if (score == -10)
// {
// 	return score;
// }
// if (bakhraa_count > 19)
// {
// 	return 0;
// }

// if (isMax)
// {
// 	int best = -1000;
// 	for (int i = 0; i < 4; i++) // i means bagh number
// 	{
// 		int tiger_i_position_x = tigers[i].get_X();
// 		int tiger_i_position_y = tigers[i].get_Y();
// 		for (int j = -2; j < 3; j++)
// 		{
// 			for (int k = -2; k < 3; k++)
// 			{
// 				if (tiger_i_position_x + j >= 0 and tiger_i_position_y + k >= 0 and tiger_i_position_x + j <= 4 and tiger_i_position_y + k <= 4)
// 				{
// 					if (j != 0 and k != 0 and k != j)
// 					{
// 						continue;
// 					}
// 					if ((abs(j) == 2 or abs(k) == 2) and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0 and grid[tiger_i_position_x + j / 2][tiger_i_position_y + k / 2] == 1) // Tiger moves to eat goat
// 					{
// 						new_t_pos_x = tiger_i_position_x + j;
// 						new_t_pos_y = tiger_i_position_y + k;
// 						if (j == k or j == -k)
// 						{ //////Diagonal//////
// 							mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
// 							mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

// 							for (int goat_i = 0; goat_i < 20; goat_i++)
// 							{
// 								if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
// 								{
// 									bali_ka_bakhraa = goat_i;
// 									break;
// 								}
// 							}
// 							goats[bali_ka_bakhraa].setstate(Dead);
// 							bakhraa_killed++;
// 							goats[bali_ka_bakhraa].set_Position(-1, -1);
// 							grid[mid_tile_x][mid_tile_y] = 0;

// 							grid[tiger_i_position_x][tiger_i_position_y] = 0;

// 							grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
// 							tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
// 							is_goats_turn = true;
// 							// 	//tigers[i].setPosition(Vector2f())
// 							// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
// 							// }
// 						}

// 						else if (abs(new_t_pos_x - tiger_i_position_x) == 2 and new_t_pos_y == tiger_i_position_y)
// 						{ /// Horizontal///
// 							mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
// 							mid_tile_y = tiger_i_position_y;

// 							for (int goat_i = 0; goat_i < 20; goat_i++)
// 							{
// 								if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
// 								{
// 									bali_ka_bakhraa = goat_i;
// 									break;
// 								}
// 							}
// 							goats[bali_ka_bakhraa].setstate(Dead);
// 							bakhraa_killed++;
// 							goats[bali_ka_bakhraa].set_Position(-1, -1);
// 							grid[mid_tile_x][mid_tile_y] = 0;

// 							grid[tiger_i_position_x][tiger_i_position_y] = 0;

// 							grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
// 							tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
// 							is_goats_turn = true;
// 							// 	//tigers[i].setPosition(Vector2f())
// 							// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
// 						}

// 						else
// 						{ // Vertical //
// 							mid_tile_x = tiger_i_position_x;
// 							mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

// 							for (int goat_i = 0; goat_i < 20; goat_i++)
// 							{
// 								if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
// 								{
// 									bali_ka_bakhraa = goat_i;
// 									break;
// 								}
// 							}
// 							goats[bali_ka_bakhraa].setstate(Dead);
// 							bakhraa_killed++;
// 							goats[bali_ka_bakhraa].set_Position(-1, -1);
// 							grid[mid_tile_x][mid_tile_y] = 0;

// 							grid[tiger_i_position_x][tiger_i_position_y] = 0;

// 							grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
// 							tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
// 							is_goats_turn = true;
// 							// 	//tigers[i].setPosition(Vector2f())
// 							// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
// 						}
// 					}

// 					else if (abs(j) <= 2 and abs(k) <= 2 and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0)
// 					{
// 						grid[tiger_i_position_x][tiger_i_position_y] = 0;
// 						grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
// 						tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
// 						is_goats_turn = true;
// 					}
// 				}
// 			}
// 		}
// 	}
// 	// return best;
// }

// else // if Min's turn
// {
// 	int best = 1000;
// 	if (bakhraa_count < 20) // To check phase 1 or 2 of game
// 	{
// 		for (int j = 0; j < 4; j++)
// 		{
// 			for (int k = 0; k < 4; k++)
// 			{
// 				if ((j == 0 or k == 0) and grid[j][k] == 0)
// 				{
// 					grid[j][k] = 1;
// 					goats[bakhraa_count].set_Position(j, k);
// 					goats[bakhraa_count].setstate(alive);
// 					// is_goats_turn = false;
// 					bakhraa_count++;

// 					best = min(best, minimax(grid, goats, tigers, depth, !isMax));
// 				}
// 				else if (grid[j][k] = 0)
// 				{
// 					grid[j][k] = 1;
// 					goats[bakhraa_count].set_Position(j, k);
// 					goats[bakhraa_count].setstate(alive);
// 					// is_goats_turn = false;
// 					bakhraa_count++;

// 					best = min(best, minimax(grid, goats, tigers, depth, !isMax));
// 				}
// 			}
// 		}
// 		// if (grid[x_mouse][y_mouse] == 0 && Mouse::isButtonPressed(Mouse::Left) && bakhraa_count < 20 && x_m > 400 && x_m < 800 && y_m > 200 && y_m < 600)

// 		//{
// 		// grid[x_mouse][y_mouse] = 1;
// 		// goats[bakhraa_count].set_Position(x_mouse, y_mouse);
// 		// goats[bakhraa_count].setstate(alive);
// 		// goats[bakhraa_count].setPosition(Vector2f(x_grid[x_mouse], y_grid[y_mouse]));
// 		// is_goats_turn = false;
// 		// bakhraa_count++;
// 		//}
// 	}
// }
// int evaluate();

void update_events(RenderWindow& window, Bakhraa goats[], Baagh tigers[], int* x_grid, int* y_grid, int grid[][5]);

int main()
{
	int screen_height = 800, screen_width = 1200;
	RenderWindow window(VideoMode(screen_width, screen_height), "baghchal", Style::Default);
	window.setFramerateLimit(60);
	int grid[5][5]; // Initializing grid(map) of Board
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			grid[i][j] = 0;
		}
	}
	int board_height = 400, board_width = 400;
	int board_origin_x = 400, board_origin_y = 200;
	int x_grid[5], y_grid[5];
	for (int i = 0; i < 5; i++)
	{ // Initializing pixel grid of board
		x_grid[i] = board_origin_x + i * board_width / 5;
		y_grid[i] = board_origin_y + i * board_height / 5;
	}

	// to load image
	Sprite background, gturn, tturn, killed[6], ctiger, cgoat,board;
	Texture backgroundtex, gturnt, tturnt, killeds[6], ctigert, cgoatt,boardt;
	backgroundtex.loadFromFile(filepath.ImgPath + "/background.jpg");
	background.setTexture(backgroundtex);
	background.setScale(1.2f, 1.2f);
	// turn display
	gturnt.loadFromFile(filepath.ImgPath + "/goaturn.png");
	gturn.setTexture(gturnt);
	gturn.setScale(0.6f, 0.6f);
	gturn.setPosition(450.f, 5.f);

	tturnt.loadFromFile(filepath.ImgPath + "/tigerturn.png");
	tturn.setTexture(tturnt);
	tturn.setScale(0.6f, 0.6f);
	tturn.setPosition(450.f, 5.f);
	// killed display
	killeds[1].loadFromFile(filepath.ImgPath + "/one.png");
	killeds[2].loadFromFile(filepath.ImgPath + "/two.png");
	killeds[3].loadFromFile(filepath.ImgPath + "/three.png");
	killeds[4].loadFromFile(filepath.ImgPath + "/four.png");
	killeds[0].loadFromFile(filepath.ImgPath + "/zero.png");

	for (int i = 0; i < 6; i++)
	{
		killed[i].setTexture(killeds[i]);
		killed[i].setScale(0.5f, 0.5f);
		killed[i].setPosition(450.f, 600.f);
	}


	boardt.loadFromFile(filepath.ImgPath + "/board.png");
	board.setTexture(boardt);
	board.setScale(1.78f, 1.8f);
	board.setPosition(398.f, 200.f);
	// piece display

	Texture igoat, itiger;
	igoat.loadFromFile(filepath.ImgPath + "/goat.png");
	itiger.loadFromFile(filepath.ImgPath + "/tiger.png");

	Sprite goatw, tigerw;
	Texture goatwin, tigerwin;
	goatwin.loadFromFile(filepath.ImgPath + "/gameoverBakhraa.png");
	tigerwin.loadFromFile(filepath.ImgPath + "/gameoverBagh.png");
	tigerw.setTexture(tigerwin);
	goatw.setTexture(goatwin);
	tigerw.setScale(0.7f, 0.7f);
	goatw.setScale(0.7f, 0.7f);

	// other display
	ctigert.loadFromFile(filepath.ImgPath + "/ctiger.png");
	ctiger.setTexture(ctigert);
	ctiger.setScale(0.6f, 0.6f);
	ctiger.setPosition(40.f, 200.f);

	cgoatt.loadFromFile(filepath.ImgPath + "/cgoat.png");
	cgoat.setTexture(cgoatt);
	cgoat.setScale(0.6f, 0.6f);
	cgoat.setPosition(820.f, 220.f);

	// sound

	sf::SoundBuffer stiger;
	sf::Music bsound;

	stiger.loadFromFile(filepath.SoundPath + "/tiger_roar.wav");
	bsound.openFromFile(filepath.SoundPath + "/bsound.ogg");
	sf::Sound soundt;

	soundt.setBuffer(stiger);

	bsound.play();

	VertexArray Borders(LineStrip, 5); // Drawing Borders
	Borders[0].position = Vector2f(board_origin_x, board_origin_y);
	Borders[1].position = Vector2f(board_origin_x + board_width, board_origin_y);
	Borders[2].position = Vector2f(board_origin_x + board_width, board_origin_y + board_height);
	Borders[3].position = Vector2f(board_origin_x, board_origin_y + board_height);
	Borders[4].position = Vector2f(board_origin_x, board_origin_y);

	VertexArray V_lines(LineStrip, 8); // Drawing Vertical lines
	VertexArray H_lines(LineStrip, 8); // Drawing Horizontal lines

	for (int i = 1, j = 0; i < 5; i++, j++)
	{
		if (i % 2 == 1)
		{
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + board_height / 5);
		}
		else
		{
			V_lines[j].position = Vector2f(x_grid[i], y_grid[4] + board_height / 5);
			j++;
			V_lines[j].position = Vector2f(x_grid[i], y_grid[0]);
		}
	}

	for (int i = 1, j = 0; i < 5; i++, j++)
	{
		if (i % 2 == 1)
		{
			H_lines[j].position = Vector2f(x_grid[0], y_grid[i]);
			j++;
			H_lines[j].position = Vector2f(x_grid[4] + board_width / 5, y_grid[i]);
		}
		else
		{
			H_lines[j].position = Vector2f(x_grid[4] + board_width / 5, y_grid[i]);
			j++;
			H_lines[j].position = Vector2f(x_grid[0], y_grid[i]);
		}
	}
	Bakhraa goats[20]; // Initializing goats
	for (int i = 0; i < 20; i++)
	{
		goats[i].setRadius(40.f);
		goats[i].set_Position(-1, -1);
		// goats[i].setFillColor(Color::White);
		goats[i].setTexture(&igoat); // image

		goats[i].setstate(Dead);
	}
	Baagh tigers[4]; // Iinitializing Tigers
	tigers[0].set_Position(0, 0);
	tigers[1].set_Position(0, 4);
	tigers[2].set_Position(4, 4);
	tigers[3].set_Position(4, 0);

	for (int i = 0; i < 4; i++)
	{
		tigers[i].setRadius(40.f);
		tigers[i].setTexture(&itiger); // image
		// tigers[i].setFillColor(Color::Red);
		tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
		grid[tigers[i].get_X()][tigers[i].get_Y()] = 2;
	}

	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{

			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
				window.close();
		}
		if (tick_speed == 2 || is_multiplayer)
		{

			tick_speed = 0;
			update_events(window, goats, tigers, x_grid, y_grid, grid);
		}
		else
		{
			tick_speed++;
		}

		window.clear(Color::Black);

		if (!GameOver::game_is_over)
		{
			// SHOWING GAME UI unless game is over (work needs to be done)
			/////
			//////
			//////

			window.draw(background);
			window.draw(V_lines);
			window.draw(H_lines);
			window.draw(Borders);
			window.draw(board);
			window.draw(ctiger);
			window.draw(cgoat);

			if (is_goats_turn)
			{
				window.draw(gturn);
			}
			else
			{
				window.draw(tturn);
				soundt.play();
			}
			int t = Bakhraa::getDeathToll();
			window.draw(killed[t]);

			for (int i = 0; i < 20; i++) // draw goats on board
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
		}

		else
		{

			if (GameOver::has_goat_won)
			{
				window.draw(goatw);
			}
			else
			{
				window.draw(tigerw);
			}
		}

		window.display();
	}
}

void update_events(RenderWindow& window, Bakhraa goats[], Baagh tigers[], int* x_grid, int* y_grid, int grid[][5])

{ // mouse positon to record in pixels
	int x_m = Mouse::getPosition(window).x, y_m = Mouse::getPosition(window).y;
	int x_mouse = 0, y_mouse = 0; // mouse to record position in grid placement
	int r = 40;

	if (x_m > 400 && x_m < 800 && y_m > 200 && y_m < 600)
	{ // changing pixel to grid state
		x_mouse = (x_m - 400) / 80;
		y_mouse = (y_m - 200) / 80;
	}

	// bool IsGameOver()
	// {
	// 	if (bakhraa_killed > 4)
	// 	{
	// 		has_goat_won = false;
	// 		return true;
	// 	}
	// bagh_can_move = false;
	// for (int i = 0; i < 4; i++) //i = baagh number
	// {
	// 	int tiger_going_to_x = tigers[i].get_X();
	// 	int tiger_going_to_y = tigers[i].get_Y();
	// 	for (int j = -2; j < 3; j++)
	// 	{
	// 		for (int k = -2; k < 3; k++)
	// 		{
	// 			if (tiger_going_to_x + j >= 0 && tiger_going_to_y + k >= 0 && tiger_going_to_x + j <= 4 && tiger_going_to_y + k <= 4)
	// 			{
	// 				if (j != 0 && k != 0 && k != j)
	// 				{

	// 					continue;
	// 				}
	// 				if (grid[tiger_going_to_x + j][tiger_going_to_y + k] == 0)
	// 				{
	// 					bagh_can_move = true;
	// 					//////////////////////////
	// 					/////////////////////////
	// 					//break garna mile gara//
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// if (!bagh_can_move)
	// {
	// 	has_goat_won = true;
	// 	return true;
	// }

	// }
	GameOver gameOver;
	GameOver::game_is_over = gameOver.IsGameOver(grid, goats, tigers);

	// if (bakhraa_killed > 4)
	// {
	// 	game_is_over = true;
	// 	has_goat_won = false;
	// 	//DISPLAY BAGH WON
	// }
	// bagh_can_move = false;
	// for (int i = 0; i < 4; i++) //i = baagh number
	// {
	// 	int tiger_going_to_x = tigers[i].get_X();
	// 	int tiger_going_to_y = tigers[i].get_Y();
	// 	for (int j = -2; j < 3; j++)
	// 	{
	// 		for (int k = -2; k < 3; k++)
	// 		{
	// 			if (tiger_going_to_x + j >= 0 && tiger_going_to_y + k >= 0 && tiger_going_to_x + j <= 4 && tiger_going_to_y + k <= 4)
	// 			{
	// 				if (j != 0 && k != 0 && k != j)
	// 				{

	// 					continue;
	// 				}
	// 				if (grid[tiger_going_to_x + j][tiger_going_to_y + k] == 0)
	// 				{
	// 					bagh_can_move = true;
	// 					//////////////////////////
	// 					/////////////////////////
	// 					//break garna mile gara//
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	// if (!bagh_can_move)
	// {
	// 	has_goat_won = true;
	// 	game_is_over = true;

	// }

	if (!GameOver::game_is_over)
	{
		if (is_multiplayer)
		{
			if (is_goats_turn)
			{ //****nedd to logic bool is_goat_placed logic doesnt seem to work

				if (Bakhraa::getCount() < 20) // To check phase 1 or 2 of game
				{
					if (grid[x_mouse][y_mouse] == 0 && Mouse::isButtonPressed(Mouse::Left) && Bakhraa::getCount() < 20 && x_m > 400 && x_m < 800 && y_m > 200 && y_m < 600)

					{

						grid[x_mouse][y_mouse] = 1;
						goats[Bakhraa::getCount()].set_Position(x_mouse, y_mouse);
						goats[Bakhraa::getCount()].setstate(alive);
						goats[Bakhraa::getCount()].setPosition(Vector2f(x_grid[x_mouse], y_grid[y_mouse]));
						is_goats_turn = false;
						Bakhraa::increaseCount();
					}
				} // TO MOVE GOAT
				else
				{
					if (grid[x_mouse][y_mouse] == 1 && !piece_is_clicked) // to see which goat mouse is hovered over
					{
						for (int i = 0; i < 20; i++)
						{
							if (goats[i].get_X() == x_mouse && goats[i].get_Y() == y_mouse)
							{
								Bakhraa::goat_number = i;
								break;
							}
						}
						x_selected = goats[Bakhraa::goat_number].getPosition().x; // recording that piece's position
						y_selected = goats[Bakhraa::goat_number].getPosition().y;
					}
					// if mouse is clicked on the piece
					if (x_m > x_selected && x_m < (x_selected + 2 * r) && y_m > y_selected && y_m < (y_selected + 2 * r) && Mouse::isButtonPressed(Mouse::Left))
					{
						mouse_clicked_once = true; // to fix ghost goat bug
						piece_is_clicked = true;
						if (!is_current_recorded) // recording piece's old position once before moving starts
						{
							current_g_pos_x = goats[Bakhraa::goat_number].get_X();
							current_g_pos_y = goats[Bakhraa::goat_number].get_Y();
							is_current_recorded = true;
						}
						new_g_pos_x = x_mouse;
						new_g_pos_y = y_mouse;

						goats[Bakhraa::goat_number].setPosition(Vector2f(x_m - r, y_m - r)); // making the piece follow the mouse i.e. drag and drop
						x_selected = goats[Bakhraa::goat_number].getPosition().x;
						y_selected = goats[Bakhraa::goat_number].getPosition().y;
					}
					else if (abs(new_g_pos_x - current_g_pos_x) <= 1 && abs(new_g_pos_y - current_g_pos_y) <= 1 && grid[new_g_pos_x][new_g_pos_y] == 0 && mouse_clicked_once && !(((current_g_pos_x + current_g_pos_y) % 2 == 1) && abs(new_g_pos_x - current_g_pos_x) == 1 && abs(new_g_pos_y - current_g_pos_y) == 1))
					{ // if mouse is not clicked
						piece_is_clicked = false;
						if (current_g_pos_x != new_g_pos_x || current_g_pos_y != new_g_pos_y) // if you pick up the piece and put it back where it was
						{																	  // then your turn isn't completed
							is_goats_turn = false;
						}
						grid[current_g_pos_x][current_g_pos_y] = 0; // updating game grid
						grid[new_g_pos_x][new_g_pos_y] = 1;
						goats[Bakhraa::goat_number].set_Position(new_g_pos_x, new_g_pos_y); // updating piece's position and then piece's pixel position

						current_g_pos_x = new_g_pos_x; // updating to new posiion
						current_g_pos_y = new_g_pos_y;
						goats[Bakhraa::goat_number].setPosition(Vector2f(x_grid[new_g_pos_x], y_grid[new_g_pos_y]));
						is_current_recorded = false;
					}
					else
					{ // if piece is moved to invalid square
						for (int i = 0; i < 20; i++)
						{

							if (goats[i].getstate())
							{
								goats[i].setPosition(Vector2f(x_grid[goats[i].get_X()], y_grid[goats[i].get_Y()]));
							}
							else
							{
								goats[i].setPosition(Vector2f(0, 0));
							}
						}
						piece_is_clicked = false;
						is_current_recorded = false;
					}
				}
			}
			else
			{
				if (grid[x_mouse][y_mouse] == 2 && !piece_is_clicked) // to see which tiger mouse is hovered over
				{
					for (int i = 0; i < 4; i++)
					{
						if (tigers[i].get_X() == x_mouse && tigers[i].get_Y() == y_mouse)
						{
							Baagh::tiger_number = i;
							break;
						}
					}
					x_selected = tigers[Baagh::tiger_number].getPosition().x; // recording that piece's position
					y_selected = tigers[Baagh::tiger_number].getPosition().y;
				}
				// if mouse is clicked on the piece
				if (x_m > x_selected && x_m < (x_selected + 2 * r) && y_m > y_selected && y_m < (y_selected + 2 * r) && Mouse::isButtonPressed(Mouse::Left))
				{
					piece_is_clicked = true;
					if (!is_current_recorded) // recording piece's old position once before moving starts
					{
						current_t_pos_x = tigers[Baagh::tiger_number].get_X();
						current_t_pos_y = tigers[Baagh::tiger_number].get_Y();
						is_current_recorded = true;
					}
					new_t_pos_x = x_mouse;
					new_t_pos_y = y_mouse;

					tigers[Baagh::tiger_number].setPosition(Vector2f(x_m - r, y_m - r)); // making the piece follow the mouse i.e. drag and drop
					x_selected = tigers[Baagh::tiger_number].getPosition().x;
					y_selected = tigers[Baagh::tiger_number].getPosition().y;
				}
				else if (abs(new_t_pos_x - current_t_pos_x) <= 1 && abs(new_t_pos_y - current_t_pos_y) <= 1 && grid[new_t_pos_x][new_t_pos_y] == 0 && !(((current_t_pos_x + current_t_pos_y) % 2 == 1) && abs(new_t_pos_x - current_t_pos_x) == 1 && abs(new_t_pos_y - current_t_pos_y) == 1))
				{ // if mouse is not clicked
					piece_is_clicked = false;
					if (current_t_pos_x != new_t_pos_x || current_t_pos_y != new_t_pos_y) // if you pick up the piece and put it back where it was
					{																	  // then your turn isn't completed
						is_goats_turn = true;
						mouse_clicked_once = false; // to fix ghost goat bug
					}
					grid[current_t_pos_x][current_t_pos_y] = 0; // updating game grid
					grid[new_t_pos_x][new_t_pos_y] = 2;
					current_t_pos_x = new_t_pos_x; // updating to new posiion
					current_t_pos_y = new_t_pos_y;
					tigers[Baagh::tiger_number].set_Position(new_t_pos_x, new_t_pos_y); // updating piece's position and then piece's pixel position
					tigers[Baagh::tiger_number].setPosition(Vector2f(x_grid[tigers[Baagh::tiger_number].get_X()], y_grid[tigers[Baagh::tiger_number].get_Y()]));
					is_current_recorded = false;
				}
				else if (((abs(new_t_pos_x - current_t_pos_x) == 2 && abs(new_t_pos_y - current_t_pos_y) == 0) || (abs(new_t_pos_x - current_t_pos_x) == 0 && abs(new_t_pos_y - current_t_pos_y) == 2) || (abs(new_t_pos_x - current_t_pos_x) == 2 && abs(new_t_pos_y - current_t_pos_y) == 2)) && grid[new_t_pos_x][new_t_pos_y] == 0 && !(((current_t_pos_x + current_t_pos_y) % 2 == 1) && abs(new_t_pos_x - current_t_pos_x) == 2 && abs(new_t_pos_y - current_t_pos_y) == 2))
				{ // if baagh tries to eat a goat
					piece_is_clicked = false;
					is_current_recorded = false;
					if (new_t_pos_x != current_t_pos_x && new_t_pos_y != current_t_pos_y)
					{ // diagonal case
						mid_tile_x = min(current_t_pos_x, new_t_pos_x) + 1;
						mid_tile_y = min(current_t_pos_y, new_t_pos_y) + 1;
					}
					else if (abs(new_t_pos_x - current_t_pos_x) == 2 && new_t_pos_y == current_t_pos_y)
					{ // horizontal case
						mid_tile_x = min(current_t_pos_x, new_t_pos_x) + 1;
						mid_tile_y = current_t_pos_y;
					}
					else
					{ // vertical case
						mid_tile_x = current_t_pos_x;
						mid_tile_y = min(current_t_pos_y, new_t_pos_y) + 1;
					}
					if (grid[mid_tile_x][mid_tile_y] == 1) // bakhraa killed

					{
						for (int i = 0; i < 20; i++)
						{
							if (goats[i].get_X() == mid_tile_x && goats[i].get_Y() == mid_tile_y) // determining which goat to kill
							{
								bali_ka_bakhraa = i;
								break;
							}
						}

						goats[bali_ka_bakhraa].setstate(Dead);
						Bakhraa::increaseDeathToll();				 // killing said goat
						goats[bali_ka_bakhraa].set_Position(-1, -1); // getting rid of the body
						grid[mid_tile_x][mid_tile_y] = 0;			 // updating grid

						grid[current_t_pos_x][current_t_pos_y] = 0;
						grid[new_t_pos_x][new_t_pos_y] = 2;
						current_t_pos_x = new_t_pos_x; // updating to new posiion
						current_t_pos_y = new_t_pos_y;

						tigers[Baagh::tiger_number].set_Position(new_t_pos_x, new_t_pos_y); // updating piece's position and then piece's pixel position
						tigers[Baagh::tiger_number].setPosition(Vector2f(x_grid[tigers[Baagh::tiger_number].get_X()], y_grid[tigers[Baagh::tiger_number].get_Y()]));
						is_goats_turn = true;
						mouse_clicked_once = false; // to fix ghost goat bug
						piece_is_clicked = false;
					}
				}
				else
				{ // if piece is moved to invalid square
					for (int i = 0; i < 4; i++)
					{
						tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
					}
					piece_is_clicked = false;

					is_current_recorded = false;
				}
			}
		}

		// //////////////////// AI PART ///////////////////////
		// /////////////////// MINIMAX ALGORITHM /////////////
		else if (!is_multiplayer)
		{
			if (is_goats_turn)
			{
				if (Bakhraa::getCount() < 20) // To check phase 1 or 2 of game
				{
					if (grid[x_mouse][y_mouse] == 0 && Mouse::isButtonPressed(Mouse::Left) && Bakhraa::getCount() < 20 && x_m > 400 && x_m < 800 && y_m > 200 && y_m < 600)

					{

						grid[x_mouse][y_mouse] = 1;
						goats[Bakhraa::getCount()].set_Position(x_mouse, y_mouse);
						goats[Bakhraa::getCount()].setstate(alive);
						goats[Bakhraa::getCount()].setPosition(Vector2f(x_grid[x_mouse], y_grid[y_mouse]));
						is_goats_turn = false;
						Bakhraa::increaseCount();
					}
				} // TO MOVE GOAT
				else
				{
					if (grid[x_mouse][y_mouse] == 1 && !piece_is_clicked) // to see which goat mouse is hovered over
					{
						for (int i = 0; i < 20; i++)
						{
							if (goats[i].get_X() == x_mouse && goats[i].get_Y() == y_mouse)
							{
								Bakhraa::goat_number = i;
								break;
							}
						}
						x_selected = goats[Bakhraa::goat_number].getPosition().x; // recording that piece's position
						y_selected = goats[Bakhraa::goat_number].getPosition().y;
					}
					// if mouse is clicked on the piece
					if (x_m > x_selected && x_m < (x_selected + 2 * r) && y_m > y_selected && y_m < (y_selected + 2 * r) && Mouse::isButtonPressed(Mouse::Left))
					{
						mouse_clicked_once = true; // to fix ghost goat bug
						piece_is_clicked = true;
						if (!is_current_recorded) // recording piece's old position once before moving starts
						{
							current_g_pos_x = goats[Bakhraa::goat_number].get_X();
							current_g_pos_y = goats[Bakhraa::goat_number].get_Y();
							is_current_recorded = true;
						}
						new_g_pos_x = x_mouse;
						new_g_pos_y = y_mouse;

						goats[Bakhraa::goat_number].setPosition(Vector2f(x_m - r, y_m - r)); // making the piece follow the mouse i.e. drag and drop
						x_selected = goats[Bakhraa::goat_number].getPosition().x;
						y_selected = goats[Bakhraa::goat_number].getPosition().y;
					}
					else if (abs(new_g_pos_x - current_g_pos_x) <= 1 && abs(new_g_pos_y - current_g_pos_y) <= 1 && grid[new_g_pos_x][new_g_pos_y] == 0 && mouse_clicked_once && !(((current_g_pos_x + current_g_pos_y) % 2 == 1) && abs(new_g_pos_x - current_g_pos_x) == 1 && abs(new_g_pos_y - current_g_pos_y) == 1))
					{ // if mouse is not clicked
						piece_is_clicked = false;
						if (current_g_pos_x != new_g_pos_x || current_g_pos_y != new_g_pos_y) // if you pick up the piece and put it back where it was
						{																	  // then your turn isn't completed
							is_goats_turn = false;
						}
						grid[current_g_pos_x][current_g_pos_y] = 0; // updating game grid
						grid[new_g_pos_x][new_g_pos_y] = 1;
						goats[Bakhraa::goat_number].set_Position(new_g_pos_x, new_g_pos_y); // updating piece's position and then piece's pixel position

						current_g_pos_x = new_g_pos_x; // updating to new posiion
						current_g_pos_y = new_g_pos_y;
						goats[Bakhraa::goat_number].setPosition(Vector2f(x_grid[new_g_pos_x], y_grid[new_g_pos_y]));
						is_current_recorded = false;
					}
					else
					{ // if piece is moved to invalid square
						for (int i = 0; i < 20; i++)
						{

							if (goats[i].getstate())
							{
								goats[i].setPosition(Vector2f(x_grid[goats[i].get_X()], y_grid[goats[i].get_Y()]));
							}
							else
							{
								goats[i].setPosition(Vector2f(0, 0));
							}
						}
						piece_is_clicked = false;
						is_current_recorded = false;
					}
				}
			}
			else if (!is_goats_turn)
			{
				for (int i = 0; i < 5; i++)
				{
					for (int j = 0; j < 5; j++)
					{
						if (!is_goats_turn and ((i == 0 and j == 0) or (i == 0 and j == 4) or (i == 4 and j == 0) or (i == 4 and j == 4)))
						{ // skipped for corners
							continue;
						}
						else if (!is_goats_turn and grid[i][j] == 1)
						{
							if (i >= 1 and i <= 3 and j >= 1 and j <= 3 and grid[i - 1][j - 1] == 2 and grid[i + 1][j + 1] == 0 and ((i + j) % 2 == 0)) // top left bagh, bottom right empty
							{
								for (int goat_i = 0; goat_i < 20; goat_i++)
								{
									if (goats[goat_i].get_X() == i and goats[goat_i].get_Y() == j)
									{
										bali_ka_bakhraa = goat_i;
										break;
									}
								}
								for (int tiger_i = 0; tiger_i < 4; tiger_i++)
								{
									if (tigers[tiger_i].get_X() == (i - 1) and tigers[tiger_i].get_Y() == (j - 1))
									{
										hunter_tiger = tiger_i;
										break;
									}
								}
								goats[bali_ka_bakhraa].setstate(Dead);
								Bakhraa::increaseDeathToll();
								goats[bali_ka_bakhraa].set_Position(-1, -1);
								grid[i][j] = 0;

								grid[i - 1][j - 1] = 0;
								grid[i + 1][j + 1] = 2;
								tigers[hunter_tiger].set_Position(i + 1, j + 1);
								tigers[hunter_tiger].setPosition(Vector2f(x_grid[tigers[hunter_tiger].get_X()], y_grid[tigers[hunter_tiger].get_Y()]));
								is_goats_turn = true;
								continue;
							}
							else if (i >= 1 and i <= 3 and j >= 0 and j <= 4 and grid[i - 1][j] == 2 and grid[i + 1][j] == 0) //tried for top bagh, bottom empty, don't know what has become
							{
								for (int goat_i = 0; goat_i < 20; goat_i++)
								{
									if (goats[goat_i].get_X() == i and goats[goat_i].get_Y() == j)
									{
										bali_ka_bakhraa = goat_i;
										break;
									}
								}
								for (int tiger_i = 0; tiger_i < 4; tiger_i++)
								{
									if (tigers[tiger_i].get_X() == (i - 1) and tigers[tiger_i].get_Y() == (j))
									{
										hunter_tiger = tiger_i;
										break;
									}
								}
								goats[bali_ka_bakhraa].setstate(Dead);
								Bakhraa::increaseDeathToll();
								goats[bali_ka_bakhraa].set_Position(-1, -1);
								grid[i][j] = 0;

								grid[i - 1][j] = 0;
								grid[i + 1][j] = 2;
								tigers[hunter_tiger].set_Position(i + 1, j);
								tigers[hunter_tiger].setPosition(Vector2f(x_grid[tigers[hunter_tiger].get_X()], y_grid[tigers[hunter_tiger].get_Y()]));
								is_goats_turn = true;
								continue;
							}
							if (((i - 1) >= 0 and (j + 1) <= 4 and (i + 1) <= 4 and (j - 1) >= 0) and grid[i - 1][j + 1] == 2 and grid[i + 1][j - 1] == 0 and ((i + j) % 2 == 0)) //tried for top right bagh, bottom left empty, don't know what has become
							{
								for (int goat_i = 0; goat_i < 20; goat_i++)
								{
									if (goats[goat_i].get_X() == i and goats[goat_i].get_Y() == j)
									{
										bali_ka_bakhraa = goat_i;
										break;
									}
								}
								for (int tiger_i = 0; tiger_i < 4; tiger_i++)
								{
									if (tigers[tiger_i].get_X() == (i - 1) and tigers[tiger_i].get_Y() == (j + 1))
									{
										hunter_tiger = tiger_i;
										break;
									}
								}
								goats[bali_ka_bakhraa].setstate(Dead);
								Bakhraa::increaseDeathToll();
								goats[bali_ka_bakhraa].set_Position(-1, -1);
								grid[i][j] = 0;

								grid[i - 1][j + 1] = 0;
								grid[i + 1][j - 1] = 2;
								tigers[hunter_tiger].set_Position(i + 1, j - 1);
								tigers[hunter_tiger].setPosition(Vector2f(x_grid[tigers[hunter_tiger].get_X()], y_grid[tigers[hunter_tiger].get_Y()]));
								is_goats_turn = true;
								continue;
							}
							if (((i) >= 0 and (j + 1) <= 4 and (i) <= 4 and (j - 1) >= 0) and grid[i][j + 1] == 2 and grid[i][j - 1] == 0) //tried for right bagh, left empty, don't know what has become xD
							{
								for (int goat_i = 0; goat_i < 20; goat_i++)
								{
									if (goats[goat_i].get_X() == i and goats[goat_i].get_Y() == j)
									{
										bali_ka_bakhraa = goat_i;
										break;
									}
								}
								for (int tiger_i = 0; tiger_i < 4; tiger_i++)
								{
									if (tigers[tiger_i].get_X() == (i) and tigers[tiger_i].get_Y() == (j + 1))
									{
										hunter_tiger = tiger_i;
										break;
									}
								}
								goats[bali_ka_bakhraa].setstate(Dead);
								Bakhraa::increaseDeathToll();
								goats[bali_ka_bakhraa].set_Position(-1, -1);
								grid[i][j] = 0;

								grid[i][j + 1] = 0;
								grid[i][j - 1] = 2;
								tigers[hunter_tiger].set_Position(i, j - 1);
								tigers[hunter_tiger].setPosition(Vector2f(x_grid[tigers[hunter_tiger].get_X()], y_grid[tigers[hunter_tiger].get_Y()]));
								is_goats_turn = true;
								continue;
							}
							if (grid[i][j - 1] == 2 and grid[i][j + 1] == 0 and i >= 0 and i <= 4 and j >= 1 and j <= 3) //tried for left bagh, right empty, don't know what has become xD
							{
								for (int goat_i = 0; goat_i < 20; goat_i++)
								{
									if (goats[goat_i].get_X() == i and goats[goat_i].get_Y() == j)
									{
										bali_ka_bakhraa = goat_i;
										break;
									}
								}
								for (int tiger_i = 0; tiger_i < 4; tiger_i++)
								{
									if (tigers[tiger_i].get_X() == i and tigers[tiger_i].get_Y() == (j - 1))
									{
										hunter_tiger = tiger_i;
										break;
									}
								}
								goats[bali_ka_bakhraa].setstate(Dead);
								Bakhraa::increaseDeathToll();
								goats[bali_ka_bakhraa].set_Position(-1, -1);
								grid[i][j] = 0;

								grid[i][j - 1] = 0;
								grid[i][j + 1] = 2;
								tigers[hunter_tiger].set_Position(i, j + 1);
								tigers[hunter_tiger].setPosition(Vector2f(x_grid[tigers[hunter_tiger].get_X()], y_grid[tigers[hunter_tiger].get_Y()]));
								is_goats_turn = true;
								continue;
							}
						}
					}
				}

				for (int j = -2; j < 3; j++)
				{
					for (int k = -2; k < 3; k++)
					{
						for (int i = 0; i < 4; i++)
						{
							int tiger_i_position_x = tigers[i].get_X();
							int tiger_i_position_y = tigers[i].get_Y();
							if ((abs(j) == 2 and abs(k) == 1) or (abs(j) == 1 and abs(k) == 2))
							{			  // if L shaped, skip that
								continue; // skipped for all tigers
							}
							if (!is_goats_turn and tiger_i_position_x + j >= 0 and tiger_i_position_y + k >= 0 and tiger_i_position_x + j <= 4 and tiger_i_position_y + k <= 4)
							{
								new_t_pos_x = tiger_i_position_x + j;
								new_t_pos_y = tiger_i_position_y + k;
								if ((abs(j) == 2 or abs(k) == 2) and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0 and grid[tiger_i_position_x + j / 2][tiger_i_position_y + k / 2] == 1) // Tiger moves to eat goat
								{																																									  // If tiger is in a position to eat
									if (j == k or j == -k && ((tiger_i_position_x + tiger_i_position_y) % 2 == 0))
									{ //////Diagonal//////
										mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
										mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

										for (int goat_i = 0; goat_i < 20; goat_i++)
										{
											if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
											{
												bali_ka_bakhraa = goat_i;
												break;
											}
										}
										goats[bali_ka_bakhraa].setstate(Dead);
										Bakhraa::increaseDeathToll();
										goats[bali_ka_bakhraa].set_Position(-1, -1);
										grid[mid_tile_x][mid_tile_y] = 0;

										grid[tiger_i_position_x][tiger_i_position_y] = 0;

										grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
										tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
										tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
										is_goats_turn = true;
										continue;
										// 	//tigers[i].setPosition(Vector2f())
									}

									else if (abs(new_t_pos_x - tiger_i_position_x) == 2 and new_t_pos_y == tiger_i_position_y)
									{ /// Horizontal///
										mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
										mid_tile_y = tiger_i_position_y;

										for (int goat_i = 0; goat_i < 20; goat_i++)
										{
											if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
											{
												bali_ka_bakhraa = goat_i;
												break;
											}
										}
										goats[bali_ka_bakhraa].setstate(Dead);
										Bakhraa::increaseDeathToll();
										goats[bali_ka_bakhraa].set_Position(-1, -1);
										grid[mid_tile_x][mid_tile_y] = 0;

										grid[tiger_i_position_x][tiger_i_position_y] = 0;

										grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
										tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
										tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
										is_goats_turn = true;
										continue;
										// 	//tigers[i].setPosition(Vector2f())
									}

									else
									{ // Vertical //
										mid_tile_x = tiger_i_position_x;
										mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

										for (int goat_i = 0; goat_i < 20; goat_i++)
										{
											if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
											{
												bali_ka_bakhraa = goat_i;
												break;
											}
										}
										goats[bali_ka_bakhraa].setstate(Dead);
										Bakhraa::increaseDeathToll();
										goats[bali_ka_bakhraa].set_Position(-1, -1);
										grid[mid_tile_x][mid_tile_y] = 0;

										grid[tiger_i_position_x][tiger_i_position_y] = 0;

										grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
										tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
										tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
										is_goats_turn = true;
										continue;
										// 	//tigers[i].setPosition(Vector2f())
										// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
									}
								}

								else if (!is_goats_turn and abs(j) < 2 and abs(k) < 2 and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0 && !(((tiger_i_position_x + tiger_i_position_y) % 2 == 1) && abs(j) == 1 && abs(k) == 1))
								{
									grid[tiger_i_position_x][tiger_i_position_y] = 0;
									grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
									tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
									tigers[i].setPosition(Vector2f(x_grid[tigers[i].get_X()], y_grid[tigers[i].get_Y()]));
									is_goats_turn = true;
									continue;
								}
							}
						}
					}

					// for (int i = 0; i < 4; i++) // i means bagh number
					// {if(!is_goats_turn) {
					// for (int j = -2; j < 3; j++)
					// {
					// 	if (!is_goats_turn)
					// 	{
					// 		for (int k = -2; k < 3; k++)
					// 		{
					// 			if (!is_goats_turn)
					// 			{
					// 				for (int i = 0; i < 4; i++) // i means bagh number
					// 				{
					// 					if (!is_goats_turn)
					// 					{
					// 						int tiger_i_position_x = tigers[i].get_X();
					// 						int tiger_i_position_y = tigers[i].get_Y();
					// 						if (tiger_i_position_x + j >= 0 and tiger_i_position_y + k >= 0 and tiger_i_position_x + j <= 4 and tiger_i_position_y + k <= 4)
					// 						{ // If Going position inside board
					// 							if (abs(j) == 1 or abs(k) == 1 or (j == k and k == 0) /*j != 0 and k != 0 and k != j*/)
					// 							{
					// 								continue;
					// 							}
					// 							else if ((abs(j) == 2 or abs(k) == 2) and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0 and grid[tiger_i_position_x + j / 2][tiger_i_position_y + k / 2] == 1) // Tiger moves to eat goat
					// 							{
					// 								new_t_pos_x = tiger_i_position_x + j;
					// 								new_t_pos_y = tiger_i_position_y + k;
					// 								if (j == k or j == -k)
					// 								{ //////Diagonal//////
					// 									mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
					// 									mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

					// 									for (int goat_i = 0; goat_i < 20; goat_i++)
					// 									{
					// 										if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
					// 										{
					// 											bali_ka_bakhraa = goat_i;
					// 											break;
					// 										}
					// 									}
					// 									goats[bali_ka_bakhraa].setstate(Dead);
					// 									bakhraa_killed++;
					// 									goats[bali_ka_bakhraa].set_Position(-1, -1);
					// 									grid[mid_tile_x][mid_tile_y] = 0;

					// 									grid[tiger_i_position_x][tiger_i_position_y] = 0;

					// 									grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
					// 									tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
					// 									is_goats_turn = true;
					// 									// 	//tigers[i].setPosition(Vector2f())
					// 									// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
					// 									// }
					// 								}

					// 								else if (abs(new_t_pos_x - tiger_i_position_x) == 2 and new_t_pos_y == tiger_i_position_y)
					// 								{ /// Horizontal///
					// 									mid_tile_x = min(tiger_i_position_x, new_t_pos_x) + 1;
					// 									mid_tile_y = tiger_i_position_y;

					// 									for (int goat_i = 0; goat_i < 20; goat_i++)
					// 									{
					// 										if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
					// 										{
					// 											bali_ka_bakhraa = goat_i;
					// 											break;
					// 										}
					// 									}
					// 									goats[bali_ka_bakhraa].setstate(Dead);
					// 									bakhraa_killed++;
					// 									goats[bali_ka_bakhraa].set_Position(-1, -1);
					// 									grid[mid_tile_x][mid_tile_y] = 0;

					// 									grid[tiger_i_position_x][tiger_i_position_y] = 0;

					// 									grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
					// 									tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
					// 									is_goats_turn = true;
					// 									// 	//tigers[i].setPosition(Vector2f())
					// 									// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
					// 								}

					// 								else
					// 								{ // Vertical //
					// 									mid_tile_x = tiger_i_position_x;
					// 									mid_tile_y = min(tiger_i_position_y, new_t_pos_y) + 1;

					// 									for (int goat_i = 0; goat_i < 20; goat_i++)
					// 									{
					// 										if (goats[goat_i].get_X() == mid_tile_x and goats[goat_i].get_Y() == mid_tile_y)
					// 										{
					// 											bali_ka_bakhraa = goat_i;
					// 											break;
					// 										}
					// 									}
					// 									goats[bali_ka_bakhraa].setstate(Dead);
					// 									bakhraa_killed++;
					// 									goats[bali_ka_bakhraa].set_Position(-1, -1);
					// 									grid[mid_tile_x][mid_tile_y] = 0;

					// 									grid[tiger_i_position_x][tiger_i_position_y] = 0;

					// 									grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
					// 									tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
					// 									is_goats_turn = true;
					// 									// 	//tigers[i].setPosition(Vector2f())
					// 									// best = max(best, minimax(grid, goats, tigers, depth, !isMax));
					// 								}
					// 							}

					// 							else if (!is_goats_turn and abs(j) < 2 and abs(k) < 2 and grid[tiger_i_position_x + j][tiger_i_position_y + k] == 0)
					// 							{
					// 								grid[tiger_i_position_x][tiger_i_position_y] = 0;
					// 								grid[tiger_i_position_x + j][tiger_i_position_y + k] = 2;
					// 								tigers[i].set_Position(tiger_i_position_x + j, tiger_i_position_y + k);
					// 								is_goats_turn = true;
					// 							}
					// 						}
					// 						//}
					// 					}
					// 				}
					// 			}
					// 		}

					// 		////// isMovesLeft not written ///////
					// 		// GameOver gameOver;
					// 		// gameOver.IsGameOver()
					// 		// int evaluate()
					// 		// {
					// 		// 	GameOver gameOverTry;
					// 		// 	g
					// 		// 	if(has_goat_won == true)
					// 		// 	{
					// 		// 		return -10;
					// 		// 	}
					// 		// 	else if(has_goat_won == false)
					// 		// 	{
					// 		// 		return +10;
					// 		// 	}
					// 		// }
					// 	}
					// }
				}
			}
		}
	}
}
