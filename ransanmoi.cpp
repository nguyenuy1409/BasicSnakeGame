#include <iostream>
#include <cstdlib> //Library for function rand()
#include "mylibs.h"
void top_wall();
void bot_wall();
void right_wall();
void left_wall();
void wall();
void snake_create(int x_coord[], int y_coord[]);
void snake(int x_coord[], int y_coord[]);
void snake_clear(int x_coord[], int y_coord[]);
void snake_move(int x_coord[], int y_coord[], int x, int y, int &xfood, int &yfood);
bool game_over(int x_coord[], int y_coord[], int x, int y);
bool snake_eat_food(int xfood, int yfood, int x_coord[],  int y_coord[]);
void food_create(int &xfood, int &yfood, int x_coord[], int y_coord[]);
bool snake_ate_food(int xfood, int yfood, int x0, int y0);
void score_display();

#define MAX 100

using namespace std;

int sl = 4; //snake beginning length 
int score = 0; //starting score
void top_wall(){ //the top wall
    int x = 10, y = 1;
    while(x < 100){
        gotoXY(x, y);
        cout << '=';
        x++;
    }
}
void bot_wall(){ //the bottom wall
    int x = 10, y = 26;
    while(x < 100){
        gotoXY(x, y);
        cout << '=';
        x++;
    }
}
void right_wall(){ //the right wall
    int x = 100, y = 1;
    while(y < 27){
        gotoXY(x, y);
        cout << '+';
        y++;
    }
}
void left_wall(){ //the left wall
    int x = 10, y = 1;
    while(y < 27){
        gotoXY(x, y);
        cout << '+';
        y++;
    }
}
void wall(){ //save the 4 sides of the wall
    SetColor(2);
    top_wall();
    bot_wall();
    right_wall();
    left_wall();
}
void snake_create(int x_coord[], int y_coord[]){ //create the beginning coordinates of the snake
    int x = 50, y = 13;
    for(int i = 0; i < sl; i++){
        x_coord[i] = x;
        y_coord[i] = y;
        x--;
    }
}
void snake(int x_coord[], int y_coord[]){ //create the snake
    for(int i = 0; i < sl; i++){
        gotoXY(x_coord[i], y_coord[i]);
        if(i == 0){
            cout << '0'; //snake head
        }
        else{
            cout << 'o'; //snake body
        }
    }
}
void snake_clear(int x_coord[], int y_coord[]){ //remove old element
    for (int i = 0; i < sl; i++) {
        gotoXY(x_coord[i], y_coord[i]);
        cout << ' ';
    }
}
void snake_move(int x_coord[], int y_coord[], int x, int y, int &xfood, int &yfood){ //Snake's moverment and handle if snake eat food
    for (int i = sl - 1; i > 0; i--) {
        x_coord[i] = x_coord[i - 1];
        y_coord[i] = y_coord[i - 1];
    }
    if(snake_ate_food(xfood, yfood, x_coord[0], y_coord[0]) == false){ //
        x_coord[0] = x;
        y_coord[0] = y;
    }
    else{
        sl++;
        score +=1;
        food_create(xfood, yfood, x_coord, y_coord);
    }
}
bool game_over(int x_coord[], int y_coord[], int x, int y){ //Game over case
    //Check if snake hits the walls
    if(x <= 10 || x >= 100 || y <= 1 || y >= 26){
        return true;
    }
    //Check if snake hits its body
    for(int i = 1 ; i < sl ; i++){
        if(x == x_coord[i] && y == y_coord[i]){
            return true;
        }
    }
    return false;
}
void food_create(int &xfood, int &yfood, int x_coord[], int y_coord[]){ //create food randomly on the map
    //formula [a, b]: rand()%(b-a+1) + a
    do{
        //x food coordinate range [11, 99]
        xfood = rand()%89 + 11;
        //y food coordinate range [2, 25]
        yfood = rand()%24 + 2; 
    }
    while(snake_eat_food(xfood, yfood, x_coord, y_coord) == true); 
    gotoXY(xfood, yfood); 
    cout << '@';
}
bool snake_eat_food(int xfood, int yfood, int x_coord[],  int y_coord[]){ //check if the snake ate the fruit
    for(int i = 0 ; i < sl ; i++){
        if(xfood == x_coord[i] && yfood == y_coord[i]){
            return true; //the snake ate food
        }
    }
    return false; //the snake has not eaten the fruit yet

}
bool snake_ate_food(int xfood, int yfood, int x0, int y0){ //check if snake ate food
    if((x0 == xfood) && (y0 == yfood)){
        return true; //the snake ate food
    }
    return false;
}
void score_display(){ //score table
    gotoXY(0, 0);
    cout << "Score: " << score;
}
int main(){
    ShowCur(false); //hide mouse pointer
    int x_coord[MAX], y_coord[MAX];

    wall();
    snake_create(x_coord, y_coord);
    snake(x_coord, y_coord);
    int x = 50, y = 13; //Starting point
    int check = 2;
    srand(time(NULL)); //reset food position in the map
    int xfood = 0, yfood = 0;
    food_create(xfood, yfood, x_coord, y_coord); //create food in the map
    while(true){
        snake_clear(x_coord, y_coord);
        /*
        0: go down
        1: go up
        2: turn right
        3: turn left
        */
       if(_kbhit()){
        char button = _getch(); //input from keyboard
        if(button == -32){ //arrow keys
            button = _getch();
            if(button == 72 && check != 0){ //Up arrow key
                check = 1;
            }
            else if(button == 80 && check != 1){ //Down arrow key
                check = 0;
            }
            else if(button == 75 && check != 2){ //Left arrow key
                check = 3;
            }
            else if(button == 77 && check != 3){ //Right arrow key
                check = 2;
            }
        }
       }
       if(check == 0){ //go down
        y++;
       }
       else if(check == 1){ //go up
        y--;
       }
       else if(check == 2 ){ //turn right
        x++;
       }
       else if(check == 3){ //turn left
        x--;
       }
       if(game_over(x_coord, y_coord, x, y)){
        gotoXY(50, 13); 
        cout << "Game Over!" << endl;
        gotoXY(48, 14);
        cout << "Your Score: " << score;
        break;
       }
       snake_move(x_coord, y_coord, x, y, xfood, yfood);
       snake(x_coord, y_coord);
       score_display();
       Sleep(120);
    }
    return 0;
}