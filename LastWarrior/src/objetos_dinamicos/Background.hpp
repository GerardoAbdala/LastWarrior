#pragma once
#include "ObjetoDinamico.hpp"
#include<SDL.h>
#include <string>

class background : public ObjetoDinamico
{

    public:
        background(std::string path_sprite, int x, int y,int w, int h);
        void update(double dt);
        void set_estado(void* estado);
        void* get_estado();
};
    





