#include "./setfml.h"

typedef struct myworld {
    int depth[10][10];
    int random_number;
} myworld_t;

size_t data_callback(setfml_t *setfml)
{
    printf("data callback!\n");
    return (size_t)SETFML_SUCC;
}

size_t event_callback(setfml_t *setfml)
{
    printf("event callback!\n");
    return (size_t)SETFML_SUCC;
}

size_t event_callback2(setfml_t *setfml)
{
    printf("data callback 2!\n");
    return (size_t)SETFML_SUCC;
}

size_t event_callback3(setfml_t *setfml)
{
    printf("draw callback 3!\n");
    return (size_t)SETFML_SUCC;
}


int main(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)5);
    myworld_t *myworld = c_alloc(sizeof(myworld_t), 1, alloc);
    setfml_t *setfml = setfml_ini((void *)myworld);

    if (!setfml)
        return 84;
    
    setfml_add_event(setfml, NULL, "event_callback", &event_callback);
    //setfml_add_data(setfml, &event_callback, "event_callback2", &event_callback2);
    //setfml_add_draw(setfml, NULL, "event_callback3", &event_callback3);
    setfml_fillparams(setfml);

    setfml_windowcreate(setfml);
    setfml_windowstart(setfml);

    setfml_destroy(setfml);
    c_delete(alloc, true);
    return 0;
}