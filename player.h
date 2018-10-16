#ifndef PLAYER_H
#define PLAYER_H


class player
{
private:
    unsigned int x,y;
    int temperature;

public:
    int speed = 1;
    player(int x, int y,int temperature);
    void setX(int x);
    void setY(int y);
    void setTemperature(int temperature);
    int getX();
    int getY();
    int getTemperature();
};

#endif // PLAYER_H
