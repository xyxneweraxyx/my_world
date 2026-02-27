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
    function_t *func = c_alloc(sizeof(function_t), 1, alloc);
    function_t *func2 = c_alloc(sizeof(function_t), 1, alloc);

    setfml_t *setfml = setfml_ini((void *)myworld);

    if (!setfml)
        return 84;

    func->function = &data_callback;
    func->name[0] = 'a';
    func->name[1] = 'b';
    func->name[2] = 'c';
    func->paused = false;
    func->return_code = 0;
    node_t *node = linkedlist_newnode((void *)func);

    func2->function = &event_callback;
    func2->name[0] = 'd';
    func2->name[1] = 'e';
    func2->name[2] = 'f';
    func2->paused = false;
    func2->return_code = 0;
    node_t *node2 = linkedlist_newnode((void *)func2);

    setfml_fillparams(setfml);
    setfml_windowcreate(setfml);

    linkedlist_inserthead(setfml->functions[LOOP_DATA], node);
    linkedlist_inserthead(setfml->functions[LOOP_EVENT], node2);

    setfml_windowstart(setfml);
    setfml_destroy(setfml);
    c_delete(alloc, true);
    return 0;
}