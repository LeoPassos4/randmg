#include "player.h"

player::player(int x, int y,int temperature){
    this->x = x;
    this->y = y;
    this->temperature = temperature;
}

void player::setX(int x) {
    this->x = x;
}

void player::setY(int y) {
    this->y = y;
}

void player::setTemperature(int temperature) {
    this->temperature = temperature;
}

int player::getTemperature(){
    return temperature;
}

int player::getX() {
    return x;
}

int player::getY() {
    return y;
}
