#ifndef BASE_INIT_H
#define BASE_INIT_H
#include <vector>
#include <string>

#include "Timer.h"
#include "Entity.h"
#include "Scanner.h"
//#include "Layers.h"

//#include <vita2d.h>


class Base_Init
{
    public:
        Base_Init();
        virtual ~Base_Init();
        void GPU_init();
        void GPU_init(unsigned int megabytes);
        void GPU_finish();

        //vita2d_pgf *pgf;
        vita2d_pvf *pvf;
        float rad;
        float delta_rad = 0.015f;
        bool grid_activated;

        void draw_grid();
        void draw_grid(int stride);

        bool draw_frame(std::vector<Entity *> obj);
        bool draw_frame(std::vector<std::vector<Entity *> *> &lay);


        void free_textures(std::vector<Entity *> &obj);

        void draw_texture_waved(vita2d_texture *image, int pos_x, int pos_y, int scale_x, int scale_y);


        //creates several letter objects using font spritesheet
        void create_text_from_font(std::string text, int x, int y,
                                   const char *filename, std::vector<Entity *> &obj);

        //layers;
        std::vector<Entity *> layer0;
        std::vector<Entity *> layer1;
        std::vector<Entity *> layer2;
        std::vector<Entity *> layer3;

        //vector of pointers to layers
        std::vector<std::vector<Entity *> *> layers;



        Timer grid_toggle_timer;


    protected:

    private:
        bool show(std::vector<Entity *> obj);

};

#endif // BASE_INIT_H
