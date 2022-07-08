#include<iostream>

class Animal
{
private:
    int totalNumber;
    int from_row, to_row;
    int from_column, to_column;
public: //change return types if necessary, wrote void just for declaration
    void DisplayOnBoard(); //need to write function definition

    void SelectPiece(); //need to write function definition

    void CheckValidityOfMove(); //need to write function definition
    
    void MovePieceToDestination(); //need to write function definition


};