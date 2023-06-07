#include "sdlapp.hpp"
#include "utilidad/Tiempo.hpp"
#include "motor/KeyOyente.hpp"
#include "motor/MouseOyente.hpp"
#include <SDL_ttf.h>
#include "utilidad/RenderTexto.hpp"
#include "motor/fisica/MotorFisico.hpp"
#include <cmath>

//#define RECTANGULOS
//#define TRIANGULOS
//#define CIRCULOS

SDLApp* SDLApp::instancia = 0;

SDLApp::SDLApp()
{
    vnt = nullptr;
    vntsurf = nullptr;
    render = nullptr;
    ensamble= nullptr;
    bg_color.r = 255; //rojo
    bg_color.g = 255; //verde
    bg_color.b = 255; //azul
    bg_color.a = 255; //alpha

    esta_corriendo = true;
    WIDTH=1024;
    HEIGHT=720;
    maxFPS=60;
    fps=0;

    
};

//Como solo queremos una instancia del esta clase, entonces se hace una clase singleton
SDLApp& SDLApp::get()
{
    if(!instancia)
        instancia = new SDLApp();
    return *instancia;
};

bool SDLApp::on_init()
{
    //revisar que SDL inicio bien
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){return false;};
    //crear la ventana
    get().vnt = SDL_CreateWindow(
        "Juego",                // Titulo de la ventana
        SDL_WINDOWPOS_UNDEFINED,// posicion X de la pantalla
        SDL_WINDOWPOS_UNDEFINED,// posicion Y de la pantalla
        get().WIDTH,            // ancho de la ventana
        get().HEIGHT,           // alto de la ventana
        SDL_WINDOW_OPENGL);     // que use OPENGL
    
    TTF_Init();
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    //revisar que se creo bien la ventana
    if(get().vnt == NULL)
    {
        printf("No se creo la ventana por: %s",SDL_GetError());
        return false;
    }
    //la forma de procesar en GPU
    SDL_SetHint(SDL_HINT_RENDER_BATCHING,"opengl");
    //creamos el 'canvas'
    get().render = SDL_CreateRenderer(
        get().vnt,                  // la ventana
        -1,                         // driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);  // flags driver
    //revisamos si se creo correctamente
    if(get().render == NULL)
    {
        printf("No se creo el renderer por: %s",SDL_GetError());
        return false; 
    }
    // si se creo correcto lo agregamos al Pipeline
    get().ensamble = new Pipeline(*get().render);

    //08 tiles
    mapa = new Atlas("assets/sprites/mundo/ids/proyecto_ids.txt");
    mapa->generar_mapa(get().render,2,0);
    //05
    player = new Jugador("assets/sprites/heroe/prota_sheet.png",
                //      hp , x , y, sW,sH , vW,vH ,color
                        100,500,500,50,38,100,100,{255,0,255,255});
    enemy = new Enemigo("assets/sprites/enemigos/Gunner_Yellow_Run.png",
                //      hp , x , y, sW,sH , vW,vH ,color
                        20,550,500,48,48,100,100, {255,0,255,255});
    //new Jugador(100,500,50,{255,0,255,255});
    fondo= new background("assets/sprites/background/Untitled.png", 512,360,4238,1119);
    get().ensamble->cargar_texturas(fondo->get_sprite());
    printf("Se creo el fondo");
    get().ensamble->cargar_texturas(enemy->get_sprite());
    printf("Se creo el player\n");
    get().ensamble->cargar_texturas(player->get_sprite());
    printf("Se creo el player\n");
    plataformas = mapa->get_objetos_fisicos();

    plataformas.push_back(new Plataformas(550,550,6760,20,{0,0,0,255}));
    plataformas.push_back(new Plataformas(0,250,50,600,{0,0,0,255}));

    plataformas.push_back(new Plataformas(155,460,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(550,426,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(936,462,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(285,750,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(550,750,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(480,820,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(936,820,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(936,720,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1200,770,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1463,850,130,80,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1785,770,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2045,820,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2600,820,450,90,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3735,780,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3990,750,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(4055,820,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3870,700,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3995,560,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(4200,550,140,30,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2500,427,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2105,462,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1850,395,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1520,326,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1300,210,70,450,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2730,505,60,70,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2790,510,70,50,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3540,479,50,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(400,880,950,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(66,689,75,200,{0,0,0,255}));
    plataformas.push_back(new Plataformas(1365,880,580,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(2405,880,980,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(3475,880,780,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(4450,880,780,10,{0,0,0,255}));
    plataformas.push_back(new Plataformas(4160,720,75,320,{0,0,0,255}));

    for(int i=0;i<plataformas.size();i++)
    {
        //agregar todos los objetos en una lista para la camara
        objetos.push_back(plataformas[i]);
    }

    //06_Camaras

    get().camara_principal = new Camara(0,0,get().WIDTH,get().HEIGHT,*get().render);
    objetos.push_back(fondo);
    for(int i=0;i<plataformas.size();i++)
    {
        //agregar todos los objetos en una lista para la camara
        objetos.push_back(plataformas[i]);
    }

    objetos.push_back(enemy);    
    objetos.push_back(player);

    
    printf("\nSe crearon los objetos exitosamente\n");

    //agregamos el color del background del frame
    SDL_SetRenderDrawColor(
        get().render,       // canvas
        get().bg_color.r,   // rojo
        get().bg_color.g,   // verde
        get().bg_color.b,   // azul
        SDL_ALPHA_TRANSPARENT);// como usar el alpha

    return true;
};

void SDLApp::on_evento(SDL_Event* evento)
{
    if(evento->type==SDL_QUIT)
    {
        get().esta_corriendo = false;
    }
    //eventos del mouse
    MouseOyente::get().evento_movimiento(evento);
    MouseOyente::get().evento_presionado(evento);
    MouseOyente::get().evento_scroll(evento);
    // que esta presionado
    KeyOyente::get().keyPresionado(evento);
    
};

void SDLApp::on_fisicaupdate(double dt)
{
    
    //Camara Lock UnLock
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_L))
    {
        camara_principal->lock_objeto(*player);
    }
    else if(KeyOyente::get().estaPresionado(SDL_SCANCODE_U) && !camara_principal->en_transicion)
    {
        camara_principal->unluck_objeto();
    }

    //render cuadro colisión player
    if(KeyOyente::get().estaPresionado(SDL_SCANCODE_C))
    {
        player->render_colbox = (player->render_colbox)?false:true;
    }
    

    for(auto &p:objetos)
    {  
        p->update(dt);
        //p->render_colbox = true;
    }
    
    fondo->update(dt);
    player->input_handle(KeyOyente::get(),MouseOyente::get());
    enemy->input_handle(player->get_posx());
    
    //player->update(dt);


    MotorFisico2D::get().gravedad({player});
    MotorFisico2D::get().aabb_colision(*player,plataformas);
    //MotorFisico2D::get().sat_colision(*player,plataformas);
    
    /*CAMARA al final para actualizar la proyeción de los objetos*/
    camara_principal->input_handle(KeyOyente::get(),MouseOyente::get());
    camara_principal->update();
    camara_principal->proyectar(objetos);
    //printf("Update Fisica\n");

    
    
};

void SDLApp::on_frameupdate(double dt)
{
    // limpiar frame
    SDL_RenderClear(get().render);

    //Renderizar todo a través de la camara
    camara_principal->renderizar(objetos);
    //camara_principal->render_cross();

    //posicion del mouse
    int mx = MouseOyente::get().getX();
    int my = MouseOyente::get().getY();
    std::string pm = "mouse("+std::to_string(mx)+","+std::to_string(my)+")";
    Coordenadas cp = camara_principal->get_posicion_centro();
    Coordenadas mcp = camara_principal->get_posicion_mundo();
    std::string cm = "camara("+std::to_string(cp.x)+","+std::to_string(cp.y)+")";
    std::string cmm = "camara("+std::to_string(mcp.x)+","+std::to_string(mcp.y)+")";

    //RenderTexto::get().render_texto(get().render,815,630,pm,100,30,SDL_Color{0,0,0,255});
    //RenderTexto::get().render_texto(get().render,815,580,cmm,100,30,SDL_Color{0,0,0,255});
    //RenderTexto::get().render_texto(get().render,815,530,cm,100,30,SDL_Color{0,0,0,255});
    //fps
    RenderTexto::get().render_texto(get().render,get().WIDTH-200,30,
        std::to_string((int)(dt*1000*60))+" fps",
        100,30,SDL_Color{0,135,62});
    
    //RenderTexto::get().render_texto(get().render,50,630,player->get_strEstado(),120,30,SDL_Color{0,0,0,255});

    //Actualizar
    SDL_RenderPresent(get().render);

    //resetear color del frame
    SDL_SetRenderDrawColor(
        get().render,
        get().bg_color.r,
        get().bg_color.g,
        get().bg_color.b,
        SDL_ALPHA_TRANSPARENT);
};

void SDLApp::on_limpiar()
{
    SDL_DestroyRenderer(get().render);
    SDL_FreeSurface(get().vntsurf);
    SDL_DestroyWindow(get().vnt);

    for(auto &p:plataformas)
    {
        delete p;
    }
    plataformas.clear();
    delete ensamble;
    delete player;
    delete enemy;
    SDL_Quit();
};

int SDLApp::on_correr()
{
    //revisar que todo se inicializo bien
    if(get().on_init()==false){return -1;}

    SDL_Event eventos;
    double dt=0;
    double frecuencia = 1/get().maxFPS; // 1 frame a 60fps
    get().msfrecuencia = frecuencia*1000;

    while(get().estaCorriendo())
    {
        //double start = SDL_GetTicks();
        double inicio = Tiempo::get_tiempo();

        //printf("%lf <> %d\n",Tiempo::get_tiempo(),SDL_GetTicks());
        //captura eventos
        while(SDL_PollEvent(&eventos))
        {
            get().on_evento(&eventos);
        }

        //actualizamos si inicia o hay una diferencia de tiempo
        
        get().on_fisicaupdate(dt);
        get().on_frameupdate(dt);

        //calculamos el tiempo del frame
        dt = (Tiempo::get_tiempo() - inicio)/frecuencia*1000;
        
        inicio=dt; //el nuevo frame inicia en este tiempo
        //printf("<%d>[%lf][%d]\n",get().fps,dt,(int)Tiempo::get_tiempo());
        if(dt<get().msfrecuencia)
        {
            SDL_Delay(floor(get().msfrecuencia-dt));
        }
        //get().fps++;
    }
    //liberamos memoria
    get().on_limpiar();
    return 0;
};



