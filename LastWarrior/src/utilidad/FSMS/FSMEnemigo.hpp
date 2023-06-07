#pragma once
#include "../../objetos_dinamicos/ObjetoDinamico.hpp"
#include "../../motor/KeyOyente.hpp"
#include "../../motor/MouseOyente.hpp"
#include<string>

class Enemigo; //forward declaration

class FSMEnemigo
{
    protected:
        std::string strnombre;
        Coordenadas direccion;
    
    public:
        virtual ~FSMEnemigo(){};
        virtual FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse)=0;
        FSMEnemigo* input_handle(int corX);
        virtual void entrar(Enemigo& enemy)=0;
        virtual void salir(Enemigo& enemy)=0;
        virtual void update(Enemigo& enemy,double dt)=0;
        std::string get_namestate()const{return strnombre;};

    public:
    // ... Funciones existentes ...

};

class EstadoEnemigoIDLE : public FSMEnemigo
{
    public:
        EstadoEnemigoIDLE();
        virtual  ~EstadoEnemigoIDLE(){};
        FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse);
        FSMEnemigo* input_handle(int corX);
        void entrar(Enemigo& enemy);
        void salir(Enemigo& enemy);
        void update(Enemigo& enemy,double dt);

    private:
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
    
};

class EstadoEnemigoMOVER : public FSMEnemigo
{
    public:
        EstadoEnemigoMOVER(Coordenadas dir);
        virtual ~EstadoEnemigoMOVER(){};
        FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse);
        FSMEnemigo* input_handle(int corX);
        void entrar(Enemigo& enemy);
        void salir(Enemigo& enemy);
        void update(Enemigo& enemy,double dt);
    private:
        Coordenadas direccion;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
};

class EstadoEnemigoSALTAR : public FSMEnemigo
{
    public:
        EstadoEnemigoSALTAR(int fuerza);
        virtual ~EstadoEnemigoSALTAR(){};
        FSMEnemigo* input_handle(KeyOyente& input, MouseOyente& mouse);
        FSMEnemigo* input_handle(int corX);
        void entrar(Enemigo& enemy);
        void salir(Enemigo& enemy);
        void update(Enemigo& enemy,double dt);
    private:
        int fuerza;
        int velocidad;
        int frames_actual_ani;
        int frames_maxim_ani;
        int frame_dt{0};
        bool aire{true};
};