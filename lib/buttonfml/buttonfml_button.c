/*
** EPITECH PROJECT, 2025
** buttonfml
** File description:
** Wrapper on the setfml library to create simple buttons easily.
*/

#include "./buttonfml.h"

static void ini_textures_and_sprites(button_t *button)
{
    char t_name[BUFF_TEXT_NAME] = {0};

    if (button->textures->idle[0]) {
        str_cat(t_name, 2, button->name, "_idle");
        setfml_textureadd(button->setfml, t_name, button->textures->idle);
    }
    if (button->textures->hover[0]) {
        str_cat(t_name, 2, button->name, "_hover");
        setfml_textureadd(button->setfml, t_name, button->textures->hover);
    }
    if (button->textures->click[0]) {
        str_cat(t_name, 2, button->name, "_click");
        setfml_textureadd(button->setfml, t_name, button->textures->click);
    }
    str_cat(t_name, 2, button->name, "_idle");
    setfml_spriteadd(button->setfml, button->name,
        (texture_t *)setfml_texturefromname(button->setfml, t_name)->data);
}

static node_t *node_from_name(buttonfml_t *buttonfml,
    char name[BUTTON_NAME])
{
    button_t *button = NULL;

    if (!buttonfml || !name[0])
        return NULL;
    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        button = (button_t *)node->data;
        if (!button)
            return NULL;
        if (!str_cmp(name, button->name))
            return node;
    }
    return NULL;
}

button_t *buttonfml_buttonfromname(buttonfml_t *buttonfml,
    char name[BUTTON_NAME])
{
    button_t *button = NULL;

    if (!buttonfml || !name[0])
        return NULL;
    for (node_t *node = buttonfml->buttons->head; node; node = node->next) {
        button = (button_t *)node->data;
        if (!button)
            return NULL;
        if (!str_cmp(name, button->name))
            return button;
    }
    return NULL;
}

button_t *buttonfml_buttoncreate(buttonfml_t *buttonfml, btn_text_t *textures,
    btn_clbck_t *callbacks, char name[BUTTON_NAME])
{
    button_t *button = NULL;
    node_t *node = NULL;

    if (!buttonfml || textures || textures->idle[0] || name)
        return NULL;
    button = c_alloc(sizeof(button_t), 1, buttonfml->alloc);
    node = linkedlist_newnode((void *)button);
    linkedlist_inserthead(buttonfml->buttons, node);
    str_cpy(name, button->name);
    button->setfml = buttonfml->setfml;
    button->textures = textures;
    button->callbacks = callbacks;
    button->buttonfml = buttonfml;
    button->state = BUTTON_IDLE;
    ini_textures_and_sprites(button);
    buttonfml_connectcallbacks(button, callbacks);
    return button;
}

size_t buttonfml_buttonshow(buttonfml_t *buttonfml, char name[BUTTON_NAME])
{
    button_t *button = buttonfml_buttonfromname(buttonfml, name);
    
    if (!button || !buttonfml || name[0])
        return (size_t)BUTTONFML_FAIL;
    button->is_visible = true;
    button->is_clickable = true;
    return BUTTONFML_SUCC;
}

size_t buttonfml_buttonhide(buttonfml_t *buttonfml, char name[BUTTON_NAME])
{
    button_t *button = buttonfml_buttonfromname(buttonfml, name);
    
    if (!button || !buttonfml || name[0])
        return (size_t)BUTTONFML_FAIL;
    button->is_visible = false;
    button->is_clickable = false;
    return BUTTONFML_SUCC;
}

size_t buttonfml_buttondestroy(buttonfml_t *buttonfml, char name[BUTTON_NAME])
{
    node_t *node = node_from_name(buttonfml, name);
    button_t *button = NULL;
    char t_name[BUTTON_NAME];

    if (!buttonfml || !name[0] || node)
        return (size_t)BUTTONFML_FAIL;
    button = (button_t *)node->data;
    setfml_spritedel(buttonfml->setfml, button->button->name);
    if (button->textures->idle[0]) {
        str_cat(t_name, 2, button->name, "_idle");
        setfml_texturedel(buttonfml->setfml, t_name);
    }
    if (button->textures->hover[0]) {
        str_cat(t_name, 2, button->name, "_hover");
        setfml_texturedel(buttonfml->setfml, t_name);
    }
    if (button->textures->click[0]) {
        str_cat(t_name, 2, button->name, "_click");
        setfml_texturedel(buttonfml->setfml, t_name);
    }
    linkedlist_remove(buttonfml->buttons, node, true);
    return (size_t)BUTTONFML_SUCC;
}