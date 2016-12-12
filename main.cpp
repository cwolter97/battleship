#include <iostream>
#include "ship.h"

using namespace std;

void ResetGame();
void DisplayBoard();
void PlaceShips();

const int MAX_SHIPS = 5;
const int BOARD_SIZE = 10;
const char MISS = 'O';
const char HIT = 'X';

char game_board[BOARD_SIZE][BOARD_SIZE] = {'~'};

ship playerShips[MAX_SHIPS];
ship computerShips[MAX_SHIPS];

int main()
{
    ResetGame();
    DisplayBoard();

    PlaceShips();

    return 0;
}

void PlaceShips(){

    for(int i = 0; i < MAX_SHIP_SIZE; i++){
        ship* currentShip = &playerShips[i];
        bool shipPlaced = false;
        do{
            coord cPlacement;
            string sPlacement = "";

            cout << "\n\nPlease enter valid start coordinates for your " << currentShip->m_name << ". ex: x,y";
            cout << "\n>>";

            cin >> sPlacement;
                                //converts char to int
            cPlacement.x = sPlacement.c_str()[0] - '0';
            cPlacement.y = sPlacement.c_str()[2] - '0';

            bool directionPicked = false;
            char d;
            do{
                string direction = "";
                cout << "\nWhich direction should your boat point N,S,E,W";
                cout << "\n>>";
                cin >> direction;
                d = tolower(direction[0]);
                if(d == 'n' || d == 's' || d == 'e' || d == 'w'){
                    directionPicked = true;
                }
            }while(!directionPicked);

            coord lastcoord;
            //automatically puts coords for which direction told to go
            if(d == 'n' || d == 's'){
                playerShips[i].m_BoardPosition[0] = cPlacement;
                for(int j = 1; j < currentShip->m_length; j++){
                    currentShip->m_BoardPosition[j].x = currentShip->m_BoardPosition[0].x;
                    if(d == 'n')
                        currentShip->m_BoardPosition[j].y = (currentShip->m_BoardPosition[j-1].y - 1);
                    if(d == 's')
                        currentShip->m_BoardPosition[j].y = (currentShip->m_BoardPosition[j-1].y + 1);

                    lastcoord = currentShip->m_BoardPosition[j];
                }
            }

            if(d == 'e' || d == 'w'){
                playerShips[i].m_BoardPosition[0] = cPlacement;
                for(int j = 1; j < currentShip->m_length; j++){
                    currentShip->m_BoardPosition[j].y = currentShip->m_BoardPosition[0].y;
                    if(d == 'e')
                        currentShip->m_BoardPosition[j].x = (currentShip->m_BoardPosition[j-1].x + 1);
                    if(d == 'w')
                        currentShip->m_BoardPosition[j].x = (currentShip->m_BoardPosition[j-1].x - 1);

                    lastcoord = currentShip->m_BoardPosition[j];
                }
            }

            //check boat is on board
            if(lastcoord.x < 0 || lastcoord.x > BOARD_SIZE - 1){
                cout << "Your boat fell off the board on the X coord!";
            } else if(lastcoord.y < 0 || lastcoord.y > BOARD_SIZE -1){
                cout << "Your boat fell off the baord on the Y coord!";
            } else {
                shipPlaced = true;
            }

            //check no boat is already there
            for(int j = 0; j < MAX_SHIPS; j++){
                for(int k = 0; k < currentShip->m_length; k++){
                    for(int z = 0; z < currentShip->m_length; z++){
                        if(currentShip->m_name != playerShips[j].m_name){
                            if(currentShip->m_BoardPosition[k] == playerShips[j].m_BoardPosition[k]){
                                cout << "\nYou cannot put your " << currentShip->m_name << " over your " << playerShips[j].m_name << "!";
                                shipPlaced = false;
                                //please don't yell at me
                                goto endloop;
                            }
                        }
                    }
                }
            }
            endloop:
            shipPlaced = shipPlaced;
        }while(!shipPlaced);

        DisplayBoard();
    }
}

void DisplayBoard(){
    cout << " ";
    for(int i = 0; i < BOARD_SIZE; i++){
        cout << " " << i;
    }

    cout << endl;

    for(int k = 0; k < MAX_SHIPS; k++){
        for(int z = 0; z < playerShips[k].m_length; z++){
            for(int i = 0; i < BOARD_SIZE; i++){
                for(int j = 0; j < BOARD_SIZE; j++){
                    coord c(i,j);
                    if(playerShips[k].m_BoardPosition[z] == c)
                        game_board[i][j] = 'B';
                }
            }
        }
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        cout << i << " ";
        for(int j = 0; j < BOARD_SIZE; j++){
            cout << game_board[j][i] << " ";
        }
        cout << endl;
    }
}

void ResetGame(){
    //resets board
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            game_board[i][j] = '~';
        }
    }
    //reset ships
    playerShips[0].m_name = "Carrier";
    playerShips[0].m_length = 5;

    playerShips[1].m_name = "Battleship";
    playerShips[1].m_length = 4;

    playerShips[2].m_name = "Cruiser";
    playerShips[2].m_length = 3;

    playerShips[3].m_name = "Submarine";
    playerShips[3].m_length = 3;

    playerShips[4].m_name = "Destroyer";
    playerShips[4].m_length = 2;

    computerShips[0].m_name = "Carrier";
    computerShips[0].m_length = 5;

    computerShips[1].m_name = "Battleship";
    computerShips[1].m_length = 4;

    computerShips[2].m_name = "Cruiser";
    computerShips[2].m_length = 3;

    computerShips[3].m_name = "Submarine";
    computerShips[3].m_length = 3;

    computerShips[4].m_name = "Destroyer";
    computerShips[4].m_length = 2;

    for(int j = 0; j < MAX_SHIPS; j++){
        for(int i = 0; i < MAX_SHIP_SIZE; i++){
            playerShips[j].m_BoardPosition[i].x = -1;
            playerShips[j].m_BoardPosition[i].y = -1;

            computerShips[j].m_BoardPosition[i].x = -1;
            computerShips[j].m_BoardPosition[i].y = -1;

        }
    }
}
