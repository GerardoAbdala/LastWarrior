#include "FSMEnemigo.hpp"
#include "../Func_aux.hpp"
#include<SDL.h>
#include<iostream>
#include <sstream>
#include<cmath>

/*
IDLE
*/
EstadoEnemigoIDLE::EstadoEnemigoIDLE()
{
    strnombre = "IDLE";
    frames_actual_ani=0;
    frames_maxim_ani=1;
};

FSMEnemigo* FSMEnemigo::input_handle(int corX)
{
    
    if(direccion.x > corX)
        return new EstadoEnemigoMOVER({1,0});
    else {
        return new EstadoEnemigoMOVER({-1,0});
    }
    //if(input.estaPresionado(SDL_SCANCODE_SPACE))
       // return new EstadoJugadorSALTAR(-10);

    // Handle input for state transition
    return NULL; // No state transition
};

FSMEnemigo* EstadoEnemigoIDLE::input_handle(KeyOyente& input, MouseOyente& mouse)
{
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoEnemigoMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoEnemigoMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_SPACE))
        return new EstadoEnemigoSALTAR(-10);
    /*if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoEnemigoMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoEnemigoMOVER({0,1});
*/
    return NULL;
};
void EstadoEnemigoIDLE::entrar(Enemigo& enemy)
{
    frames_actual_ani=0;
    frames_maxim_ani=4;
};
void EstadoEnemigoIDLE::salir(Enemigo& enemy)
{

};
void EstadoEnemigoIDLE::update(Enemigo& enemy,double dt)
{
    enemy.get_sprite()->play_frame(0,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>7)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    frame_dt++;

};

/*
MOVER
*/
EstadoEnemigoMOVER::EstadoEnemigoMOVER(Coordenadas dir)
{
    strnombre = "MOVER";
    direccion = dir;
    velocidad = 1;
    frames_actual_ani=0;
    frames_maxim_ani=1;
};

FSMEnemigo* EstadoEnemigoMOVER::input_handle(KeyOyente& input, MouseOyente& mouse)
{

    /*if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
       return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,-1});
        */
    /*
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});
    */
    //buggy
    
    if(input.nadaPresionado())
        return new EstadoEnemigoIDLE();
    

    return NULL;
};

//La siguiente funcion quien sabe si funcione, es una compia de la de arriba

FSMEnemigo* EstadoEnemigoMOVER::input_handle(int corX)
{

    /*if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_D))
       return new EstadoJugadorMOVER({1,1});
    if(input.estaPresionado(SDL_SCANCODE_S) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,-1});
    if(input.estaPresionado(SDL_SCANCODE_W) & input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,-1});
        */
    /*
    if(input.estaPresionado(SDL_SCANCODE_D))
        return new EstadoJugadorMOVER({1,0});
    if(input.estaPresionado(SDL_SCANCODE_A))
        return new EstadoJugadorMOVER({-1,0});
    if(input.estaPresionado(SDL_SCANCODE_W))
        return new EstadoJugadorMOVER({0,-1});
    if(input.estaPresionado(SDL_SCANCODE_S))
        return new EstadoJugadorMOVER({0,1});
    */
    //buggy
    
    //if(input.nadaPresionado())
        return new EstadoEnemigoIDLE();
    

    return NULL;
};

void EstadoEnemigoMOVER::entrar(Enemigo& enemy)
{
    frames_actual_ani=1;
    frames_maxim_ani=5;
    if(direccion.x==-1){
        enemy.get_sprite()->invertir=true;
    }else
    {
        enemy.get_sprite()->invertir=false;
        }
};
void EstadoEnemigoMOVER::salir(Enemigo& enemy){};
void EstadoEnemigoMOVER::update(Enemigo& enemy,double dt)
{
    Coordenadas p = enemy.get_posicion_mundo();
    if (enemy.en_colision)
    {
        float mag = std::sqrt(enemy.offsetoverlap.x*enemy.offsetoverlap.x +enemy.offsetoverlap.y*enemy.offsetoverlap.y);
        float rx = enemy.offsetoverlap.x/mag;
        float ry = enemy.offsetoverlap.y/mag;
        if(mag ==0)
        {
            rx=1;
            ry=0;
        }
        p.x =(p.x+rx*(-direccion.x)*velocidad) ;
        p.y =(p.y+ry*(-direccion.y)*velocidad) ;
    }
    else
    {
        p.x+=(velocidad*direccion.x);
        p.y+=(velocidad*direccion.y);
    }
    enemy.set_posicion_mundo(p);
    enemy.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    if (frames_actual_ani >=5)
            frames_actual_ani=1;
    frame_dt++;
};

//salto
EstadoEnemigoSALTAR::EstadoEnemigoSALTAR(int Fuerza){
    this->fuerza=Fuerza;
    frames_actual_ani=1;
    frames_maxim_ani=6;
};

FSMEnemigo* EstadoEnemigoSALTAR::input_handle(KeyOyente &keys, MouseOyente& mouse){
    if(!aire){
        return new EstadoEnemigoIDLE();
    }
    return NULL;
};

void EstadoEnemigoSALTAR::entrar(Enemigo & Enemy){
    Enemy.set_dtgf(fuerza);
    frames_actual_ani=1;
    frames_maxim_ani=6;
};

void EstadoEnemigoSALTAR::salir(Enemigo & Enemy){};

void EstadoEnemigoSALTAR::update(Enemigo & Enemy, double dt){
    DEBUGCOOR(Enemy.get_posicion_mundo());
    DEBUGPRINT(Enemy.get_dtgf())
    Enemy.get_sprite()->play_frame(1,frames_actual_ani%frames_maxim_ani);
    if(frame_dt>5)
    {
        frame_dt=0;
        frames_actual_ani++;
    }
    if (frames_actual_ani >=6)
            frames_actual_ani=1;
    frame_dt++;
    if (Enemy.get_dtgf()<1){
        aire=false;
    }
};


