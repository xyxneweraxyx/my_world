/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

void setfml_fillparams(setfml_t *setfml)
{
    if (!setfml)
        return;
    setfml->params.window.fps = (uint8_t)240;
    setfml->params.window.max_scr_res[0] = (uint16_t)1920;
    setfml->params.window.max_scr_res[1] = (uint16_t)1080;
    setfml->params.window.min_scr_res[0] = (uint16_t)800;
    setfml->params.window.min_scr_res[1] = (uint16_t)600;
    setfml->params.window.settings = NULL;
    setfml->params.window.title = "My title";
    setfml->params.window.style = sfClose;
    setfml->params.time.event = 0;
    setfml->params.time.draw = 0;
    setfml->params.time.data = 300 * MILLI_TO_NANO;
    setfml->params.time.render = 0;
}

setfml_t *setfml_ini(void *userdata)
{
    c_alloc_t *alloc = c_ini((uint16_t)C_ALLOC_BASE);
    setfml_t *setfml = NULL;

    if (!alloc)
        return NULL;
    setfml = c_alloc(sizeof(setfml_t), 1, alloc);
    if (!setfml)
        return NULL;
    setfml->alloc = alloc;
    setfml->userdata = userdata;
    setfml->sprites = linkedlist_ini();
    setfml->textures = linkedlist_ini();
    for (size_t i = 0; i < 4; i++)
        setfml->functions[i] = linkedlist_ini();
    return setfml;
}

// On choisit de ne supprimer que les nodes et pas la data
// En supposant que l'utilisateur gère et free sa data
// (Notamment en utilisant c_alloc)
size_t setfml_destroy(setfml_t *setfml)
{
    linkedlist_destroy(setfml->sprites, false);
    linkedlist_destroy(setfml->textures, false);
    for (size_t i = 0; i < 4; i++)
        linkedlist_destroy(setfml->functions[i], false);
    sfRenderWindow_destroy(setfml->window);
    c_delete(setfml->alloc, true);
    return (size_t)SETFML_SUCC;
}