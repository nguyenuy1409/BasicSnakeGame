#include <iostream>
#include "mylibs.h"

#define MAX 100

using namespace std;

int sl = 5; //snake beginning length 
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
void snake_move(int x_coord[], int y_coord[], int x, int y) {
    // Di chuyển con rắn
    for (int i = sl - 1; i > 0; i--) {
        x_coord[i] = x_coord[i - 1];
        y_coord[i] = y_coord[i - 1];
    }
    x_coord[0] = x;
    y_coord[0] = y;
}
int main(){
    ShowCur(false); //hide mouse pointer
    int x_coord[MAX], y_coord[MAX];
    wall();
    snake_create(x_coord, y_coord);
    snake(x_coord, y_coord);
    int x = 50, y = 13; //Starting point
    int check = 2;
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
       snake_move(x_coord, y_coord, x, y);
       snake(x_coord, y_coord);
       Sleep(200);
    }
    return 0;
}