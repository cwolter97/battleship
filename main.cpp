#include <iostream>
#include <cstring> //memset()
#include <iomanip> //setw()
#include <windows.h> //system()
#include <stdlib.h> //rand() ?
#include <time.h> //time()
#include "ship.h"

using namespace std;

void ResetGame();
void DisplayBoard();
void PlaceShips();
void PlaceEnemyShips();

const int MAX_SHIPS = 5;
const int BOARD_SIZE = 10;
const char MISS = 'O';
const char HIT = 'X';

char game_board[BOARD_SIZE][BOARD_SIZE];
char target_board[BOARD_SIZE][BOARD_SIZE];

ship playerShips[MAX_SHIPS];
ship computerShips[MAX_SHIPS];

int main()
{
    ResetGame();
    DisplayBoard();
    //PlaceShips();
    PlaceEnemyShips();
    DisplayBoard();

    system("pause");
    return 0;
}

void PlaceEnemyShips(){
    coord c(-1,-1);
    srand((unsigned) time(NULL));
    for(int k = 0; k < MAX_SHIPS; k++){
        bool shipPlaced = false;
        do{
            ship* currentShip = &computerShips[k];
            int x = rand() % 10;
            int y = rand() % 10;
            coord start(x,y);
            computerShips[k].m_BoardPosition[0] = start;
            int dir = rand() % 4 + 1;

            switch(dir){
                case 1://north
                    //computerShips[k].m_BoardPosition[0] = cPlacement;
                    for(int j = 1; j < currentShip->m_length; j++){
                        currentShip->m_BoardPosition[j].x = start.x;
                        currentShip->m_BoardPosition[j].y = (currentShip->m_BoardPosition[j-1].y - 1);
                    }
                    break;
                case 2://south
                    for(int j = 1; j < currentShip->m_length; j++){
                        currentShip->m_BoardPosition[j].x = start.x;
                        currentShip->m_BoardPosition[j].y = (currentShip->m_BoardPosition[j-1].y + 1);
                    }
                    break;
                case 3://east
                    for(int j = 1; j < currentShip->m_length; j++){
                        currentShip->m_BoardPosition[j].y = start.y;
                        currentShip->m_BoardPosition[j].x = (currentShip->m_BoardPosition[j-1].x + 1);
                    }
                    break;
                case 4://west
                    for(int j = 1; j < currentShip->m_length; j++){
                        currentShip->m_BoardPosition[j].y = start.y;
                        currentShip->m_BoardPosition[j].x = (currentShip->m_BoardPosition[j-1].x - 1);
                    }
                    break;
            }

            coord lastcoord = currentShip->m_BoardPosition[currentShip->m_length-1];
            if(lastcoord.x >= BOARD_SIZE || lastcoord.x < 0){
            } else if(lastcoord.y >= BOARD_SIZE || lastcoord.y < 0){
            } else {
                shipPlaced = true;
            }

            //check no boat is already there
            for(int j = 0; j < MAX_SHIPS; j++){ //check all ships
                for(int k = 0; k < computerShips[j].m_length; k++){ //check length of comparison boat
                    for(int z = 0; z < currentShip->m_length; z++){ //check length of boat being put down
                        if(currentShip->m_name != computerShips[j].m_name){ //avoid checking itself
                            if(currentShip->m_BoardPosition[z] == computerShips[j].m_BoardPosition[k]){
                                shipPlaced = false;
                                //please don't yell at me
                                goto endloop1;
                            }
                        }
                    }
                }
            }
            endloop1:
            if(0){}
        }while(!shipPlaced);
    }
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
            for(int j = 0; j < MAX_SHIPS; j++){ //check all ships
                for(int k = 0; k < playerShips[j].m_length; k++){ //check length of comparison boat
                    for(int z = 0; z < currentShip->m_length; z++){ //check length of boat being put down
                        if(currentShip->m_name != playerShips[j].m_name){ //avoid checking itself
                            if(currentShip->m_BoardPosition[z] == playerShips[j].m_BoardPosition[k]){
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
            if(0){}//need code after label for goto
        }while(!shipPlaced);

        DisplayBoard();
    }
}

void DisplayBoard(){
    system("cls");
    cout << setw(17) << "ENEMY BOARD\n";
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
                    if(playerShips[k].m_BoardPosition[z] == c){
                        game_board[i][j] = playerShips[k].m_name[0];
                    }
                    if(playerShips[k].m_hit[z]){
                        game_board[i][j] = 'X';
                    }
                }
            }
        }
    }

    for(int i = 0; i < BOARD_SIZE; i++){
        cout << i << " ";
        for(int j = 0; j < BOARD_SIZE; j++){
            cout << target_board[j][i] << " ";
        }
        cout << endl;
    }

    cout << " ";

    for(int i = 0; i < BOARD_SIZE; i++){
        cout << " " << i;
    }

    cout << endl;

    for(int i = 0; i < BOARD_SIZE; i++){
        cout << i << " ";
        for(int j = 0; j < BOARD_SIZE; j++){
            cout << game_board[j][i] << " ";
        }
        cout << endl;
    }

    cout << setw(17) << "YOUR BOARD\n";
}

void ResetGame(){
    //resets board
    memset(game_board, '~', sizeof(game_board[0][0]) * BOARD_SIZE * BOARD_SIZE);
    memset(target_board, '~', sizeof(target_board[0][0]) * BOARD_SIZE * BOARD_SIZE);

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
            coord offBoard(-1,-1);

            playerShips[j].m_BoardPosition[i] = offBoard;
            computerShips[j].m_BoardPosition[i] = offBoard;

        }
    }
}
