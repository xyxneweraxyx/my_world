/*
** EPITECH PROJECT, 2025
** setfml
** File description:
** Tired of initializing csfml? Up your workflow with this simple wrapper.
*/

#include "./setfml.h"

static node_t *find_sprite(setfml_t *setfml, char name[BUFF_SPRITE_NAME])
{
    sprite_t *sprite = NULL;

    for (node_t *node = setfml->sprites->head; node; node = node->next) {
        sprite = (sprite_t *)node->data;
        if (!str_cmp(sprite->name, name))
            return node;
    }
    return NULL;
}

size_t setfml_spriteadd(setfml_t *setfml, char name[BUFF_SPRITE_NAME],
    texture_t *texture)
{
    sprite_t *sprite = c_alloc(sizeof(sprite_t), 1, setfml->alloc);
    node_t *node = c_alloc(sizeof(node_t), 1, setfml->alloc);

    if (!sprite || !node)
        return (size_t)SETFML_FAIL;
    str_cpy(name, sprite->name);
    sprite->texture = texture;
    sprite->sprite = sfSprite_create();
    if (!sprite->sprite)
        return (size_t)SETFML_FAIL;
    sfSprite_setTexture(sprite->sprite, texture->texture, sfTrue);
    node->data = (void *)sprite;
    if (linkedlist_inserthead(setfml->sprites, node) == (size_t)SETFML_FAIL)
        return (size_t)SETFML_FAIL;
    return (size_t)SETFML_SUCC;
}

size_t setfml_spritedel(setfml_t *setfml, char name[BUFF_SPRITE_NAME])
{
    node_t *node = NULL;
    sprite_t *sprite = NULL;

    if (!setfml || !setfml->sprites)
        return (size_t)SETFML_FAIL;
    node = find_sprite(setfml, name);
    if (!node)
        return (size_t)SETFML_FAIL;
    sprite = (sprite_t *)node->data;
    if (sprite->sprite)
        sfSprite_destroy(sprite->sprite);
    linkedlist_remove(setfml->sprites, node, true);
    return (size_t)SETFML_SUCC;
}
