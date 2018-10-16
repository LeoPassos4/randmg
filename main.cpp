#include <iostream>
#include <ctime>
#include <cmath>
#include <stdio.h>
#include "player.h"
#include <termios.h>
#include <unistd.h>

//int x,y;
int localtemper;

using namespace std;

void clearscr();
bool movep(char a);

int worldmap[100][200] = { //Map array
    {2,2,2,2,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,2},
    {2,1,1,1,1,1,1,1,1,2},
    {2,1,1,1,1,1,1,1,1,2},
    {2,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,1,1,1,1,2},
    {2,1,1,1,3,1,1,1,1,2},
    {2,1,1,1,2,1,1,1,1,2},
    {2,1,1,1,2,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2}
};

short season[2] {0,2};

int maxshowx = 40,maxshowy = 30;
//int maxshowx = 200,maxshowy = 60;

void drawmap(player pl);
int getch(void);
void randwm(int seed);

player p(0,0,0);
player p2(5,5,0);

void movec(int x,int y);

int main() {
    char a;
    bool R = true;

    //Main menu
    cout << "Random Map gerator v1.2" << endl;
    cout << endl << "\t\tBy Leonardo de Campos Passos" << endl;
    cout << "Controls:" << endl;
    cout << "\t'wasd' : to move" << endl;
    cout << "\t'r'    : to new random map" << endl;
    cout << "\t'esc'  : to exit." << endl;
    cout << endl << endl << "press any key to start...";
    getch();

    randwm(42);//Generate world with seed "42"

    bool randplayerpos = true;
    while (randplayerpos)//Random player initial location
    {
        srand(clock());rand();
        p.setX(rand() % maxshowx);
        srand(clock());rand();
        p.setY(rand() % maxshowy);
        //if (worldmap[p.getY()][p.getX()] != 1)
            randplayerpos = false;
        cout << "next roll" << endl;
    }

    while (R)
    {
        clearscr();//clear screem
        drawmap(p);//draw map and player
        cout << "X " << p.getX() << " Y " << p.getY() << " " << (int)worldmap[p.getY()][p.getX()] << endl;//Show player coords and tile id
        cout << "Local Temperature " << p.getTemperature() << endl;//Not finished yet
        //getline(cin,a);
        a = getch();
        if (a == 27)//Esc to exit
            //exit(0x0A);
            R = false;
        else if (a == 'w')//<Player movement>
            //p.setY(p.getY() - 1);
            movec(0,-1);
        else if (a == 's')
            //p.setY(p.getY() + 1);
            movec(0,1);
        else if (a == 'd')
            //p.setX(p.getX() + 1);
            movec(1,0);
        else if (a == 'a')
            //p.setX(p.getX() - 1);
            movec(-1,0);//</Player movement>
        else if (a == 'r')//Regenenerate the world
            randwm(clock());
        else
            cout << "nothing happen..." << endl;
    }
    return 0x00;
}

void movec(int x, int y){
    if (worldmap[p.getY() + y][p.getX() + x] == 3){}
    else if (worldmap[p.getY() + y][p.getX() + x] == 2){}
    else if (p.getY() + y < 0 || p.getY() + y >= maxshowy){}
    else if (p.getX() + x < 0 || p.getX() + x >= maxshowx){}
    else
    {
        p.setX(p.getX() + x);
        p.setY(p.getY() + y);
    }
}

void clearscr(){
    for (int i = 0;i < 50;i++)
        cout << endl;
}

void fillmap(int a){
    int x,y;
    for (y = 0;y < maxshowy;y++){
        for (x = 0;x < maxshowx;x++){
            worldmap[y][x] = a;
        }
    }
}

void randwm(int seed)
{
    int x,y;
    srand(seed);
    fillmap(1);

    for (int z = 0; z < 5; z++){
        for (y = 0;y < maxshowy;y++){
            for (x = 0;x < maxshowx;x++){
                if (worldmap[y][x] == 1)
                {
                    long a = rand();
                    if (a % 15){
                        if (worldmap[y + 1][x] == 1 || worldmap[y - 1][x] == 1 || worldmap[y][x + 1] == 1 || worldmap[y][x - 1] == 1)
                                {worldmap[y][x] = 1;}
                    }

                    else if (a % 12)
                        worldmap[y][x] = 2;

                    //else if (a % 13)
                    //    worldmap[y][x] = 3;
                    else if (a % 16)
                        worldmap[y][x] = 4;
                }
            }
        }
    }
}

void drawmap(player pl)
{
    for (int y = 0;y < maxshowy;y++){
        for (int x = 0;x < maxshowx;x++){
            if (pl.getX() == x && pl.getY() == y)
                cout << "\033[1;35m()\033[0m";
            //else if (p2.getX() == x && p2.getY() == y)
                //cout << "P2";
            else if (worldmap[y][x] == 1)
                cout <<  "\033[7;32m  \033[0m";
            else if (worldmap[y][x] == 2)
                cout << "\033[7;34m\033[1;47m^^\033[0m";
            else if (worldmap[y][x] == 3)
                cout << "\033[42m\033[7;36m[]\033[0m";
            else if (worldmap[y][x] == 4)
                cout << "\033[1;42m..\033[0m";
            else cout << '  ';

        }
        cout << endl;
    }
}

int getch(void)
{
	struct termios oldt, newt;
	int ch;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return ch;
}
