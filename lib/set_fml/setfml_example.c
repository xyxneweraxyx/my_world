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

int main(void)
{
    c_alloc_t *alloc = c_ini((uint16_t)5);
    myworld_t *myworld = c_alloc(sizeof(myworld_t), 1, alloc);
    setfml_t *setfml = setfml_ini((void *)myworld);

    if (!setfml)
        return 84;
    
    setfml_add_event(setfml, NULL, "event_callback", &event_callback);
    function_t *function = (function_t *)setfml->functions[LOOP_EVENT]->head->data;
    printf("rn %d\n", (int)function->paused);
    setfml_fillparams(setfml);

    setfml_windowcreate(setfml);
    setfml_windowstart(setfml);

    setfml_destroy(setfml);
    c_delete(alloc, true);
    return 0;
}