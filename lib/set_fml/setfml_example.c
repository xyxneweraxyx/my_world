#include "./setfml.h"

typedef struct myworld {
    int depth[10][10];
    int random_number;
} myworld_t;

void configure(setfml_t *setfml)
{
    setfml->params.fps = (uint8_t)60;
    setfml->params.max_scr_res[0] = (uint16_t)1920;
    setfml->params.max_scr_res[1] = (uint16_t)1080;
    setfml->params.min_scr_res[0] = (uint16_t)800;
    setfml->params.min_scr_res[1] = (uint16_t)600;
    setfml->params.settings = NULL;
    setfml->params.title = "Ceci est un example";
    setfml->params.style = sfClose;
}

int main(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)5);
    myworld_t *myworld = NULL;
    setfml_t *setfml = NULL;

    if (!alloc)
        return 84;
    myworld = c_alloc(sizeof(myworld_t), 1, alloc);
    if (!myworld)
        return 84;
    setfml = setfml_ini((void *)myworld);
    configure(setfml);
    setfml_windowCreate(setfml);
    setfml_windowStart(setfml);
    setfml_destroy(setfml);
    c_delete(alloc, true);
    return 0;
}