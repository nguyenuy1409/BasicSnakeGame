#pragma once //Avoid library conflicts when including files on top of each other
#include <stdio.h> 
#include <conio.h> //Library for real-time support 
#include <ctime>
#include <windows.h> 

#define KEY_NONE -1

//Get the current x-coordinate of the cursor.
int whereX(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}
//Get the current y-coordinate of the cursor.
int whereY(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}
//Move the current cursor to the coordinates (x, y)
void gotoXY(int x, int y){
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { (SHORT)x, (SHORT)y };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//Change the text color
void SetColor(WORD color){
/*
0	Black
1	Blue
2	Green
3	Aqua
4	Red
5	Purple
6	Yellow
7	White
8	Gray
9	Light Blue
10	Light Green
11	Light Aqua
12	Light Red
13	Light Purple
14	Light Yellow
15	Bright White
*/
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//Hide the mouse cursor
void ShowCur(bool CursorVisibility){ //hide mouse pointer
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}
//Return the key code of the key pressed by the user
int inputKey(){
    if (_kbhit()) {
        int key = _getch();

        if (key == 224) {
            key = _getch();
            return key + 1000;
        }

        return key;
    } else {
        return KEY_NONE;
    }

    return KEY_NONE;
}