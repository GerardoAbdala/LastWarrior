#include "Background.hpp"
#include "../motor/imagen/sprites.hpp"

background::background(std::string path_sprite, int x, int y,int w, int h){
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = nullptr;
    col_box=nullptr;
    tile=nullptr;

    sprite= new Sprite(path_sprite, posicion_mundo, w,h,w,h);


};

void background::update(double dt){
    if(posicion_mundo.x>=2000){
        posicion_mundo.x=512;
        }else if(posicion_mundo.x<=100){
        posicion_mundo.x=512;
        }
    };

void background::set_estado(void* estado){

};

void* background::get_estado(){
    return NULL;
};

