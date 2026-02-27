#include "./setfml.h"

typedef struct myworld {
    int depth[10][10];
    int random_number;
} myworld_t;

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
    if (!setfml)
        return 84;
    setfml_fillparams(setfml);
    setfml_windowCreate(setfml);
    setfml_windowStart(setfml);
    setfml_destroy(setfml);
    c_delete(alloc, true);
    return 0;
}