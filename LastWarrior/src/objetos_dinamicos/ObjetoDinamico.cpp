#include "ObjetoDinamico.hpp"
#include "../objetos/Figuras.hpp"
#include "../utilidad/Func_aux.hpp"
#include <iostream>

Jugador::Jugador(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {500,500}; // definir el piso en general
};

Jugador::Jugador(std::string path_sprite,float vida, int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,sw,sh,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,sw+10,sh+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoJugadorIDLE();
    piso = {512,360}; // definir el piso en general

    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);
    tile = nullptr;
};

std::string Jugador::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Jugador::get_estado()
{
    return estado_actual;
};

void Jugador::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMJugador*)estado;
    estado_actual->entrar(*this);
};

void Jugador::update(double dt)
{

    if(!estado_actual) //nulo
        return;

    /*if(en_colision)
        avatar->set_rellenocolor({255,0,0,255});
    else
        avatar->set_rellenocolor(color);
    */
    estado_actual->update(*this,dt);
    
    //reset
    en_colision=false;
    //DEBUGLINEA(posicion_mundo,piso)
    if(posicion_mundo.y>piso.y){
        set_dtgf(0);
        posicion_mundo.y=piso.y;
    }

};

void Jugador::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMJugador* estado = estado_actual->input_handle(input,mouse);
    if(estado)
    {
        set_estado(estado);
    }
};

Enemigo::Enemigo(float vida, int x, int y , SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,75,75,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,75+10,75+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoIDLE();
    piso = {500,500}; // definir el piso en general
};

Enemigo::Enemigo(std::string path_sprite,float vida, int x, int y, int w, int h, int sw, int sh, SDL_Color c)
:ObjetoDinamico{}
{
    hp = vida;
    posicion_mundo.x=x;
    posicion_mundo.y=y;
    avatar = new Rectangulo(x,y,sw,sh,c);
    c.a=150;
    color = c;
    avatar->set_rellenocolor(c);
    avatar->set_serellena(true);
    col_box = new Rectangulo(x,y,sw+10,sh+10,c);
    col_box->set_serellena(false);
    tiene_fisica = true;
    en_colision = false;
    estado_actual = new EstadoEnemigoIDLE();
    piso = {512,360}; // definir el piso en general

    sprite = new Sprite(path_sprite,posicion_mundo,w,h,sw,sh);
    tile = nullptr;
};

std::string Enemigo::get_strEstado()
{
    return estado_actual->get_namestate();
};

void* Enemigo::get_estado()
{
    return estado_actual;
};

void Enemigo::set_estado(void* estado)
{
    estado_actual->salir(*this);
    delete estado_actual;
    estado_actual = (FSMEnemigo*)estado;
    estado_actual->entrar(*this);
};

void Enemigo::update(double dt)
{

    if(!estado_actual) //nulo
        return;

    /*if(en_colision)
        avatar->set_rellenocolor({255,0,0,255});
    else
        avatar->set_rellenocolor(color);
    */
    estado_actual->update(*this,dt);
    
    //reset
    en_colision=false;
    //DEBUGLINEA(posicion_mundo,piso)
    if(posicion_mundo.y>piso.y){
        set_dtgf(0);
        posicion_mundo.y=piso.y;
    }

};

void Enemigo::input_handle(KeyOyente& input,MouseOyente& mouse)
{
    if(!estado_actual) //nulo
        return;
    FSMEnemigo* estado = estado_actual->input_handle(input,mouse);
    if(estado)
    {
        set_estado(estado);
    }
};

void Enemigo::input_handle(int corX)
{
    if (!estado_actual)
        return;
    FSMEnemigo* estado = estado_actual->input_handle(corX);
    if (estado)
    {
        set_estado(estado);
    }
};
