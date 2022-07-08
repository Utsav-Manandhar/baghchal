#include <iostream>
#include <cmath>
using namespace std;
bool is_free(int arr[][5], int x, int y);
bool is_close(int arr[][5], int x, int y, int x2, int y2);
bool is_edible(int arr[][5], int x, int y, int x2, int y2);
void display_board(int arr[][5]);
int main()
{
	int arr[5][5], x_pos, y_pos, x_move, y_move, test, x_des, y_des,c=1,x_k,y_k;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			arr[i][j] = 0;
		}
	}
	arr[0][0] = 2;
	arr[0][4] = 2;
	arr[4][4] = 2;
	arr[4][0] = 2;
	while (c!=0)
	{
		//goat part
		test =0;
		while (test != 1)
		{
			display_board(arr);
			cout << "Choose the position of goat : " << endl;
			cin >> x_pos >> y_pos;
			x_pos--;
			y_pos--;
			test = 0;
			if (arr[x_pos][y_pos] == 2 || arr[x_pos][y_pos] == 1)
			{
				cout << "Square is full. " << endl;
			}
			else
			{
				arr[x_pos][y_pos] = 1;
				test = 1;
				display_board(arr);
			}
		}
		//tiger part
		test = 0;
		while (test != 1)
		{
			cout << "Choose tiger:  " << endl;
			cin >> x_pos >> y_pos;
			x_pos--;
			y_pos--;
			if (arr[x_pos][y_pos] == 2)
			{
				test = 1;
			}
			else
			{
				cout << "No tiger there. " << endl;
			}
		}
		test = 0;
		while (test != 1)
		{
			cout << "Choose destination: " << endl;
			cin >> x_des >> y_des;
			x_des--;
			y_des--;
			if (is_free(arr, x_des, y_des) && is_close(arr, x_pos, y_pos, x_des, y_des))
			{
				arr[x_pos][y_pos]=0;
				arr[x_des][y_des]=2;
				display_board(arr);
				test = 1;

			}else if(is_free(arr,x_des,y_des)&&is_edible(arr,x_pos,y_pos,x_des,y_des)){
				arr[x_des][y_des]=2;
				arr[x_pos][y_pos]=0;
				//arr[x_k][y_k]=0;
				display_board(arr);
				test =1;
			
			}else{
				cout<<"invalid move"<<endl;
			}
		}
		cout<<"Do you want to continue? "<<endl;
		cin>>c;
	}
	
	return 0;
}
void display_board(int arr[][5]){
	for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					cout << arr[i][j] << "  ";
				}
				cout << "\n";
			}
}
bool is_free(int arr[][5], int x, int y)
{
	if (arr[x][y] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool is_close(int arr[][5], int x, int y, int x2, int y2)
{

	if (x2 >=0 && y2 >=0 && x2 < 5 && y2 < 5 && abs(x2 - x) <= 1 && abs(y2 - y) <= 1)
	{
		return true;
	}
	{
	return false;
	}
}
bool is_edible(int arr[][5], int x, int y, int x2, int y2){
	if(x2>=0&&y2>=0&& x2 < 5 && y2 < 5){
		if(abs(x2-x)==2&&abs(y2-y)==0){
			if(x2>x&&arr[x+1][y]==1){
				// xk=x+1;
				// yk=y;
				return true;

			}else if(x2<x&&arr[x-1][y]==1){
				return true;
				// xk=x-1;
				// yk=y;
			}else{
				return false;
			}
		}else if(abs(y2-y)==2&&abs(x2-x)==0){
			if(y2>y&&arr[x][y+1]==1){
				return true;
				// xk=x;
				// yk=yk+1;
			}else if(y2<y&&arr[x][y-1]==1){
				return true;
				// xk=x;
				// yk=y-1;
			}else{
				return false;
			}
		}else if(abs(x2-x)==2&&(y2-y)==2){

			if(x2>x&&y2>y&&arr[x+1][y+1]==1){
				return true;
				// xk=x+1;
				// yk=y+1;
			}else if(x2>x&&y2<y&&arr[x+1][y-1]==1){
				// xk=x+1;
				// yk=y-1;
				return true;
			}else if(x2<x&&y2>y&&arr[x-1][y+1]==1){
				// xk=x-1;
				// yk=y-1;
				return true;
			}else{
				// xk=x-1;
				// yk=y-1;
				return true;
			}

		}
		else{
			return false;
		}
	}else{
		return false;
	}
}

